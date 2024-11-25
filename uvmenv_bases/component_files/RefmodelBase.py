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




############################
###    COMPONENT FILE    ###
############################

import importlib
import pyuvm
from abc import ABC, ABCMeta, abstractmethod
from pyuvm import uvm_component

UVMComponentMeta = uvm_component.__class__


# Combined metaclass
class CombinedMeta(ABCMeta, UVMComponentMeta):
    pass

class RefModel(ABC, uvm_component, metaclass=CombinedMeta):
    def __init__(self, name, parent, abstract_param='default'):
        uvm_component.__init__(self, name, parent)
        self.abstract_param = abstract_param

    @abstractmethod
    def makeTest(self):
        pass



