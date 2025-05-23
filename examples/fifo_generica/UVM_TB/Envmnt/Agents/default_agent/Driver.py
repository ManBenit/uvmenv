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
                clk_i = op.clk_i,
                rst_ni = op.rst_ni,
                rd_i = op.rd_i,
                wr_i = op.wr_i,
                command_i = op.command_i,
                data_i = op.data_i,
                address_i = op.address_i
            )
            
            self.get_parent().get_parent().refmodel.set_inputs(
                clk_i = op.clk_i,
                rst_ni = op.rst_ni,
                rd_i = op.rd_i,
                wr_i = op.wr_i,
                command_i = op.command_i,
                data_i = op.data_i,
                address_i = op.address_i
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

    