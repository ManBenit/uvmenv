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
from your_seqitem import Request as YourRequestAlias
"""
from default_seqitem import Request as DefaultSeqitemRequest

# Set the number of items you want to send
NUM_OF_ITEMS = 10

class DefaultSequence(uvm_sequence):
    def __init__(self, name):
        super().__init__(name)
    
    
    async def body(self):
        for _ in range(NUM_OF_ITEMS):
            """ Use the class invoked with your_seqitem module, for example:
            req = YourRequestAlias("req_DefaultSequence")
            """
            req = DefaultSeqitemRequest("req_DefaultSequence")

            await self.start_item(req)
            """ Write the focused or random sequence of stimulus here, example:
            req.randomize()
            req.signal1        = 8
            req.signal2        = 0
            """
            req.randomize()
            await self.finish_item(req)



