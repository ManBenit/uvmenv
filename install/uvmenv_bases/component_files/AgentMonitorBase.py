############################
###    COMPONENT FILE    ###
############################

# ====================
# Python imports
# ====================
import importlib
import pyuvm
import copy
from pyuvm import uvm_monitor, uvm_analysis_port

# ====================
# UVMEnv imports
# ====================
from UVMEnvReport import report
from utils import config
ISDUTSEQ = config.dut_design.type == 'sequential'


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
            # Read transaction from DUT   
            transaction = await self.bfm.get()

            # Send to reference model
            self.get_parent().get_parent().refmodel.set(transaction)

            # Write on report (optional)
            report.write(message=str(transaction), component=self, level=pyuvm.INFO)

            # Send transaction to subscribers
            self.send.write(copy.copy(transaction))


    def __import_bfm(self):
        # Get an specific value from .json
        implementation_class = config.uvm_components.itface.bfm_impl

        # Convert value into Python implementation that you want to use
        try:
            module = importlib.import_module(implementation_class)
            self.bfm = module()
        except Exception as e:
            self.logger.critical(f'Failed to load BFM implementation: {e}')
            return

    
