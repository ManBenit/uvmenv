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
                'alu_op': self.ins['alu_op'],
                'a': self.ins['a'],
                'b': self.ins['b']
            },
            'response':{
                'zero': self.outs['zero'],
                'result': self.outs['result']
            }
        }

    def __str__(self):
        try:
            item_dict_int = {
                'request': {
                    'alu_op': hex(self.ins['alu_op'].integer),
                    'a': hex(self.ins['a'].integer),
                    'b': hex(self.ins['b'].integer)
                },
                'response':{
                    'zero': hex(self.outs['zero'].integer),
                    'result': hex(self.outs['result'].integer)
                }
            }
            return f'Transaction response -> {json.dumps(item_dict_int)}'
        except ValueError:
            item_dict_int = {
                'request': {
                    'alu_op': self.ins['alu_op'],
                    'a': self.ins['a'],
                    'b': self.ins['b']
                },
                'response':{
                    'zero': self.outs['zero'],
                    'result': self.outs['result']
                }
            }
            return f'Transaction response (some \'x\' or \'z\') -> {item_dict_int}'
    