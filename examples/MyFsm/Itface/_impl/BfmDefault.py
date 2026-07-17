############################
###    COMPONENT FILE    ###
############################

# ====================
# Python imports
# ====================
import sys
import cocotb
from cocotb.triggers import Timer, RisingEdge, FallingEdge, ClockCycles #, Event
from cocotb.clock import Clock
from pyuvm import uvm_sequence_item

# ====================
# UVMEnv imports
# ====================
from BFM import BFM
from utils import config
ISDUTSEQ = config.dut_design.type == 'sequential'
SYNC_CYCLES = int(config.dut_cs4seq.sync_cycles)
CLOCK_PERIOD = int(config.dut_cs4seq.clock_period)
SIM_UNITS = config.dut_design.sim_units
CYCLES4WAIT_RESET = int(config.dut_cs4seq.cycles4wait_reset)




class BfmDefault(BFM):
    def __init__(self):
        self.dut = cocotb.top
        self.__transaction = None
        
        
    async def set(self, transaction: uvm_sequence_item):
        self.__transaction = transaction

        # If DUT is SEQUENTIAL, comment lines which refers to clock and reset signals.
        # (the reason is they will be handled by cocotb triggers with init and reset methods)
        # self.dut.i_clk.value = self.__transaction.i_clk
        # self.dut.i_rst_n.value = self.__transaction.i_rst_n
        self.dut.i_x.value = self.__transaction.i_x
        
        # Time for waiting Driver request to DUT
        if ISDUTSEQ: await ClockCycles(self.dut.i_clk, SYNC_CYCLES)
        else:        await Timer(SYNC_CYCLES, units=SIM_UNITS)
        

    async def get(self):
        # Await some time for DUT to process the transaction and produce output
        if ISDUTSEQ:
            # If DUT is active in posedge, then read on FallingEdge,
            # or if DUT is active in negedge, then read on RisingEdge.
            await FallingEdge(self.dut.i_clk)
        else:
            await Timer(SYNC_CYCLES, units=SIM_UNITS)
        
        # Define response values from DUT to transaction
        self.__transaction.o_y = self.dut.o_y.value
        self.__transaction.o_state = self.dut.o_state.value

        # Return updated transaction
        return self.__transaction


    async def init(self):
        ''' This method is invoked on your Test when DUT is sequential '''

        # Define how long is your clock period (greater or equal with 'ns')
        # Start clock
        cocotb.start_soon( Clock(self.dut.i_clk, CLOCK_PERIOD, units=SIM_UNITS).start() ) 
        
        # Make the initial reset
        await self.reset()



    async def reset(self):
        ''' Use this method only if DUT is sequential '''        
        # Define the correct sequence to reset DUT
        # (depends on your DUT design, active high or low)
        self.dut.i_rst_n.value = 0
        await ClockCycles(self.dut.i_clk, CYCLES4WAIT_RESET)
        self.dut.i_rst_n.value = 1
        

sys.modules[__name__] = BfmDefault
