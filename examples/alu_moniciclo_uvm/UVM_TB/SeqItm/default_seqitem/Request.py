############################
###    COMPONENT FILE    ###
############################

import random
import json
from pyuvm import uvm_sequence_item

class Request(uvm_sequence_item):
    def __init__(self, name):
        super().__init__(name)
        self.ex_aluop_i = 0
        self.ex_datars1_i = 0
        self.ex_datars2_i = 0



    def randomize(self):
        op_values = [1,2,3,4,5,6,7,8,9,13,14]
        self.ex_aluop_i = random.choice(op_values)
        self.ex_datars1_i = random.randint(0, 100)
        self.ex_datars2_i = random.randint(0, 100)



    def __str__(self):
        item_dict = {
            'ex_aluop_i': self.ex_aluop_i,
            'ex_datars1_i': self.ex_datars1_i,
            'ex_datars2_i': self.ex_datars2_i
        }
        return f'Transaction request -> {json.dumps(item_dict)}'
        
    