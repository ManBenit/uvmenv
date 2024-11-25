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
        self.dut_result_fifo = uvm_tlm_analysis_fifo("dut_result_fifo", self)

    def import_refmdl(self):
        # Get an specific value from .json
        config = load_config('config.json')
        implementation_class = config.uvm_components.refmdl.refmdl_impl

        # Convert value into Python implementation that you want to use
        try:
            module = importlib.import_module(implementation_class)
            clazz = getattr(module, implementation_class)
            self.refmodel = clazz('reference_model', self)
        except Exception as e:
            self.logger.critical(f"Failed to load RefModel implementation: {e}")
            return
        
    def connect_phase(self):
        super().connect_phase()
        self.result_export = self.dut_result_fifo.analysis_export
    
    
    def write(self, t):
        self.tr = t.copy()
        self.logger.info(f'Received from Monitor: {self.tr}')
        
        tr_response = self.tr.get_response()


        # Here are all inputs that you need to send to make test into reference model:
        refm_result = self.refmodel.makeTest(
SIGNALS_REFM_RESULT
        )

        """
        You can use assertions (RECOMMENDED, failures will be showed and process will be aborted):
        assert tr_response.response.sum.integer == refm_result.sum, 'DUT({}) != MODEL({})'.format(tr_response.response.YOUR_RESULT_SIGNAL.integer, refm_result.YOUR_RESULT_SIGNAL)


        You can use conditionals (failures will be showed but process will finished always successfully):
        if tr_response.response.YOUR_RESULT_SIGNAL.integer == refm_result.YOUR_RESULT_SIGNAL:
            self.logger.info(f"TEST PASSED")
        else:
            self.logger.critical(
                'TEST FAILED -> DUT response ({}) != MODEL response ({})'
                .format(tr_response.response.YOUR_RESULT_SIGNAL.integer, refm_result.YOUR_RESULT_SIGNAL)
            )


            ## If you want to stop running when an error happens, use these lines:
            from cocotb.result import TestFailure
            raise TestFailure("Check log messages for error details")

            ## If you want to finish test successfully only reporting errors, use these lines:
            import cocotb
            cocotb.regression_manager.failures+=1


        NOTE: If you are uing signed signals, use signed_integer for your RESULT_SIGNAL if necessary.
        """
        
            