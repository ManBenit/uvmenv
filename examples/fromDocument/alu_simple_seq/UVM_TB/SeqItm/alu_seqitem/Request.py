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
        self.alu_op = 0
        self.a = 0
        self.b = 0



    def randomize(self):
        self.clk = random.randint(0, 1)
        self.reset = random.randint(0, 1)
        self.alu_op = random.randint(0, 15)
        self.a = random.randint(0, 20)
        self.b = random.randint(0, 20)



    def __str__(self):
        item_dict = {
            'clk': self.clk,
            'reset': self.reset,
            'alu_op': self.alu_op,
            'a': self.a,
            'b': self.b
        }
        return f'Transaction request -> {json.dumps(item_dict)}'
        
    
