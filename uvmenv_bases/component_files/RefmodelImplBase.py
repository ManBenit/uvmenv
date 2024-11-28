############################
###    COMPONENT FILE    ###
############################

from RefModel import RefModel
from pyuvm import uvm_analysis_port


class CLASS_NAME(RefModel):
    def __init__(self, name, parent, abstract_param='default'):
        super().__init__(name, parent, abstract_param)


    def set_inputs(self, *, PARAMETERS):
PARAMS_ASSIGNS

        self.send.write(self.do_with_python())

    def do_with_python(self): 
        """Write here your model handling""" 
              

        # Finally return the result to compare 
        # (assign your correct values)
        return {
RETURNS
        }

    def do_with_verilator(self):
        import ctypes
        sim = ctypes.CDLL('./RTLRef/some_rtl_model/obj_dir/libmodel.so')

        sim.init()
        sim.reset()
              
        """
        Write here your model handling, for example:
        sim.set_a()
        sim.set_b()
        sim.eval()
        """

        sim.finalize()


        # Finally return the result to compare 
        # (assign your correct values)
        return {
RETURNS
        }

    def makeTest(self):
        return self.do_with_python()

    def build_phase(self):
        super().build_phase()
        self.send = uvm_analysis_port('send_refmodel', self)
          
          

