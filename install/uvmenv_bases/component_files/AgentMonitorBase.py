############################
###    COMPONENT FILE    ###
############################

# ====================
# Python imports
# ====================
import importlib
import pyuvm
from pyuvm import uvm_monitor, uvm_analysis_port
from cocotb.triggers import Timer, RisingEdge, FallingEdge

# ====================
# Python imports
# ====================
from UVMEnvReport import report
from utils import config
ISDUTSEQ = config.dut_design.type == 'sequential'
CLOCK_CYCLES = int(config.dut_design.sync_clock_cycles)


class Monitor(uvm_monitor):
    def __init__(self, name, parent):
        super().__init__(name, parent)


    def build_phase(self):
        super().build_phase()
        self.__import_bfm()
        self.send = uvm_analysis_port('send_monitor', self)

    async def run_phase(self):
        await super().run_phase()
        while True:
            # Time for waiting response from DUT 
            if ISDUTSEQ:            
                ## This await is for matching with event on BFMImpl)
                ## (you can use also FallingEdge)
                await RisingEdge(self.bfm.dut.YOUR_CLOCK_SIGNAL)
            else:
                await Timer(CLOCK_CYCLES, units='ns')

            transaction = await self.bfm.get()
            report.write(message=str(transaction), component=self, level=pyuvm.INFO)
            self.send.write(transaction.response)


    def __import_bfm(self):
        # Get an specific value from .json
        implementation_class = config.uvm_components.itface.bfm_impl

        # Convert value into Python implementation that you want to use
        try:
            module = importlib.import_module(implementation_class)
            clazz = getattr(module, implementation_class)
            self.bfm = clazz()
        except Exception as e:
            self.logger.critical(f'Failed to load BFM implementation: {e}')
            return

    
