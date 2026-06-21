############################
###    COMPONENT FILE    ###
############################

# ====================
# Python imports
# ====================
import sys
from pyuvm import uvm_sequence



# ============================================================
# Every sequence items are into Seqitem/ of each Test.
#
# Use: 
#     uvmenv component list seqitem <TestName>
# to show the available scoreboards on your specific Environment.
#
# Import the Scoreboards you need, i.e.:
# import SitDefault
# ============================================================
import SitDefault

# Define how many times you want to send the sequence
REPEAT_SEQ = 1

class CLASS_NAME(uvm_sequence):
    def __init__(self, name):
        super().__init__(name)
    
    
    async def body(self):
        for _ in range(REPEAT_SEQ):
            transaction = SitDefault('SitDefault')

            await self.start_item(transaction)
            # Write the focused or random stimulus, i.e.:
            # transaction.randomize()
            # transaction.signal1 = 8
            # transaction.signal2 = 0
            transaction.randomize()
            await self.finish_item(transaction)


sys.modules[__name__] = CLASS_NAME

