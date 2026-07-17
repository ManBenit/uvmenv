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
        self.clk = 0
        self.reset = 0
        self.alu_op = 0
        self.zero = 0
        self.a = 0
        self.b = 0
        self.result = 0


    def randomize(self):
        self.clk = random.randint(0, 1)
        self.reset = random.randint(0, 1)
        self.alu_op = random.randint(0, 8)
        self.a = random.randint(0, 200)
        self.b = random.randint(0, 200)
    
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
            'clk': self.clk,
            'reset': self.reset,
            'alu_op': self.alu_op,
            'a': self.a,
            'b': self.b
        }

    def __response_dict(self):
        try:
            return {
                'zero': self.zero,
                'result': self.result
            }
        except ValueError as err:
            return {
                'zero': process_unkn_val(self.zero),
                'result': process_unkn_val(self.result)
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

