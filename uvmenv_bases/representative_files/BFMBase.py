#################################
###    REPRESENTATIVE FILE    ###
#################################

import importlib
import pyuvm
from abc import ABC, abstractmethod


class BFM(ABC): #metaclass=pyuvm.Singleton
	@abstractmethod	
	def set(self):
		pass

	@abstractmethod
	def get(self):
		pass

	@abstractmethod
	def init(self):
		pass




