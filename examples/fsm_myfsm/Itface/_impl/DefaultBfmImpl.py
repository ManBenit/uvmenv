############################
###    COMPONENT FILE    ###
############################

import cocotb
from cocotb.triggers import Timer, RisingEdge, FallingEdge
from cocotb.clock import Clock
from utils import load_config


CONFIG = load_config('config.json')
SEQUENTIAL_DUT = True if CONFIG.dut_design.type == 'sequential' else False
CLOCK_CYCLES = int(CONFIG.dut_design.sync_clock_cycles)

from BFM import BFM


class DefaultBfmImpl(BFM):
    def __init__(self):
        self.dut = cocotb.top
        
        
    async def set(self, *, i_clk,i_rst_n,i_x):
        # If DUT is sequential, comment the two lines which refers to clock and reset signal.
        # (the reason is they are being handled by cocotb triggers with init and reset method) 
        #self.dut.i_clk.value = i_clk
        #self.dut.i_rst_n.value = i_rst_n
        self.dut.i_x.value = i_x

        # Time for waiting Driver request to DUT
        ## The next await line when DUT is combinatorial (watch config.json)
        ###await Timer(CLOCK_CYCLES, units='ns')
        ## The next await line when DUT is sequential (It must match with event on Monitor)
        await RisingEdge(self.dut.i_clk)

    async def get(self):
        ins = {
            'i_clk': self.dut.i_clk.value,
            'i_rst_n': self.dut.i_rst_n.value,
            'i_x': self.dut.i_x.value
        }

        outs = {
            'o_y': self.dut.o_y.value,
            'o_state': self.dut.o_state.value
        }
        
        return (ins, outs)

    async def init(self):
        # Use this method for init DUT when it's sequential
        ## It defines how long is clock period (greater or equal with 'ns')
        
        self.clock = Clock(self.dut.i_clk, CLOCK_CYCLES, units='ns')  
        cocotb.start_soon(self.clock.start()) 
        

        # Make the initial reset
        await self.reset()



    async def reset(self):
        # Use this method for reset DUT when it's sequential
        
        self.dut.i_rst_n.value = 0
        await RisingEdge(self.dut.i_clk)
        self.dut.i_rst_n.value = 1

    async def reset_on(self):
        self.dut.i_rst_n.value = 0
        await RisingEdge(self.dut.i_clk)

    async def reset_off(self):
        self.dut.i_rst_n.value = 1
        await RisingEdge(self.dut.i_clk)
        

