############################
###    COMPONENT FILE    ###
############################

import importlib
from pyuvm import uvm_driver

from utils import load_config


class Driver(uvm_driver):
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

	async def run_phase(self):
		while True:
			op = await self.seq_item_port.get_next_item()
			await self.bfm.set(
BFM_SET
			)

			self.seq_item_port.item_done()