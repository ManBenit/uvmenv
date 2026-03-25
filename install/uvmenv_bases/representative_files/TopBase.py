#################################
###    REPRESENTATIVE FILE    ###
#################################

import paths
import cocotb
from pyuvm import uvm_root
from colorama import Fore
import pyfiglet
from utils import load_config

# Import your tests when you create someone, for example the next line:
#from Test import Test

CONFIG = load_config('config.json')

@cocotb.test()
async def default_test(dut):
    print( Fore.BLUE+pyfiglet.figlet_format('UVMEnv')+Fore.RESET )
    print( Fore.YELLOW+pyfiglet.figlet_format(CONFIG.dut_design.top_module)+Fore.RESET )

    # This is a fake test, you can delete it when you create your own tests.
    await do_fake_test()

    # Await for some specific test
    #await uvm_root().run_test('Test')









# =====================
# Fake test with Cocotb
# =====================
async def do_fake_test():
    from cocotb.triggers import Timer
    dut = FakeDUT()

    cocotb.log.info('Loading default fake DUT')

    # Fake test case 1
    dut.a.value = 2
    dut.b.value = 3
    dut.eval()
    await Timer(1, units='ns')

    assert dut.result.value == 5, f'Expected 5, obtained {dut.result.value}'
    cocotb.log.info('Test 1 OK')

    # Fake test case 2
    dut.a.value = 10
    dut.b.value = -4
    dut.eval()
    await Timer(1, units='ns')

    assert dut.result.value == 6, f'Expected 6, obtained {dut.result.value}'
    cocotb.log.info('Test 2 OK')

    cocotb.log.info('Fake test completed successfully')


# ===============================
# Artificial DUT done with Python
# ===============================
class FakeSignal:
    def __init__(self, value=0):
        self.value = value

class FakeDUT:
    def __init__(self):
        self.a = FakeSignal(0)
        self.b = FakeSignal(0)
        self.result = FakeSignal(0)

    def eval(self):
        self.result.value = self.a.value + self.b.value

