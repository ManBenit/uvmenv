############################
###    COMPONENT FILE    ###
############################

import importlib

from pyuvm import uvm_scoreboard, uvm_tlm_analysis_fifo
from utils import load_config


"""
Import all sequece item responses from SeqItm directory, with an specific alias for each.
Use: 
	uvmenv --show-seqitems
to show the available sequence items on your project.
Example:
from your_seqitem import Response as YourResponseAlias
"""


class CLASS_NAME(uvm_scoreboard):
	def __init__(self, name, parent):
		super().__init__(name, parent)
		""" Instance your transaction, for example:
		self.tr = YourResponseAlias("tr")
		"""
		self.tr=None

	def build_phase(self):
		super().build_phase()
		self.import_refmdl()
		self.result_fifo = uvm_tlm_analysis_fifo("result_fifo", self)

	def import_refmdl(self):
		config = load_config('config.json')

		implementation_class = config.uvm_components.refmdl.refmdl_impl

		try:
			module = importlib.import_module(implementation_class)
			clazz = getattr(module, implementation_class)
			self.refmodel = clazz()
		except Exception as e:
			self.logger.critical(f"Failed to load RefModel implementation: {e}")
			return
		
	def connect_phase(self):
		self.result_export = self.result_fifo.analysis_export
	
	
	def write(self, t):
		self.tr = t.copy()
		
		tr_response = self.tr.get_response()


		# Here are all inputs that you need to send to make test into reference model:
		refm_result = self.refmodel.makeTest(
SIGNALS_REFM_RESULT
		)

		if tr_response.response.YOUR_RESULT_SIGNAL.signed_integer == refm_result:
			self.logger.info(f"[SCB] TEST PASSED")
		else:
			self.logger.critical(
				"[SCB] TEST FAILED -> DUT response ({}) != MODEL response ({})"
				.format(tr_response.response.YOUR_RESULT_SIGNAL.signed_integer, refm_result)
			)

			"""If you want to stop running when an error happens, use these lines"""
			#from cocotb.result import TestFailure
			#raise TestFailure("Check log messages for error details")

			"""If you want to finish test succesfully only reporting errors, use these lines"""		
			#import cocotb
			#cocotb.regression_manager.failures+=1
		