############################
###    COMPONENT FILE    ###
############################

import random
import json
from pyuvm import uvm_sequence_item

class Request(uvm_sequence_item):
    def __init__(self, name):
        super().__init__(name)
        self.alu_op = 0
        self.a = 0
        self.b = 0



    def randomize(self):
        self.alu_op = random.randint(0, 8)
        self.a = random.randint(0, 100)
        self.b = random.randint(0, 100)



    def __str__(self):
        item_dict = {
            'alu_op': self.alu_op,
            'a': self.a,
            'b': self.b
        }
        return f'Transaction request -> {json.dumps(item_dict)}'
        
    