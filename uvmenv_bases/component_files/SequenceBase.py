############################
###    COMPONENT FILE    ###
############################

from pyuvm import uvm_sequence

"""
Import all request from a seqence item, with an specific alias for each.
Use: 
	uvmenv --show-seqitems
to show the available sequence items on your project.
Example:
from your_seqitem import SequenceItem as YourSequenceItemAlias
"""

# Set the number of items you want to send
NUM_OF_ITEMS = 1

class CLASS_NAME(uvm_sequence):
	def __init__(self, name="seqnce_CLASS_NAME"):
		super().__init__(name)
		""" Use the class invoked with your_seqitem module, for example:
		self.tr = YourSequenceItemAlias()
		"""
	
	async def body(self):
		for _ in range(NUM_OF_ITEMS):
			await self.start_item(self.tr)
			""" Write the focused or random sequence of stimulus here, example:
			self.tr.randomize()
			self.tr.signal1		= 8
			self.tr.signal2		= 0
			"""
			await self.finish_item(self.tr)



