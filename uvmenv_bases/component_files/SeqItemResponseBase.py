############################
###    COMPONENT FILE    ###
############################

from pyuvm import uvm_sequence_item
from utils import dict_to_namespace
import copy

class Response(uvm_sequence_item):
    def __init__(self, name):
        super().__init__(name)
        self.ins = None
        self.outs = None
    
    def do(self):
        self.item_dict = {
            'request': {
THE_INPUTS
            },
            'response':{
THE_OUTPUTS
            }
        }

    def get_response(self):
        self.do()
        return dict_to_namespace(self.item_dict)
    
    def copy(self):
        return copy.deepcopy(self)
    
    def __str__(self):
        item_dict_int = {
            'request': {
THE_STR_INPUTS
            },
            'response':{
THE_STR_OUTPUTS
            }
        }
        return f'Transaction response -> {item_dict_int}'
    