############################
###    COMPONENT FILE    ###
############################

import cocotb
from cocotb.triggers import Timer

from BFM import BFM

class CLASS_NAME(BFM):
	def __init__(self):
		self.dut = cocotb.top
		

	async def set(self, *, PARAMETERS):
INIT_VALUES
		# Time for stimulus
		await Timer(1, units='ns')

	async def get(self):
		ins = {
GET_INS
		}

		outs = {
GET_OUTS
		}
		
		return (ins, outs)

	def init(self):
		"""use this method for init reset, clock, etc"""
		print()

