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
"""
#from your_seqitem import Request as SpecificNameForUse

# Set the numebr of items you want to send
NUM_OF_ITEMS = 1

class CLASS_NAME(uvm_sequence):
	def __init__(self, name="seqnce_CLASS_NAME"):
		super().__init__(name)
	
	async def body(self):
		for _ in range(NUM_OF_ITEMS):
			req = SpecificNameForUse("req")
			await self.start_item(req)
			req.randomize()
			await self.finish_item(req)

