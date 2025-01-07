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
                'i_a': self.ins['i_a'],
                'i_b': self.ins['i_b'],
                'i_c': self.ins['i_c'],
                'i_d': self.ins['i_d'],
                'i_sel': self.ins['i_sel']
            },
            'response':{
                'o_y': self.outs['o_y']
            }
        }

    def __str__(self):
        try:
            item_dict_int = {
                'request': {
                    'i_a': hex(self.ins['i_a'].integer),
                    'i_b': hex(self.ins['i_b'].integer),
                    'i_c': hex(self.ins['i_c'].integer),
                    'i_d': hex(self.ins['i_d'].integer),
                    'i_sel': hex(self.ins['i_sel'].integer)
                },
                'response':{
                    'o_y': hex(self.outs['o_y'].integer)
                }
            }
            return f'Transaction response -> {json.dumps(item_dict_int)}'
        except ValueError:
            item_dict_int = {
                'request': {
                    'i_a': self.ins['i_a'],
                    'i_b': self.ins['i_b'],
                    'i_c': self.ins['i_c'],
                    'i_d': self.ins['i_d'],
                    'i_sel': self.ins['i_sel']
                },
                'response':{
                    'o_y': self.outs['o_y']
                }
            }
            return f'Transaction response (some \'x\' or \'z\') -> {item_dict_int}'
    