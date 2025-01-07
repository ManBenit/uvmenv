############################
###    COMPONENT FILE    ###
############################

import random
import json
from pyuvm import uvm_sequence_item

class Request(uvm_sequence_item):
    def __init__(self, name):
        super().__init__(name)
        self.clk_i = 0
        self.rst_ni = 0
        self.rd_i = 0
        self.wr_i = 0
        self.command_i = 0
        self.data_i = 0
        self.address_i = 0



    def randomize(self):
        self.clk_i = random.randint(0, 1)
        self.rst_ni = random.randint(0, 1)
        self.rd_i = random.randint(0, 1)
        self.wr_i = random.randint(0, 1)
        self.command_i = random.randint(0, 255)
        #self.data_i = random.randint(0, 18446744073709551615)
        #self.address_i = random.randint(0, 18446744073709551615)
        self.data_i = random.randint(0, 500)
        self.address_i = random.randint(0, 100)



    def __str__(self):
        item_dict = {
            'clk_i': self.clk_i,
            'rst_ni': self.rst_ni,
            'rd_i': self.rd_i,
            'wr_i': self.wr_i,
            'command_i': self.command_i,
            'data_i': self.data_i,
            'address_i': self.address_i
        }
        return f'Transaction request -> {json.dumps(item_dict)}'
        
    