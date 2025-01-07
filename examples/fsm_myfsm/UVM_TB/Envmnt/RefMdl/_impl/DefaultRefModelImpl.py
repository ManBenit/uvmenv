############################
###    COMPONENT FILE    ###
############################

import ctypes # Used if you define a _do_with_verilator()
from RefModel import RefModel
from pyuvm import uvm_analysis_port


class DefaultRefModelImpl(RefModel):
    def __init__(self, name, parent, abstract_param='default'):
        import os
        super().__init__(name, parent, abstract_param)
        # Uncomment the next line if you will use a verilated reference model
        self.sim = ctypes.CDLL(f'{os.getcwd()}/UVM_TB/Envmnt/RefMdl/RTLRef/fsm_myfsm/libmodel.so')
        self.sim.init()
        self.fsm = MyFSM()


    def build_phase(self):
        super().build_phase()
        self.send = uvm_analysis_port('send_refmodel', self)


    def makeTest(self):
        return self._do_with_python()
    
    def set_inputs(self, *, i_clk,i_rst_n,i_x):
        self.i_clk = i_clk
        self.i_rst_n = i_rst_n
        self.i_x = i_x

        #self.send.write(self._do_with_python())
        self.send.write(self._do_with_verilator())


    def _do_with_python(self): 
        """Write here your Python model handling""" 
            
        o_y, o_state = self.fsm.evaluate(self.i_x)

        # Finally return the result to compare 
        # (assign your correct values)
        return {
            'o_y': o_y,
            'o_state': o_state
        }

    def _do_with_verilator(self):
        """Write here your Verilated model handling"""

        # Write here your model handling, for example:
        self.sim.set_i_x(self.i_x)
        o_y = self.sim.get_o_y()
        o_state = self.sim.get_o_state()

        # Finally return the result to compare 
        # (assign your correct values)
        return {
            'o_y': o_y,
            'o_state': o_state
        }

    



class MyFSM:
    from enum import Enum
    class State(Enum):
        S0 = 0b00
        S1 = 0b01
        S2 = 0b10
        S3 = 0b11

    def __init__(self):
        # Estado inicial
        self.state = MyFSM.State.S0
    
    def evaluate(self, i_x):
        """
        Evalúa la máquina de estados con la entrada actual.
        
        :param i_x: Entrada de la FSM (booleano o 0/1)
        :return: Una tupla con la salida o_y y el estado actual (o_state)
        """
        # Salida lógica
        bit0 = (self.state.value >> 0) & 1  # Primer bit (bit menos significativo)
        bit1 = (self.state.value >> 1) & 1  # Segundo bit

        o_y = (bit0 & bit1) & i_x  # state == S3 & i_x
        
        # Actualizar el estado según la lógica de transición
        if self.state == MyFSM.State.S0:
            self.state = MyFSM.State.S1 if i_x else MyFSM.State.S0
        elif self.state == MyFSM.State.S1:
            self.state = MyFSM.State.S2 if i_x else MyFSM.State.S0
        elif self.state == MyFSM.State.S2:
            self.state = MyFSM.State.S3 if i_x else MyFSM.State.S0
        elif self.state == MyFSM.State.S3:
            self.state = MyFSM.State.S0
        
        # Salida del estado actual
        o_state = self.state.value
        
        return o_y, o_state
          
          

