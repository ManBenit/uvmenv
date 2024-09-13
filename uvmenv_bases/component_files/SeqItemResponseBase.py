############################
###    COMPONENT FILE    ###
############################

from pyuvm import uvm_sequence_item
from types import SimpleNamespace
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

	def dict_to_namespace(self, d):
		for key, value in d.items():
			if isinstance(value, dict):
				d[key] = self.dict_to_namespace(value)
		return SimpleNamespace(**d)

	def get_response(self):
		self.do()
		return self.dict_to_namespace(self.item_dict)
	
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
	