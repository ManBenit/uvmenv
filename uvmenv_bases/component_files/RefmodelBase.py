############################
###    COMPONENT FILE    ###
############################

import importlib
import pyuvm
from abc import ABC, abstractmethod


class RefModel(ABC): #metaclass=pyuvm.Singleton
	@abstractmethod
	def makeTest(self):
		pass



