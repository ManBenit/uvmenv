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

    def make_test_python(self): 
        """Write here your model handling""" 
              

        # Finally return the result to compare 
        # (assign your correct values)
        return {
RETURNS
        }

    def make_test_verilator(self):
        sim_init()
        sim.reset()
              
        """
        Write here your model handling, for example:
        sim.set_a()
        sim.set_b()
        sim.eval()
        """

        sim_finalize()


        # Finally return the result to compare 
        # (assign your correct values)
        return {
RETURNS
        }

    def build_phase(self):
        super().build_phase()
        self.send = uvm_analysis_port("send_refmodel", self)
          
    def extract_phase(self):
        super().extract_phase()
        transaction_ref = self.makeTest()
        self.send.write(transaction_ref)


 