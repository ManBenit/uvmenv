############################
###    COMPONENT FILE    ###
############################

import random
import json
from pyuvm import uvm_sequence_item

class Request(uvm_sequence_item):
    def __init__(self, name):
        super().__init__(name)
        self.clk = 0
        self.reset = 0



    def randomize(self):
        self.clk = random.randint(0, 1)
        self.reset = random.randint(0, 1)



    def __str__(self):
        item_dict = {
            'clk': self.clk,
            'reset': self.reset
        }
        return f'Transaction request -> {json.dumps(item_dict)}'
        
    