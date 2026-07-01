############################
###    COMPONENT FILE    ###
############################

# ====================
# Python imports
# ====================
import importlib
from pyuvm import uvm_driver

# ====================
# UVMEnv imports
# ====================
from utils import config


class Driver(uvm_driver):
    def __init__(self, name, parent):
        super().__init__(name, parent)
    

    def build_phase(self):
        super().build_phase()
        self.__import_bfm()

    async def run_phase(self):
        await super().run_phase()
        while True:
            transaction = await self.seq_item_port.get_next_item()

            # Send transaction to DUT
            await self.bfm.set(transaction)
            
            self.seq_item_port.item_done()

            
    def __import_bfm(self):
        # Get an specific value from .json
        implementation_class = config.uvm_components.itface.bfm_impl

        # Convert value into Python implementation that you want to use
        try:
            module = importlib.import_module(implementation_class)
            self.bfm = module()
        except Exception as e:
            self.logger.critical(f'Failed to load BFM implementation: {e}')
            return

    