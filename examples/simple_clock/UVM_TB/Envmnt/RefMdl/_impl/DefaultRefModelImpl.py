############################
###    COMPONENT FILE    ###
############################

from RefModel import RefModel
from pyuvm import uvm_analysis_port


class DefaultRefModelImpl(RefModel):
    def __init__(self, name, parent, abstract_param='default'):
        super().__init__(name, parent, abstract_param)


    def build_phase(self):
        super().build_phase()
        self.send = uvm_analysis_port('send_refmodel', self)


    def makeTest(self):
        return self._do_with_python()
    
    def set_inputs(self, *, clk,reset):
        self.clk = clk
        self.reset = reset

        self.send.write(self._do_with_python())


    def _do_with_python(self): 
        """Write here your model handling""" 
              

        # Finally return the result to compare 
        # (assign your correct values)
        return {
            'count': None
        }

    def _do_with_verilator(self):
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
            'count': None
        }

    

    
          
          

