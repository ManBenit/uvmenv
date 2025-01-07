############################
###    COMPONENT FILE    ###
############################

from pyuvm import uvm_sequence_item
from utils import dict_to_namespace
import copy
import json

class Response(uvm_sequence_item):
    def __init__(self, name):
        super().__init__(name)
        self.ins = None
        self.outs = None
    

    def get_transaction(self):
        self._do()
        return dict_to_namespace(self.item_dict)
    
    def copy(self):
        return copy.deepcopy(self)
    

    def _do(self):
        self.item_dict = {
            'request': {
                'num1_i': self.ins['num1_i'],
                'num2_i': self.ins['num2_i']
            },
            'response':{
                'resul_o': self.outs['resul_o']
            }
        }

    def __str__(self):
        try:
            item_dict_int = {
                'request': {
                    'num1_i': hex(self.ins['num1_i'].integer),
                    'num2_i': hex(self.ins['num2_i'].integer)
                },
                'response':{
                    'resul_o': hex(self.outs['resul_o'].integer)
                }
            }
            return f'Transaction response -> {json.dumps(item_dict_int)}'
        except ValueError:
            item_dict_int = {
                'request': {
                    'num1_i': self.ins['num1_i'],
                    'num2_i': self.ins['num2_i']
                },
                'response':{
                    'resul_o': self.outs['resul_o']
                }
            }
            return f'Transaction response (some \'x\' or \'z\') -> {item_dict_int}'
    