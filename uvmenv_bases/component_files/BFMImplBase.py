############################
###    COMPONENT FILE    ###
############################

import cocotb
from cocotb.triggers import Timer, RisingEdge, FallingEdge
from cocotb.clock import Clock


CLOCK_CYCLES = 1

from BFM import BFM


class CLASS_NAME(BFM):
    def __init__(self):
        self.dut = cocotb.top
        
        
    async def set(self, *, PARAMETERS):
        # If DUT is sequential, comment the next two lines which refers to clock and reset signal
        # (the reason is they are being handled by cocotb triggers with init and reset method) 
INIT_VALUES
        # Time for waiting Driver request to DUT
        ## The next line when design is combinatorial
        await Timer(CLOCK_CYCLES, units='ns')
        ## The next line when design is sequential (when you are monitoring on FallingEdge)
        ###await RisingEdge(self.dut.clk_i)
        ## The next line when design is sequential (when you are monitoring on RisingEdge)
        ###await FallingEdge(self.bfm.dut.clk_i)

    async def get(self):
        ins = {
GET_INS
        }

        outs = {
GET_OUTS
        }
        
        return (ins, outs)

    async def init(self):
        # Use this method for init DUT when it's sequential
        ## It defines how long is clock period (greater or equal with 'ns')
        """
        self.clock = Clock(self.dut.YOUR_CLOCK_SIGNAL, CLOCK_CYCLES, units='ns')  
        cocotb.start_soon(self.clock.start()) 
        """

        # Make the initial reset
        await self.reset()



    async def reset(self):
        # Use this method for reset DUT when it's sequential
        """
        self.dut.YOUR_RESET_SIGNAL.value = 0
        await RisingEdge(self.dut.clk_i)
        self.dut.YOUR_RESET_SIGNAL.value = 1
        """

