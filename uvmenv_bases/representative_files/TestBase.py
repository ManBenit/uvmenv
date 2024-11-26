#################################
###    REPRESENTATIVE FILE    ###
#################################

import cocotb
from pyuvm import uvm_test, ConfigDB
# Also import uvm_sequencer from pyuvm if you will use virtual sequencer


from Environment import Environment
"""
Import here all sequences that you consider necesary.
All sequences are into Seqnce directory.
Use: 
    uvmenv --show-sequences
to show the available sequences on your project.
Import the Sequence from your Module.

Example:
from YourSequence import YourSequence
"""
from DefaultSequence import DefaultSequence



class Test(uvm_test):
    def build_phase(self):
        super().build_phase()
        self.env = Environment("env", self)
        ConfigDB().set(None, "env.*", "dut", cocotb.top)

        """
        Instance here all sequences you need:
        
        If you will use them INDIVIDUALLY, follow the next:
        self.seq1 = YourSequence1('YourSequence1')
        self.seq2 = YourSequence2('YourSequence2')

        If you will use VIRTUAL SEQUENCER, follow the next:
        self.vseq1 = YourVirtualSequencer('YourVSeq1', self)
        self.vseq2 = YourVirtualSequencer('YourVSeq2', self)
        """
        self.seq = DefaultSequence('DefaultSequence')


    async def run_phase(self):
        await super().run_phase()
        # Use the next line if you are verifying a sequential design:
        #self.env.agent.driver.bfm.init()

        self.raise_objection()
        #await self.env.agent.driver.bfm.reset()
        
        """
        Start here all sequences you need:

        If you are using them INDIVIDUALLY, follow the next:
        await self.seq1.start(self.env.agent.seqr)
        await self.seq2.start(self.env.agent.seqr)
        
        If you are using VIRTUAL SEQUENCER, follow the next:
        await self.vseq1.setMyTestVersion1(self.env)
        await self.vseq2.setMyTestVersion2(self.env)
        """
        await self.seq.start(self.env.agent.seqr)
        self.drop_objection()

        

"""
# Use this template for your virtual sequences
class YourVirtualSequencer(uvm_sequencer):
    def __init__(self, name, parent):
        super().__init__(name, parent)

        # Instance here your sequences INDIVIDUALLY, example:
        self.seq1 = YourSequence1("YourSequence1")
        self.seq2 = YourSequence2("YourSequence2")

    # Define your different versions of virtual sequences as methods, example:
    async def setMyTestVersion(self, env):
        await self.seq1.start(env.agent.seqr)
        await self.seq2.start(env.agent.seqr)
"""




