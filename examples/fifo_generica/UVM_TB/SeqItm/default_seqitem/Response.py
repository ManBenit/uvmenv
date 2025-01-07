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
                'clk_i': self.ins['clk_i'],
                'rst_ni': self.ins['rst_ni'],
                'rd_i': self.ins['rd_i'],
                'wr_i': self.ins['wr_i'],
                'command_i': self.ins['command_i'],
                'data_i': self.ins['data_i'],
                'address_i': self.ins['address_i']
            },
            'response':{
                'command_o': self.outs['command_o'],
                'den': self.outs['den'],
                'empty': self.outs['empty'],
                'full': self.outs['full'],
                'data_o': self.outs['data_o'],
                'address_o': self.outs['address_o']
            }
        }

    def __str__(self):
        try:
            item_dict_int = {
                'request': {
                    'clk_i': hex(self.ins['clk_i'].integer),
                    'rst_ni': hex(self.ins['rst_ni'].integer),
                    'rd_i': hex(self.ins['rd_i'].integer),
                    'wr_i': hex(self.ins['wr_i'].integer),
                    'command_i': hex(self.ins['command_i'].integer),
                    'data_i': hex(self.ins['data_i'].integer),
                    'address_i': hex(self.ins['address_i'].integer)
                },
                'response':{
                    'command_o': hex(self.outs['command_o'].integer),
                    'den': hex(self.outs['den'].integer),
                    'empty': hex(self.outs['empty'].integer),
                    'full': hex(self.outs['full'].integer),
                    'data_o': hex(self.outs['data_o'].integer),
                    'address_o': hex(self.outs['address_o'].integer)
                }
            }
            return f'Transaction response -> {json.dumps(item_dict_int)}'
        except ValueError:
            item_dict_int = {
                'request': {
                    'clk_i': self.ins['clk_i'],
                    'rst_ni': self.ins['rst_ni'],
                    'rd_i': self.ins['rd_i'],
                    'wr_i': self.ins['wr_i'],
                    'command_i': self.ins['command_i'],
                    'data_i': self.ins['data_i'],
                    'address_i': self.ins['address_i']
                },
                'response':{
                    'command_o': self.outs['command_o'],
                    'den': self.outs['den'],
                    'empty': self.outs['empty'],
                    'full': self.outs['full'],
                    'data_o': self.outs['data_o'],
                    'address_o': self.outs['address_o']
                }
            }
            return f'Transaction response (some \'x\' or \'z\') -> {item_dict_int}'
    