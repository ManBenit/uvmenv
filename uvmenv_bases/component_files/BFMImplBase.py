############################
###    COMPONENT FILE    ###
############################

import cocotb

# Use only Timer if your design is combinational.
from cocotb.triggers import Timer
"""
# Add Clock and ClockCycles if your design is sequencial:
from cocotb.triggers import Timer, RisingEdge, ClockCycles
from cocotb.clock import Clock
"""

from BFM import BFM


class CLASS_NAME(BFM):
    def __init__(self):
        self.dut = cocotb.top
        
        
    async def set(self, *, PARAMETERS):
INIT_VALUES
        # Time for waiting Driver successfully request to DUT
        await Timer(1, units='ns')

    async def get(self):
        ins = {
GET_INS
        }

        outs = {
GET_OUTS
        }
        
        return (ins, outs)

    async def init(self):
        # Use this method for init design when design is sequential
        ## It defines how long is clock period (greater or equal with 'ns')
        """
        self.clock = Clock(self.dut.YOUR_CLOCK_SIGNAL, 1, units='ns')  
        cocotb.start_soon(self.clock.start()) 
        """

        # Make the initial reset
        await self.reset()



    async def reset(self):
        # Use this method for reset DUT
        """
        self.dut.YOUR_RESET_SIGNAL.value = 1
        await ClockCycles(self.dut.YOUR_CLOCK_SIGNAL, 2)
        self.dut.YOUR_RESET_SIGNAL.value = 0
        """

