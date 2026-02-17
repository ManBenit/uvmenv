#################################
###    REPRESENTATIVE FILE    ###
#################################

import paths
import cocotb
from pyuvm import uvm_root
from colorama import Fore
import pyfiglet
from utils import load_config

from Test import Test

CONFIG = load_config('config.json')

@cocotb.test()
async def main_test(dut):
    print( Fore.BLUE+pyfiglet.figlet_format('UVMEnv')+Fore.RESET )
    print( Fore.YELLOW+pyfiglet.figlet_format(CONFIG.dut_design.top_module)+Fore.RESET )
    await uvm_root().run_test('Test')

