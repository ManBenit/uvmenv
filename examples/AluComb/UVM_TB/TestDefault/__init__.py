#################################
###    REPRESENTATIVE FILE    ###
#################################

# ====================
# Python imports
# ====================
import sys
import cocotb
from pyuvm import uvm_test, ConfigDB
from cocotb.triggers import Timer, ClockCycles

# ====================
# UVMEnv imports
# ====================
from utils import config
ISDUTSEQ = config.dut_design.type == 'sequential'



# ============================================================
# Every environments are into Envmnt/ of each Test.
#
# Use: 
#     uvmenv component list env <TestName>
# to show the available environments on your specific Test.
#
# Import the Environments you need, i.e.:
# import EnvDefault
# ============================================================
import EnvDefault

# ============================================================
# Every sequences are into Seqnce/ of each Test.
#
# Use: 
#     uvmenv component list seqce <TestName>
# to show the available sequences on your specific Test.
#
# Import the Sequences you need, i.e.:
# import SeqDefault
# ============================================================
import SeqDefault




class TestDefault(uvm_test):
    def build_phase(self):
        super().build_phase()
        self.dut = cocotb.top
        self.env = EnvDefault('env', self)
        ConfigDB().set(None, 'env.*', 'dut', self.dut)

        # ====================================================
        # Instance here all sequences you need:
        
        # If you will use them INDIVIDUALLY, follow the next:
        # self.seq1 = YourSequence1('YourSequence1')
        # self.seq2 = YourSequence2('YourSequence2')

        # If you will use VIRTUAL SEQUENCER, follow the next:
        # self.vseq1 = YourVirtualSequencer('YourVSeq1', self)
        # self.vseq2 = YourVirtualSequencer('YourVSeq2', self)
        # ====================================================
        self.seq = SeqDefault('SeqDefault')

    async def run_phase(self):
        await super().run_phase()

        self.raise_objection()
        
        if ISDUTSEQ:
            await self.env.agent.driver.bfm.init()
        
        # ====================================================
        # Start here all sequences you need:

        # If you are using them INDIVIDUALLY, follow the next:
        # await self.seq1.start(self.env.agent.seqr)
        # await self.seq2.start(self.env.agent.seqr)
        
        # If you are using VIRTUAL SEQUENCER, follow the next:
        # await self.vseq1.setMyTestVersion1(self.env)
        # await self.vseq2.setMyTestVersion2(self.env)
        # ====================================================
        await self.seq.start(self.env.agent.seqr)

        # ====================================================
        # At the end of objection, 1 extra explicit cycle is required 
        # when DUT is sequential:
        # 1. To wait for the last output.
        # ====================================================
        if ISDUTSEQ:
            await ClockCycles(self.dut.clk, 1)

        self.drop_objection()

sys.modules[__name__] = TestDefault
        

'''
# Use this template for your virtual sequences
class YourVirtualSequencer(uvm_sequencer):
    def __init__(self, name, parent):
        super().__init__(name, parent)

        # Instance here your sequences INDIVIDUALLY, example:
        self.seq1 = YourSequence1('YourSequence1')
        self.seq2 = YourSequence2('YourSequence2')

    # Define your different versions of virtual sequences as methods, example:
    async def setMyTestVersion(self, env):
        await self.seq1.start(env.agent.seqr)
        await self.seq2.start(env.agent.seqr)
'''




