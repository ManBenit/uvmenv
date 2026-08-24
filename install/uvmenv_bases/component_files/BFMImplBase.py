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
ISDUTSEQ          =     config.dut_design.type == 'sequential'
SYNC_CYCLES       = int(config.dut_cs4seq.sync_cycles)
CLOCK_PERIOD      = int(config.dut_cs4seq.clock_period)
CYCLES4WAIT_RESET = int(config.dut_cs4seq.cycles4wait_reset)
CLOCK_NAME        =     config.dut_cs4seq.clock_name
CLOCK_EDGE_ACT    =     config.dut_cs4seq.clock_edge_act
RESET_NAME        =     config.dut_cs4seq.reset_name
RESET_EDGE_ACT    =     config.dut_cs4seq.reset_edge_act
SIM_UNITS         =     config.simulation.time_unit





class CLASS_NAME(BFM):
    def __init__(self):
        self.dut = cocotb.top
        self.__transaction = None
        
        
    async def set(self, transaction: uvm_sequence_item):
        self.__transaction = transaction

        # If DUT is SEQUENTIAL, comment lines which refers to clock and reset signals.
        # (the reason is they will be handled by cocotb triggers with init and reset methods)
ASSIGN_REQ_VALUES
        
        # Time for waiting Driver request to DUT
        if ISDUTSEQ: await ClockCycles( getattr(self.dut, CLOCK_NAME, None) , SYNC_CYCLES )
        else:        await Timer(SYNC_CYCLES, unit=SIM_UNITS)
        

    async def get(self):
        # Await some time for DUT to process the transaction and produce output
        if ISDUTSEQ:
            # If DUT is active in posedge, then read on FallingEdge,
            # or if DUT is active in negedge, then read on RisingEdge.
            if CLOCK_EDGE_ACT == 'high':
                await FallingEdge(getattr(self.dut, CLOCK_NAME, None)) 
            else:
                await RisingEdge(getattr(self.dut, CLOCK_NAME, None)) 
        else:
            await Timer(SYNC_CYCLES, unit=SIM_UNITS)
        
        # Define response values from DUT to transaction
ASSIGN_RES_VALUES

        # Return updated transaction
        return self.__transaction


    async def init(self):
        ''' This method is invoked on your Test when DUT is sequential '''

        # Define how long is your clock period (greater or equal with 'ns')
        # Start clock
        clock = Clock( getattr(self.dut, CLOCK_NAME, None) , CLOCK_PERIOD, unit=SIM_UNITS )
        cocotb.start_soon( clock.start() ) 
        
        # Make the initial reset
        await self.reset()



    async def reset(self):
        ''' Use this method only if DUT is sequential '''        
        # Define the correct sequence to reset DUT
        # (depends on your DUT design, active high or low)
        do_reset = 1 if RESET_EDGE_ACT == 'high' else 0
        undo_reset = 0 if RESET_EDGE_ACT == 'high' else 1

        getattr(self.dut, RESET_NAME, None).value = do_reset
        await ClockCycles( getattr(self.dut, CLOCK_NAME, None), CYCLES4WAIT_RESET )
        getattr(self.dut, RESET_NAME, None).value = undo_reset
        

sys.modules[__name__] = CLASS_NAME
