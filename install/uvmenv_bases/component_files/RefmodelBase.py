############################
###    COMPONENT FILE    ###
############################

from abc import ABC, ABCMeta, abstractmethod
from pyuvm import uvm_component

UVMComponentMeta = uvm_component.__class__


# Combined metaclass
class UvmMeta(ABCMeta, UVMComponentMeta):
    pass

class RefModel(ABC, uvm_component, metaclass=UvmMeta):
    def __init__(self, name, parent, abstract_param='default'):
        uvm_component.__init__(self, name, parent)
        self.abstract_param = abstract_param

    @abstractmethod
    def makeTest(self):
        pass



