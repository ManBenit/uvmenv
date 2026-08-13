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
        self.i_clk = 0
        self.i_rst_n = 0
        self.i_x = 0
        self.o_y = 0
        self.o_state = 0


    def randomize(self):
        self.i_clk = random.randint(0, 1)
        self.i_rst_n = random.randint(0, 1)
        self.i_x = random.randint(0, 1)
    
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
            'i_clk': self.i_clk,
            'i_rst_n': self.i_rst_n,
            'i_x': self.i_x
        }

    def __response_dict(self):
        try:
            return {
                'o_y': self.o_y,
                'o_state': self.o_state
            }
        except ValueError as err:
            return {
                'o_y': process_unkn_val(self.o_y),
                'o_state': process_unkn_val(self.o_state)
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

