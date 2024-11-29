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
        # Time for waiting Driver request to DUT
        await Timer(1, units='ns')

    async def get(self):
        ins = {
GET_INS
        }

        outs = {
GET_OUTS
        }
        
        return (ins, outs)

    def init(self):
        # Use this method for init clock and other control signals
        """
        self.clock = Clock(self.dut.YOUR_CLOCK_SIGNAL, 1, units='ns')  
        cocotb.start_soon(self.clock.start()) 
        """

    async def reset(self):
        # Use this method for reset DUT
        """
        self.dut.YOUR_RESET_SIGNAL.value = 1
        await ClockCycles(self.dut.YOUR_CLOCK_SIGNAL, X)  # Where X: number of clock cycles for waiting.
        self.dut.YOUR_RESET_SIGNAL.value = 0
        """

