############################
###    COMPONENT FILE    ###
############################

import random
import json
from pyuvm import uvm_sequence_item

class Request(uvm_sequence_item):
    def __init__(self, name):
        super().__init__(name)
        self.i_clk = 0
        self.i_rst_n = 0
        self.i_x = 0



    def randomize(self):
        self.i_clk = random.randint(0, 1)
        self.i_rst_n = random.randint(0, 1)
        self.i_x = random.randint(0, 1)



    def __str__(self):
        item_dict = {
            'i_clk': self.i_clk,
            'i_rst_n': self.i_rst_n,
            'i_x': self.i_x
        }
        return f'Transaction request -> {json.dumps(item_dict)}'
        
    