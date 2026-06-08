############################
###    COMPONENT FILE    ###
############################

from utils import dict_to_namespace
import copy
import json

class Response:
    def __init__(self):
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
THE_INPUTS
            },
            'response':{
THE_OUTPUTS
            }
        }

    def __str__(self):
        try:
            item_dict_int = {
                'request': {
THE_STR_INPUTS
                },
                'response':{
THE_STR_OUTPUTS
                }
            }
            return f'Transaction response -> {json.dumps(item_dict_int)}'
        except ValueError:
            item_dict_int = {
                'request': {
THE_STR_NOINT_INPUTS
                },
                'response':{
THE_STR_NOINT_OUTPUTS
                }
            }
            return f'Transaction response (some \'x\' or \'z\') -> {item_dict_int}'
    