#################################
###    REPRESENTATIVE FILE    ###
#################################

import paths
import cocotb
from pyuvm import uvm_root

from Test import Test

@cocotb.test()
async def main_test(dut):
	await uvm_root().run_test("Test")

