############################
###    COMPONENT FILE    ###
############################

import ctypes # Used if you define a _do_with_verilator()
from RefModel import RefModel
from pyuvm import uvm_analysis_port


class CLASS_NAME(RefModel):
    def __init__(self, name, parent, abstract_param='default'):
        super().__init__(name, parent, abstract_param)
        # Uncomment the next two lines if you will use a verilated reference model
        ###self.sim = ctypes.CDLL('../RTLRef/SOME_RTL_MODEL_DIRECTORY/libmodel.so')
        ###self.sim.init()


    def build_phase(self):
        super().build_phase()
        self.send = uvm_analysis_port('send_refmodel', self)


    def makeTest(self):
        return self._do_with_python()
    
    def set_inputs(self, *, PARAMETERS):
PARAMS_ASSIGNS

        self.send.write(self._do_with_python())


    def _do_with_python(self): 
        """Write here your Python model handling""" 
              

        # Finally return the result to compare 
        # (assign your correct values)
        return {
RETURNS
        }

    def _do_with_verilator(self):
        """Write here your Verilated model handling"""
        
        """
        For example:
        self.sim.set_a(self.a)
        self.sim.set_b(self.b)
        sum = self.sim.get_sum()
        """

        # Finally return the result to compare 
        # (assign your correct values)
        return {
RETURNS
        }

    

    
          
          

