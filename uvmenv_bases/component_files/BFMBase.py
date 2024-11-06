#################################
###    REPRESENTATIVE FILE    ###
#################################

import importlib
import pyuvm
from abc import ABC, abstractmethod


class BFM(ABC): #metaclass=pyuvm.Singleton
	# Auto -> send the parameters signals to DUT.
	@abstractmethod	
	def set(self):
		pass

	# Auto -> receive and encapsulate signals from DUT.
	@abstractmethod
	def get(self):
		pass

	# Use init, generelly, to start clock when design is sequencial.
	@abstractmethod
	def init(self):
		pass

	# Use reset, generelly, to restart DUT when design is sequencial.
	@abstractmethod
	def reset(self):
		pass




