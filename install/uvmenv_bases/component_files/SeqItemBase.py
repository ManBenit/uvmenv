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



class SitDefault(uvm_sequence_item):
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



    def __request_dict(self):
        return {
THE_INPUTS
        }

    def __response_dict(self):
        return {
THE_OUTPUTS
        }

    def __get_transaction(self):
        return {
            'request': self.__request_dict(),
            'response': self.__response_dict()
        }



    def __str__(self):
        return str( self.__get_transaction() )
        

sys.modules[__name__] = SitDefault

