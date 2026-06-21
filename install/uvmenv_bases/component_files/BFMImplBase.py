############################
###    COMPONENT FILE    ###
############################

# ====================
# Python imports
# ====================
import sys
import cocotb
from cocotb.triggers import Timer, RisingEdge, FallingEdge
from cocotb.clock import Clock
from pyuvm import uvm_sequence_item

# ====================
# UVMEnv imports
# ====================
from BFM import BFM
from utils import config
ISDUTSEQ = config.dut_design.type == 'sequential'
CLOCK_CYCLES = int(config.dut_design.sync_clock_cycles)




class CLASS_NAME(BFM):
    def __init__(self):
        self.dut = cocotb.top
        self.__transaction = None
        
        
    async def set(self, transaction: uvm_sequence_item):
        self.__transaction = transaction

        # If DUT is sequential, comment the two lines which refers to clock and reset signals.
        # (the reason is they wil be handled by cocotb triggers with init and reset methods)
ASSIGN_REQ_VALUES
        
        # Time for waiting Driver request to DUT
        if ISDUTSEQ:
            # Must match with event on Monitor (RisingEdge or FallingEdge)
            await RisingEdge(self.dut.YOUR_CLOCK_SIGNAL)
        else:
            await Timer(CLOCK_CYCLES, units='ns')
        

    async def get(self):
        # Define response values from DUT to transaction
ASSIGN_RES_VALUES

        # Return updated transaction
        return self.__transaction

    async def init(self):
        ''' This method is invoked on your Test when DUT is sequential '''

        # Define how long is your clock period (greater or equal with 'ns')
        #self.clock = Clock(self.dut.YOUR_CLOCK_SIGNAL, CLOCK_CYCLES, units='ns')  
        #cocotb.start_soon(self.clock.start()) 
        
        # Make the initial reset
        await self.reset()



    async def reset(self):
        ''' Use this method only if DUT is sequential '''
        
        # Define the correct sequence to reset DUT
        #self.dut.YOUR_RESET_SIGNAL.value = 1
        #await RisingEdge(self.dut.YOUR_CLOCK_SIGNAL)
        #self.dut.YOUR_RESET_SIGNAL.value = 0
        

sys.modules[__name__] = CLASS_NAME
