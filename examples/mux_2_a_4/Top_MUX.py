#################################
###    REPRESENTATIVE FILE    ###
#################################

import paths
import cocotb
import pyuvm
from pyuvm import uvm_root

from Test import Test

@cocotb.test()
async def main_test(dut):
    """################## This is a UVMEnv verification project. ##################"""
    await uvm_root().run_test("Test")

