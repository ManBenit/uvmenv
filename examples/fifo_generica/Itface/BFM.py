############################
###    COMPONENT FILE    ###
############################

from abc import ABC, ABCMeta, abstractmethod

class SingletonMeta(ABCMeta, type):
    _instances = {}
    def __call__(cls, *args, **kwargs):
        if cls not in cls._instances:
            cls._instances[cls] = super().__call__(*args, **kwargs)
        return cls._instances[cls]


class BFM(ABC, metaclass=SingletonMeta):
    # Auto -> send the parameters signals to DUT.
    @abstractmethod    
    def set(self):
        pass

    # Auto -> receive and encapsulate signals from DUT.
    @abstractmethod
    def get(self):
        pass

    # Use init, generelly, to start clock when DUT is sequencial.
    @abstractmethod
    def init(self):
        pass

    # Use reset, generelly, to restart DUT when DUT is sequencial.
    @abstractmethod
    def reset(self):
        pass




