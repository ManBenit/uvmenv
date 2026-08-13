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
        self.ex_aluop_i = 0
        self.ex_zerof_o = 0
        self.ex_datars1_i = 0
        self.ex_datars2_i = 0
        self.ex_data_o = 0


    def randomize(self):
        self.ex_aluop_i = random.randint(1, 15)
        self.ex_datars1_i = random.randint(0, 200)
        self.ex_datars2_i = random.randint(0, 200)
    
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
            'ex_aluop_i': self.ex_aluop_i,
            'ex_datars1_i': self.ex_datars1_i,
            'ex_datars2_i': self.ex_datars2_i
        }

    def __response_dict(self):
        try:
            return {
                'ex_zerof_o': self.ex_zerof_o,
                'ex_data_o': self.ex_data_o
            }
        except ValueError as err:
            return {
                'ex_zerof_o': process_unkn_val(self.ex_zerof_o),
                'ex_data_o': process_unkn_val(self.ex_data_o)
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

