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
                'ex_aluop_i': self.ins['ex_aluop_i'],
                'ex_datars1_i': self.ins['ex_datars1_i'],
                'ex_datars2_i': self.ins['ex_datars2_i']
            },
            'response':{
                'ex_zerof_o': self.outs['ex_zerof_o'],
                'ex_data_o': self.outs['ex_data_o']
            }
        }

    def __str__(self):
        try:
            item_dict_int = {
                'request': {
                    'ex_aluop_i': hex(self.ins['ex_aluop_i'].integer),
                    'ex_datars1_i': hex(self.ins['ex_datars1_i'].integer),
                    'ex_datars2_i': hex(self.ins['ex_datars2_i'].integer)
                },
                'response':{
                    'ex_zerof_o': hex(self.outs['ex_zerof_o'].integer),
                    'ex_data_o': hex(self.outs['ex_data_o'].integer)
                }
            }
            return f'Transaction response -> {json.dumps(item_dict_int)}'
        except ValueError:
            item_dict_int = {
                'request': {
                    'ex_aluop_i': self.ins['ex_aluop_i'],
                    'ex_datars1_i': self.ins['ex_datars1_i'],
                    'ex_datars2_i': self.ins['ex_datars2_i']
                },
                'response':{
                    'ex_zerof_o': self.outs['ex_zerof_o'],
                    'ex_data_o': self.outs['ex_data_o']
                }
            }
            return f'Transaction response (some \'x\' or \'z\') -> {item_dict_int}'
    