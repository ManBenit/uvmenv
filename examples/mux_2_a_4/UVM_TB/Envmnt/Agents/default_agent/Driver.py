############################
###    COMPONENT FILE    ###
############################

import importlib
from pyuvm import uvm_driver

from utils import load_config


class Driver(uvm_driver):
    def __init__(self, name, parent):
        super().__init__(name, parent)
    

    def build_phase(self):
        super().build_phase()
        self._import_bfm()

    async def run_phase(self):
        await super().run_phase()
        while True:
            op = await self.seq_item_port.get_next_item()
            self.logger.info(f'Sent to DUT')

            await self.bfm.set(
                i_a = op.i_a,
                i_b = op.i_b,
                i_c = op.i_c,
                i_d = op.i_d,
                i_sel = op.i_sel
            )
            
            self.get_parent().get_parent().refmodel.set_inputs(
                i_a = op.i_a,
                i_b = op.i_b,
                i_c = op.i_c,
                i_d = op.i_d,
                i_sel = op.i_sel
            )

            self.seq_item_port.item_done()

            
    def _import_bfm(self):
        # Get an specific value from .json
        config = load_config('config.json')
        implementation_class = config.uvm_components.itface.bfm_impl

        # Convert value into Python implementation that you want to use
        try:
            module = importlib.import_module(implementation_class)
            clazz = getattr(module, implementation_class)
            self.bfm = clazz()
        except Exception as e:
            self.logger.critical(f'Failed to load BFM implementation: {e}')
            return

    