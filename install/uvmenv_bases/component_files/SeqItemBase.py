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


class CLASS_NAME(uvm_sequence_item):
    def __init__(self, name="alu_item"):
        super().__init__(name)
ATTRIB_SIGNALS


    def randomize(self):
RANDOM_SIGNALS
    
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
THE_INPUTS
        }

    def __response_dict(self):
        try:
            return {
THE_OUTPUTS
            }
        except ValueError as err:
            return {
THE_UNKN_OUTPUTS
            }

    def __get_transaction(self):
        convert_to_hex = lambda d: {k: hex(v) for k, v in d.items()}
        return {
            'request': convert_to_hex(self.__request_dict()),
            'response': convert_to_hex(self.__response_dict())
        }



    def __str__(self):
        return str( self.__get_transaction() )
        

sys.modules[__name__] = CLASS_NAME

