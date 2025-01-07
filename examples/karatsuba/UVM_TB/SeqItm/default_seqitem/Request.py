############################
###    COMPONENT FILE    ###
############################

import random
import json
from pyuvm import uvm_sequence_item

class Request(uvm_sequence_item):
    def __init__(self, name):
        super().__init__(name)
        self.num1_i = 0
        self.num2_i = 0



    def randomize(self):
        self.num1_i = random.randint(0, 4294967295)
        self.num2_i = random.randint(0, 4294967295)



    def __str__(self):
        item_dict = {
            'num1_i': self.num1_i,
            'num2_i': self.num2_i
        }
        return f'Transaction request -> {json.dumps(item_dict)}'
        
    