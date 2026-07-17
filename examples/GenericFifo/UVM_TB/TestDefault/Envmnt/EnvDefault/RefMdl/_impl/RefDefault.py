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
from collections import deque
from queue import Queue

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
        ###self.__sim = ctypes.CDLL('../RTLRef/SOME_RTL_MODEL_DIRECTORY/libmodel.so')
        ###self.__sim.init()
        depth = 16
        self.data_queue = Queue(maxsize=depth)
        self.address_queue = Queue(maxsize=depth)
        self.command_queue = Queue(maxsize=depth)
        self.fifo_model = FIFO(16)


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

        data_o, address_o, command_o, den, empty, full = 0,0,0,0,0,0

        full = self.fifo_model.is_full()
        empty = self.fifo_model.is_empty()

        # print('========================#######==========')
        # print(self.__transaction.rd_i)
        # print(self.__transaction.wr_i)
        # print(self.__transaction.command_i)
        # print(self.__transaction.data_i)
        # print(self.__transaction.address_i)
        if self.__transaction.wr_i == 1:
            success = self.fifo_model.write(
                self.__transaction.data_i,
                self.__transaction.address_i,
                self.__transaction.command_i
            )
            
        if self.__transaction.rd_i == 1:
            data_o, address_o, command_o, success = self.fifo_model.read()

        # All you need to analyse is to assign results to transaction signals, i.e.:
        # self.__transaction.SIGNAL = to_bin_repr(SIGNAL, SIGNAL_SIZE)
        # Where SIGNAL_SIZE is auto written by UVMEnv.
        if data_o is not None and address_o is not None and command_o is not None and full is not None and empty is not None and den is not None:
            self.__transaction.command_o = to_bin_repr(command_o, 8)
            self.__transaction.den = to_bin_repr(den, 1)
            self.__transaction.empty = to_bin_repr(empty, 1)
            self.__transaction.full = to_bin_repr(full, 1)
            self.__transaction.data_o = to_bin_repr(data_o, 64)
            self.__transaction.address_o = to_bin_repr(address_o, 64)


    def __do_with_verilator(self):
        ''' Write here your Verilated model handling '''
        
        # ====================================================
        # Send signals to verilated reference model and get the results like this:
        # self.__sim.set_a(self.a)
        # self.__sim.set_b(self.b)
        # sum = self.__sim.get_sum()
        # ====================================================

        # All you need to analyse is to assign results to transaction signals, i.e.:
        # self.__transaction.SIGNAL = to_bin_repr(CALCULATED_VALUE, SIGNAL_SIZE)
        # Where SIGNAL_SIZE is auto written by UVMEnv.
        self.__transaction.command_o = to_bin_repr(0000000000000000, 8)
        self.__transaction.den = to_bin_repr(0000000000000000, 1)
        self.__transaction.empty = to_bin_repr(0000000000000000, 1)
        self.__transaction.full = to_bin_repr(0000000000000000, 1)
        self.__transaction.data_o = to_bin_repr(0000000000000000, 64)
        self.__transaction.address_o = to_bin_repr(0000000000000000, 64)
    

    
sys.modules[__name__] = RefDefault
          

class FIFO:
    def __init__(self, depth):
        self.depth = depth
        # Inicializamos tres deques independientes con tamaño máximo
        self.data_queue = deque(maxlen=depth)
        self.address_queue = deque(maxlen=depth)
        self.command_queue = deque(maxlen=depth)

    def write(self, data_i, address_i, command_i):
        """Escribe en la FIFO si no está llena"""
        if not self.is_full():
            self.data_queue.append(data_i)
            self.address_queue.append(address_i)
            self.command_queue.append(command_i)
            return True  # Indica que se realizó la escritura
        else:
            return False  # FIFO llena

    def read(self):
        """Lee de la FIFO si no está vacía"""
        if not self.is_empty():
            data_o = self.data_queue.popleft()
            address_o = self.address_queue.popleft()
            command_o = self.command_queue.popleft()
            return data_o, address_o, command_o, True  # Datos leídos con éxito
        else:
            return None, None, None, False  # FIFO vacía

    def is_empty(self):
        """Indica si la FIFO está vacía"""
        return len(self.data_queue) == 0

    def is_full(self):
        """Indica si la FIFO está llena"""
        return len(self.data_queue) == self.depth

    def status(self):
        """Devuelve el estado actual de la FIFO"""
        return {
            "empty": self.is_empty(),
            "full": self.is_full(),
            "current_size": len(self.data_queue)
        }
    