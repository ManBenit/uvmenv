############################
###    COMPONENT FILE    ###
############################

import random
import json
from pyuvm import uvm_sequence_item

class Request(uvm_sequence_item):
    def __init__(self, name):
        super().__init__(name)
ATTRIB_SIGNALS


    def randomize(self):
RANDOM_SIGNALS


    def __str__(self):
        item_dict = {
ATTRIB_STR_SIGNALS
        }
        return f'Transaction request -> {json.dumps(item_dict)}'
        
    