############################
###    COMPONENT FILE    ###
############################

from pyuvm import uvm_scoreboard, uvm_tlm_analysis_fifo, uvm_get_port, uvm_sequence_item
from utils import dict_to_namespace, report


"""
Import all sequece item responses from SeqItm directory, with an specific alias for each.
Use: 
    uvmenv --show-seqitems
to show the available sequence items on your project.
Example:
from your_seqitem import Response as YourResponseAlias
"""
from default_seqitem import Response as DefaultSeqitem


class CLASS_NAME(uvm_scoreboard):
    def __init__(self, name, parent):
        super().__init__(name, parent)


    def build_phase(self):
        super().build_phase()
        self.dut_result_fifo = uvm_tlm_analysis_fifo('dut_result_fifo', self)
        self.refmodel_result_fifo = uvm_tlm_analysis_fifo('refmodel_result_fifo', self)

        self.dut_result_get_port = uvm_get_port('dut_result_get_port', self)
        self.refmodel_result_get_port = uvm_get_port('refmodel_result_get_port', self)
        
    def connect_phase(self):
        # To correct TLM connection
        self.dut_result_get_port.connect(self.dut_result_fifo.get_export)
        self.refmodel_result_get_port.connect(self.refmodel_result_fifo.get_export)

        # To easy connecting since Environment
        self.dut_result_export = self.dut_result_fifo.analysis_export
        self.refmodel_result_export= self.refmodel_result_fifo.analysis_export

    def check_phase(self):
        super().check_phase()

        while self.dut_result_get_port.can_get() and self.refmodel_result_get_port.can_get():
            success_dut, tr_dut = self.dut_result_get_port.try_get()
            success_rmod, tr_rmod = self.refmodel_result_get_port.try_get()

            if not success_dut or not success_rmod:
                self.logger.critical(f'Fail getting transaction info: (dut:{success_dut},rmod:{success_rmod})')
            else:
                self.logger.info('Analyzing TLM on check_phase')
                # They return a binary representation, compatible with integer comparison.
                request_dut = tr_dut.get_transaction().request
                response_dut = tr_dut.get_transaction().response

                # It returns integer representation
                # [Reference model has not request]
                response_rmod = dict_to_namespace(tr_rmod)


                """
                # Specular validation for possible negative values
                if(response_dut.POSSIBLE_NEGATIVE_SIGNAL.signed_integer < 0):
                    response_dut.POSSIBLE_NEGATIVE_SIGNAL=response_dut.POSSIBLE_NEGATIVE_SIGNAL.signed_integer
                """


                """
                # This is an scorboarding proposal:

                ## Save conditions
                condition_1 = response_dut.result_signal_1 == response_rmod.result_signal_1
                condition_N = response_dut.result_signal_2 == response_rmod.result_signal_2

                # Make assertions
                assert condition_1, f'TEST ERROR result_signal_1 dut({response_dut.result_signal_1.integer}), rmod({response_rmod.result_signal_1})'
                assert condition_N, f'TEST ERROR result_signal_N dut({response_dut.ex_data_o.result_signal_N}), rmod({response_rmod.result_signal_N})'

                # Save on report file if necessary (watch util.py for help)
                if condition_1:
                    report.write(f'[TEST PASSED] {tr_dut}', self, pyuvm.INFO)
                else:
                    report.write(f'[TEST FAILED] {tr_dut}', self, pyuvm.ERROR)
                """                

        self.logger.info('Final general scoreboarding')

    def report_phase(self):
        super().report_phase()

        """You can generate report actions here"""


    def write(self, t):
        if(isinstance(t, uvm_sequence_item)):
            self.tr = t.copy()
        else:
            self.tr = dict_to_namespace(t)

        self.logger.info(f'Received from Monitor: {self.tr}')

        """
        Analyze here each transaction with DUT if necessary. Recommended to use assertions.
        assert <condition>, 'Error message'
        """
        

        
            
