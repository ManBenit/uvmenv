#################################
###    REPRESENTATIVE FILE    ###
#################################

# ====================
# Python imports
# ====================
import cocotb
from pyuvm import uvm_root, uvm_component
from colorama import Fore
import pyfiglet

# ====================
# UVMEnv imports
# ====================
import paths
paths.loadProjectPaths()

import pyuvm
from utils import config
from UVMEnvReport import report



# ============================================================
# Every tests are into UVM_TB/.
#
# Use: 
#     uvmenv component list test
# to show the available Tests.
#
# Import the Tests you need, i.e.:
# import TestDefault
# ============================================================
import TestDefault

print( Fore.BLUE+pyfiglet.figlet_format('UVMEnv')+Fore.RESET )
print( Fore.YELLOW+pyfiglet.figlet_format(config.dut_design.top_module)+Fore.RESET )


@cocotb.test()
async def default_test(dut):
    # This is a fake test, you can delete it when you create your own tests.
    #await do_fake_test()

    # Await for some specific test
    await uvm_root().run_test('TestDefault')









# ===============================================================
# Little replication of UVM test using UVMEnv reporting mechanism
# ===============================================================
class ExampleTest(pyuvm.uvm_test):
    def build_phase(self):
        # Al instanciarlo aquí como hijo del Test, 
        # pyuvm llamará automáticamente a su build_phase
        self.comp = UVMComponent('exampleComponent', self)

    async def run_phase(self):
        self.raise_objection()
        # Aquí puedes poner lógica adicional o simplemente esperar
        report.write('Running example run_phase', self, pyuvm.INFO)
        self.drop_objection()

class UVMComponent(uvm_component):
    def __init__(self, name, parent):
        super().__init__(name, parent)

    def build_phase(self):
        super().build_phase()
        # Component build code here
        report.write(f'Report example', self, pyuvm.INFO)



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


# ===================================================
# Artificial DUT done with Python for using fake_test
# ===================================================
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



