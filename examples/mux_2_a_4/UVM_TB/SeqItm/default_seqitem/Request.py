############################
###    COMPONENT FILE    ###
############################

import random
import json
from pyuvm import uvm_sequence_item

class Request(uvm_sequence_item):
    def __init__(self, name):
        super().__init__(name)
        self.i_a = 0
        self.i_b = 0
        self.i_c = 0
        self.i_d = 0
        self.i_sel = 0



    def randomize(self):
        self.i_a = random.randint(0, 15)
        self.i_b = random.randint(0, 15)
        self.i_c = random.randint(0, 15)
        self.i_d = random.randint(0, 15)
        self.i_sel = random.randint(0, 3)



    def __str__(self):
        item_dict = {
            'i_a': self.i_a,
            'i_b': self.i_b,
            'i_c': self.i_c,
            'i_d': self.i_d,
            'i_sel': self.i_sel
        }
        return f'Transaction request -> {json.dumps(item_dict)}'
        
    