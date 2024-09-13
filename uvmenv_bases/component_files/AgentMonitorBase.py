############################
###    COMPONENT FILE    ###
############################

import sys
import importlib
from pyuvm import uvm_monitor, uvm_analysis_port
from cocotb.triggers import Timer

from utils import load_config

"""
Import all sequece item responses from SeqItm directory, with an specific alias for each.
Use: 
	uvmenv --show-seqitems
to show the available sequence items on your project.
Example:
"""
#from your_seqitem import Response as YourAlias



class Monitor(uvm_monitor):
	def __init__(self, name, parent):
		super().__init__(name, parent)

	def import_bfm(self):
		config = load_config('config.json')

		# Configure the BFM implementation that you want to use
		implementation_class = config.uvm_components.itface.bfm_impl
		module_name, class_name = implementation_class.rsplit(".", 1)

		try:
			module = importlib.import_module(module_name)
			clazz = getattr(module, class_name)
			self.bfm = clazz()
		except Exception as e:
			self.logger.critical(f"Failed to load BFM implementation: {e}")
			return

	def build_phase(self):
		self.import_bfm()
		self.send = uvm_analysis_port("send", self)

	async def run_phase(self):
		while True:
			await Timer(1, units='ns')  # Simulate monitoring delay
			
			""" Use the class invoked with myseqitem module """
			transaction = YourAlias("monitor_item")

			inputs, outputs = await self.bfm.get()
			transaction.ins = inputs
			transaction.outs = outputs
			self.send.write(transaction)
