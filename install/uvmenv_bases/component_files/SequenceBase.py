############################
###    COMPONENT FILE    ###
############################

import sys
from pyuvm import uvm_sequence

"""
Import all sequece item responses from SeqItm directory, with an specific alias for each.
Use: 
    uvmenv component list seqitem
to show the available sequence items on your project.
Example:
import sit_default as SitDefault
"""
import sit_default as SitDefault

# Set the number of items you want to send
NUM_OF_ITEMS = 1

class CLASS_NAME(uvm_sequence):
    def __init__(self, name):
        super().__init__(name)
    
    
    async def body(self):
        for _ in range(NUM_OF_ITEMS):
            """ Use the class invoked with your_seqitem module, for example:
            req = YourRequestAlias('req_CLASS_NAME')
            """
            req = SitDefault('req_SeqDefault')

            await self.start_item(req.request)
            """ Write the focused or random sequence of stimulus here, example:
            req.randomize()
            req.signal1        = 8
            req.signal2        = 0
            """
            req.request.randomize()
            await self.finish_item(req.request)


sys.modules[__name__] = CLASS_NAME

