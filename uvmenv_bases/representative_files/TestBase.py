#################################
###    REPRESENTATIVE FILE    ###
#################################

import cocotb
from pyuvm import uvm_test, ConfigDB

from Environment import Environment
"""
Import here all sequences that you consider necesary.
All sequences are into Seqnce directory.
Use: 
	uvmenv --show-sequences
to show the available sequences on your project.
Import the Sequence from your Module.

Example:
"""
#from YourSequence import Sequence



class Test(uvm_test):
	def build_phase(self):
		self.env = Environment("env", self)
		ConfigDB().set(None, "env.*", "dut", cocotb.top)

	async def run_phase(self):
		"""
		Write here instances of your sequences. 
		Example:
		"""
		#seq = Sequence("seq")
		

		self.raise_objection()
		"""
		Start here all sequences you consider, all of then asyncronous. 
		Example:
		"""
		#await seq.start(self.env.agent.seqr)
		
		self.drop_objection()

		