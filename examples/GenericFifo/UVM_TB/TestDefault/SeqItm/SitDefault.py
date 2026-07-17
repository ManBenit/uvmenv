############################
###    COMPONENT FILE    ###
############################

# ====================
# Python imports
# ====================
import sys
import random
import json
from pyuvm import uvm_sequence_item

# ====================
# UVMEnv imports
# ====================
from utils import process_unkn_val


class SitDefault(uvm_sequence_item):
    def __init__(self, name="alu_item"):
        super().__init__(name)
        self.clk_i = 0
        self.rst_ni = 0
        self.rd_i = 0
        self.wr_i = 0
        self.command_i = 0
        self.command_o = 0
        self.den = 0
        self.empty = 0
        self.full = 0
        self.data_i = 0
        self.address_i = 0
        self.data_o = 0
        self.address_o = 0


    def randomize(self):
        self.clk_i = random.randint(0, 1)
        self.rst_ni = random.randint(0, 1)
        self.rd_i = random.randint(0, 1)
        self.wr_i = random.randint(0, 1)
        self.command_i = random.randint(0, 255)
        self.data_i = random.randint(0, 500)
        self.address_i = random.randint(0, 100)
    
    def pretty_print(self):
        print(json.dumps(
            self.__get_transaction(),
            indent=4,
            default=str
        ))

    def get_ins_only(self):
        return self.__request_dict()
    
    def get_outs_only(self):
        return self.__response_dict()



    def __request_dict(self):
        return {
            'clk_i': self.clk_i,
            'rst_ni': self.rst_ni,
            'rd_i': self.rd_i,
            'wr_i': self.wr_i,
            'command_i': self.command_i,
            'data_i': self.data_i,
            'address_i': self.address_i
        }

    def __response_dict(self):
        try:
            return {
                'command_o': self.command_o,
                'den': self.den,
                'empty': self.empty,
                'full': self.full,
                'data_o': self.data_o,
                'address_o': self.address_o
            }
        except ValueError as err:
            return {
                'command_o': process_unkn_val(self.command_o),
                'den': process_unkn_val(self.den),
                'empty': process_unkn_val(self.empty),
                'full': process_unkn_val(self.full),
                'data_o': process_unkn_val(self.data_o),
                'address_o': process_unkn_val(self.address_o)
            }

    def __get_transaction(self):
        convert_to_hex = lambda d: {k: hex(v) for k, v in d.items()}
        return {
            'request': convert_to_hex(self.__request_dict()),
            'response': convert_to_hex(self.__response_dict())
        }



    def __str__(self):
        return str( self.__get_transaction() )
        

sys.modules[__name__] = SitDefault

