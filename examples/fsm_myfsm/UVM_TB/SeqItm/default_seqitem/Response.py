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
                'i_clk': self.ins['i_clk'],
                'i_rst_n': self.ins['i_rst_n'],
                'i_x': self.ins['i_x']
            },
            'response':{
                'o_y': self.outs['o_y'],
                'o_state': self.outs['o_state']
            }
        }

    def __str__(self):
        try:
            item_dict_int = {
                'request': {
                    'i_clk': hex(self.ins['i_clk'].integer),
                    'i_rst_n': hex(self.ins['i_rst_n'].integer),
                    'i_x': hex(self.ins['i_x'].integer)
                },
                'response':{
                    'o_y': hex(self.outs['o_y'].integer),
                    'o_state': hex(self.outs['o_state'].integer)
                }
            }
            return f'Transaction response -> {json.dumps(item_dict_int)}'
        except ValueError:
            item_dict_int = {
                'request': {
                    'i_clk': self.ins['i_clk'],
                    'i_rst_n': self.ins['i_rst_n'],
                    'i_x': self.ins['i_x']
                },
                'response':{
                    'o_y': self.outs['o_y'],
                    'o_state': self.outs['o_state']
                }
            }
            return f'Transaction response (some \'x\' or \'z\') -> {item_dict_int}'
    