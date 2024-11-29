############################
###    COMPONENT FILE    ###
############################


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
from your_seqitem import Response as YourResponseAlias
"""
from default_seqitem import Response as DefaultSeqitem


class Monitor(uvm_monitor):
    def __init__(self, name, parent):
        super().__init__(name, parent)


    def build_phase(self):
        super().build_phase()
        self._import_bfm()
        self.send = uvm_analysis_port('send_monitor', self)

    async def run_phase(self):
        await super().run_phase()
        while True:
            # Time for waiting Monitor response from DUT
            await Timer(1, units='ns')  
            
            """ Use the class invoked with your_seqitem module, for example:
            transaction = YourResponseAlias("monitor_item")
            """
            transaction = DefaultSeqitem('monitor_item')

            inputs, outputs = await self.bfm.get()
            transaction.ins = inputs
            transaction.outs = outputs

            self.logger.info(f'Received from DUT: {transaction}')

            self.send.write(transaction)


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

    
