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
        
        
    async def set(self, *, ex_aluop_i,ex_datars1_i,ex_datars2_i):
        # If DUT is sequential, comment the two lines which refers to clock and reset signal.
        # (the reason is they are being handled by cocotb triggers with init and reset method) 
        self.dut.ex_aluop_i.value = ex_aluop_i
        self.dut.ex_datars1_i.value = ex_datars1_i
        self.dut.ex_datars2_i.value = ex_datars2_i

        # Time for waiting Driver request to DUT
        ## The next await line when DUT is combinatorial (watch config.json)
        await Timer(CLOCK_CYCLES, units='ns')
        ## The next await line when DUT is sequential (It must match with event on Monitor)
        ###await RisingEdge(self.dut.YOUR_CLOCK_SIGNAL)

    async def get(self):
        ins = {
            'ex_aluop_i': self.dut.ex_aluop_i.value,
            'ex_datars1_i': self.dut.ex_datars1_i.value,
            'ex_datars2_i': self.dut.ex_datars2_i.value
        }

        outs = {
            'ex_zerof_o': self.dut.ex_zerof_o.value,
            'ex_data_o': self.dut.ex_data_o.value
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
        self.dut.YOUR_RESET_SIGNAL.value = 1
        await RisingEdge(self.dut.YOUR_CLOCK_SIGNAL)
        self.dut.YOUR_RESET_SIGNAL.value = 0
        """

