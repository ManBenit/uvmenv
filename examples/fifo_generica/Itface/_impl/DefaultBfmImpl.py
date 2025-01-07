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
        
        
    async def set(self, *, clk_i,rst_ni,rd_i,wr_i,command_i,data_i,address_i):
        # If DUT is sequential, comment the two lines which refers to clock and reset signal.
        # (the reason is they are being handled by cocotb triggers with init and reset method) 
        #self.dut.clk_i.value = clk_i
        #self.dut.rst_ni.value = rst_ni
        self.dut.rd_i.value = rd_i
        self.dut.wr_i.value = wr_i
        self.dut.command_i.value = command_i
        self.dut.data_i.value = data_i
        self.dut.address_i.value = address_i

        # Time for waiting Driver request to DUT
        ## The next await line when DUT is combinatorial (watch config.json)
        ###await Timer(CLOCK_CYCLES, units='ns')
        ## The next await line when DUT is sequential (It must match with event on Monitor)
        await RisingEdge(self.dut.clk_i)

    async def get(self):
        ins = {
            'clk_i': self.dut.clk_i.value,
            'rst_ni': self.dut.rst_ni.value,
            'rd_i': self.dut.rd_i.value,
            'wr_i': self.dut.wr_i.value,
            'command_i': self.dut.command_i.value,
            'data_i': self.dut.data_i.value,
            'address_i': self.dut.address_i.value
        }

        outs = {
            'command_o': self.dut.command_o.value,
            'den': self.dut.den.value,
            'empty': self.dut.empty.value,
            'full': self.dut.full.value,
            'data_o': self.dut.data_o.value,
            'address_o': self.dut.address_o.value
        }
        
        return (ins, outs)

    async def init(self):
        # Use this method for init DUT when it's sequential
        ## It defines how long is clock period (greater or equal with 'ns')
        
        self.clock = Clock(self.dut.clk_i, CLOCK_CYCLES, units='ns')  
        cocotb.start_soon(self.clock.start()) 
        

        # Make the initial reset
        await self.reset()



    async def reset(self):
        # Use this method for reset DUT when it's sequential
        
        self.dut.rst_ni.value = 0
        await RisingEdge(self.dut.clk_i)
        self.dut.rst_ni.value = 1
        

