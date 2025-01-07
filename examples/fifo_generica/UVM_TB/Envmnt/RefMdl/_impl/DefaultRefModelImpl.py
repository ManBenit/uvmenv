############################
###    COMPONENT FILE    ###
############################

import ctypes # Used if you define a _do_with_verilator()
from RefModel import RefModel
from pyuvm import uvm_analysis_port

from queue import Queue

class DefaultRefModelImpl(RefModel):
    def __init__(self, name, parent, abstract_param='default'):
        super().__init__(name, parent, abstract_param)
        # Uncomment the next two lines if you will use a verilated reference model
        ###self.sim = ctypes.CDLL('../RTLRef/SOME_RTL_MODEL_DIRECTORY/libmodel.so')
        ###self.sim.init()
        depth = 16
        self.data_queue = Queue(maxsize=depth)
        self.address_queue = Queue(maxsize=depth)
        self.command_queue = Queue(maxsize=depth)


    def build_phase(self):
        super().build_phase()
        self.send = uvm_analysis_port('send_refmodel', self)


    def makeTest(self):
        return self._do_with_python()
    
    def set_inputs(self, *, clk_i,rst_ni,rd_i,wr_i,command_i,data_i,address_i):
        self.clk_i = clk_i
        self.rst_ni = rst_ni
        self.rd_i = rd_i
        self.wr_i = wr_i
        self.command_i = command_i
        self.data_i = data_i
        self.address_i = address_i

        self.send.write(self._do_with_python())


    def _do_with_python(self): 
        """Write here your Python model handling""" 
        
        data_o, address_o, command_o, den, empty, full = 0,0,0,0,0,0
        # Crear una FIFO de profundidad 16
        #self.fifo = FIFO(depth=16)

        full = self.data_queue.full()
        empty = self.data_queue.empty()
        if self.wr_i == 1:
            if not self.data_queue.full():
                self.data_queue.put(self.data_i)
                self.address_queue.put(self.address_i)
                self.command_queue.put(self.command_i)
        if self.rd_i == 1:
            if not self.data_queue.empty():
                data_o = self.data_queue.get()
                address_o = self.address_queue.get()
                command_o = self.command_queue.get()
        
        # Finally return the result to compare 
        # (assign your correct values)
        return {
            'command_o': command_o,
            'den': den,
            'empty': empty,
            'full': full,
            'data_o': data_o,
            'address_o': address_o
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
            'command_o': None,
            'den': None,
            'empty': None,
            'full': None,
            'data_o': None,
            'address_o': None
        }

    
class FIFO:
    def __init__(self, depth):
        self.depth = depth
        self.data_queue = Queue(maxsize=depth)
        self.address_queue = Queue(maxsize=depth)
        self.command_queue = Queue(maxsize=depth)

    def write(self, data_i, address_i, command_i):
        """Escribe en la FIFO si no está llena"""
        if not self.data_queue.full():
            self.data_queue.put(data_i)
            self.address_queue.put(address_i)
            self.command_queue.put(command_i)
            return True  # Indica que se realizó la escritura
        else:
            return False  # FIFO llena

    def read(self):
        """Lee de la FIFO si no está vacía"""
        if not self.data_queue.empty():
            data_o = self.data_queue.get()
            address_o = self.address_queue.get()
            command_o = self.command_queue.get()
            return data_o, address_o, command_o, True  # Datos leídos con éxito
        else:
            return None, None, None, False  # FIFO vacía

    def is_empty(self):
        """Indica si la FIFO está vacía"""
        return self.data_queue.empty()

    def is_full(self):
        """Indica si la FIFO está llena"""
        return self.data_queue.full()

    def status(self):
        """Devuelve el estado actual de la FIFO"""
        return {
            "empty": self.is_empty(),
            "full": self.is_full(),
            "current_size": self.data_queue.qsize()
        }


    
          
          

