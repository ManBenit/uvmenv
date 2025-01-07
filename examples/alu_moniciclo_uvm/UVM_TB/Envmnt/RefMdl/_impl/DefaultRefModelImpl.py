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
    
    def set_inputs(self, *, ex_aluop_i,ex_datars1_i,ex_datars2_i):
        self.ex_aluop_i = ex_aluop_i
        self.ex_datars1_i = ex_datars1_i
        self.ex_datars2_i = ex_datars2_i

        self.send.write(self._do_with_python())


    def _do_with_python(self): 
        """Write here your model handling""" 
        
        alu_operations = {
            "8": self.ex_datars1_i + self.ex_datars2_i,
            "1": self.ex_datars1_i - self.ex_datars2_i,
            "2": self.ex_datars1_i * self.ex_datars2_i,
            "3": self.ex_datars1_i // self.ex_datars2_i if self.ex_datars2_i != 0 else 0,  # Dividir por cero retorna 0
            "4": self.ex_datars1_i & self.ex_datars2_i,
            "5": self.ex_datars1_i ^ self.ex_datars2_i,
            "6": self.ex_datars1_i | self.ex_datars2_i,
            "7": self.ex_datars1_i << 2,
            "D": self.ex_datars1_i >> self.ex_datars2_i,  # Shift aritmético a la derecha (Python lo maneja con signo)
            "E": self.ex_datars1_i >> self.ex_datars2_i,  # Shift lógico a la derecha (mismo operador en Python)
            "9": 1 if self.ex_datars1_i < self.ex_datars2_i else 0,  # Comparación (slt)
            "A": 1 if self.ex_datars1_i < self.ex_datars2_i else 0   # Comparación unsigned (asume misma lógica)
        }

        self.ex_data_o = alu_operations.get(str(self.ex_aluop_i), 0)

        self.ex_zerof_o = 1 if self.ex_data_o == 0 else 0
        

        # Finally return the result to compare 
        # (assign your correct values)
        return {
            'ex_zerof_o': self.ex_zerof_o,
            'ex_data_o': self.ex_data_o
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
            'ex_zerof_o': None,
            'ex_data_o': None
        }

    

    
          
          

