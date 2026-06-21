############################
###    COMPONENT FILE    ###
############################

# ====================
# Python imports
# ====================
import sys
import copy
import ctypes # Used if you define a __do_with_verilator()
from pyuvm import uvm_analysis_port, uvm_sequence_item

# ====================
# UVMEnv imports
# ====================
from RefModel import RefModel



class CLASS_NAME(RefModel):
    def __init__(self, name, parent, abstract_param='default'):
        super().__init__(name, parent, abstract_param)
        self.__transaction = None
        # Uncomment the next two lines if you will use a verilated reference model
        ###self.__sim = ctypes.CDLL('../RTLRef/SOME_RTL_MODEL_DIRECTORY/libmodel.so')
        ###self.__sim.init()


    def build_phase(self):
        super().build_phase()
        self.send = uvm_analysis_port('send_refmodel', self)

    def set(self, transaction: uvm_sequence_item):
        self.__transaction = copy.copy(transaction)

        # Use __do_with_python or __do_with_verilator
        self.__do_with_python()
        self.send.write(self.__transaction)


    def __do_with_python(self): 
        ''' Write here your Python model handling '''

        # All you need to analyse is to assign results to transaction signals, i.e.:
TRANSACTION_OUTS


    def __do_with_verilator(self):
        ''' Write here your Verilated model handling '''
        
        # ====================================================
        # Send signals to verilated reference model and get the results like this:
        # self.__sim.set_a(self.a)
        # self.__sim.set_b(self.b)
        # sum = self.__sim.get_sum()
        # ====================================================

        # All you need to analyse is to assign results to transaction signals, i.e.:
TRANSACTION_OUTS
    

    
sys.modules[__name__] = CLASS_NAME
          

