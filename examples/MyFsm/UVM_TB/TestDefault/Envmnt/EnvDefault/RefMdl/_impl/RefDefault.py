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
from utils import to_bin_repr
from RefModel import RefModel



class RefDefault(RefModel):
    def __init__(self, name, parent, abstract_param='default'):
        super().__init__(name, parent, abstract_param)
        self.__transaction = None
        # Uncomment the next two lines if you will use a verilated reference model
        rmoddir = next( p for p in sys.path if p.endswith('RefMdl') )
        self.__sim = ctypes.CDLL(f'{rmoddir}/RTLRef/MyFsm/libmodel.so')
        self.__sim.init()
        self.fsm = MyFSM()


    def build_phase(self):
        super().build_phase()
        self.send = uvm_analysis_port('send_refmodel', self)

    def set(self, transaction: uvm_sequence_item):
        self.__transaction = copy.copy(transaction)

        # Use __do_with_python or __do_with_verilator
        self.__do_with_verilator()
        self.send.write(self.__transaction)


    def __do_with_python(self): 
        ''' Write here your Python model handling '''

        o_y, o_state = self.fsm.evaluate(self.__transaction.i_x)

        # All you need to analyse is to assign results to transaction signals, i.e.:
        # self.__transaction.SIGNAL = to_bin_repr(SIGNAL, SIGNAL_SIZE)
        # Where SIGNAL_SIZE is auto written by UVMEnv.
        self.__transaction.o_y = to_bin_repr(o_y, 1)
        self.__transaction.o_state = to_bin_repr(o_state, 2)


    def __do_with_verilator(self):
        ''' Write here your Verilated model handling '''

        # Write here your model handling, for example:
        self.__sim.set_i_x(self.__transaction.i_x)
        o_y = self.__sim.get_o_y()
        o_state = self.__sim.get_o_state()
        
        # ====================================================
        # Send signals to verilated reference model and get the results like this:
        # self.__sim.set_a(self.a)
        # self.__sim.set_b(self.b)
        # sum = self.__sim.get_sum()
        # ====================================================

        # All you need to analyse is to assign results to transaction signals, i.e.:
        # self.__transaction.SIGNAL = to_bin_repr(CALCULATED_VALUE, SIGNAL_SIZE)
        # Where SIGNAL_SIZE is auto written by UVMEnv.
        self.__transaction.o_y = to_bin_repr(o_y, 1)
        self.__transaction.o_state = to_bin_repr(o_state, 2)
    

    
sys.modules[__name__] = RefDefault
          



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
          
          


