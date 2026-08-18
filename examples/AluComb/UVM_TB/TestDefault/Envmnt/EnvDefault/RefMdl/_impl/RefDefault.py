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

def sra(a: int, b: int, width: int) -> int:
    ''' Shift Right Logical(SRA) emulating hardware.
    
    :param a: Operand to shift.
    :param b: Number of positions.
    :param width: Bit length (ex. 8, 16, 32, 64).
    :return: Unsigned int of 'width' bits.
    '''
    # 1. Create mask
    mask = (1 << width) - 1                # Ex. Para 32 bits: 0xFFFFFFFF
    msb_mask = 1 << (width - 1)           # Ex. Para 32 bits: 0x80000000
    
    # 2. Define a constraint to make a correct shift
    shift_max_mask = (width - 1).bit_length()
    shift_amount = b & ((1 << shift_max_mask) - 1)
    
    # 3. Ensure operand inside bit range
    val_a = a & mask
    
    # 4. Convert to signed native int when result negative
    if val_a & msb_mask:
        val_a -= (1 << width)
        
    # 5. Make arithmetic shift
    return (val_a >> shift_amount) & mask

class RefDefault(RefModel):
    def __init__(self, name, parent, abstract_param='default'):
        super().__init__(name, parent, abstract_param)
        self.__transaction = None
        # Uncomment the next two lines if you will use a verilated reference model
        ###self.__sim = ctypes.CDLL('../RTLRef/SOME_RTL_MODEL_DIRECTORY/libmodel.so')
        ###self.__sim.init()


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

        alu_operations = {
            '0': self.__transaction.a + self.__transaction.b,                      # ADD
            '1': self.__transaction.a - self.__transaction.b,                      # SUB
            '2': self.__transaction.a & self.__transaction.b,                      # AND
            '3': self.__transaction.a | self.__transaction.b,                      # OR
            '4': self.__transaction.a ^ self.__transaction.b,                      # XOR
            '5': self.__transaction.a << (self.__transaction.b & 0x1F),            # SLL (shift left logical)
            '6': (self.__transaction.a & 0xFFFFFFFF) >> (self.__transaction.b & 0x1F),  # SRL (shift right logical)
            '7': sra(self.__transaction.a, self.__transaction.b, 32),  # SRA
            '8': 1 if self.__transaction.a < self.__transaction.b else 0           # SLT
        }

        result = alu_operations.get(str(self.__transaction.alu_op), 0)

        zero = 1 if result == 0 else 0

        # All you need to analyse is to assign results to transaction signals, i.e.:
        # self.__transaction.SIGNAL = to_bin_repr(SIGNAL, SIGNAL_SIZE)
        # Where SIGNAL_SIZE is auto written by UVMEnv.
        print(f'[RefDefault] ALU Operation: {self.__transaction.alu_op}, A: {self.__transaction.a}, B: {self.__transaction.b}')
        print(f'[RefDefault] Result: {result}, Zero: {zero}')
        self.__transaction.zero = to_bin_repr(zero, 1)
        self.__transaction.result = to_bin_repr(result, 32)


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
        self.__transaction.zero = to_bin_repr(0000000000000000, 1)
        self.__transaction.result = to_bin_repr(0000000000000000, 32)
    

    
sys.modules[__name__] = RefDefault
          

