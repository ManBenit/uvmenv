############################
###    COMPONENT FILE    ###
############################

import ctypes # Used if you define a _do_with_verilator()
from RefModel import RefModel
from pyuvm import uvm_analysis_port


class ALURefModelImpl(RefModel):
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
    
    def set_inputs(self, *, clk,reset,alu_op,a,b):
        self.clk = clk
        self.reset = reset
        self.alu_op = alu_op
        self.a = a
        self.b = b

        self.send.write(self._do_with_python())


    def _do_with_python(self): 
        """Write here your Python model handling""" 
              
        alu_operations = {
            "0": self.a + self.b,                      # ADD
            "1": self.a - self.b,                      # SUB
            "2": self.a & self.b,                      # AND
            "3": self.a | self.b,                      # OR
            "4": self.a ^ self.b,                      # XOR
            "5": self.a << (self.b & 0x1F),            # SLL (shift left logical)
            "6": (self.a & 0xFFFFFFFF) >> (self.b & 0x1F),  # SRL (shift right logical)
            "7": (self.a >> (self.b & 0x1F)) if self.a >= 0 else (self.a + 0x100000000) >> (self.b & 0x1F),  # SRA
            "8": 1 if self.a < self.b else 0           # SLT
                }

        result = alu_operations.get(str(self.alu_op), 0)

        zero = 1 if result == 0 else 0

        return { 
            'zero': zero,
            'result': result
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
            'zero': None,
            'result': None
        }

    

    
          
          

