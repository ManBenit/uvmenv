############################
###    COMPONENT FILE    ###
############################

import pyuvm
from queue import Queue
from pyuvm import uvm_scoreboard, uvm_tlm_analysis_fifo, uvm_get_port, uvm_sequence_item
from utils import dict_to_namespace, load_config
from UVMEnvReport import report
from cocotb.binary import BinaryValue

# You can define the maximum size for auxiliar queues (ensure is more than total of sequences).
# (thery are used only when verifying secuential designs)
NUM_SEQUENCES=10

CONFIG = load_config('config.json')
SEQUENTIAL_DUT = True if CONFIG.dut_design.type == 'sequential' else False


class DefaultScoreboard(uvm_scoreboard):
    def __init__(self, name, parent):
        super().__init__(name, parent)
        # Auxiliar queues when DUT is sequential
        self.reqdut_queue = Queue(maxsize=NUM_SEQUENCES)
        self.resdut_queue = Queue(maxsize=NUM_SEQUENCES)
        self.resrmod_queue = Queue(maxsize=NUM_SEQUENCES)
        self.enable_scoreboarding = False if CONFIG.dut_design.type == 'sequential' else True


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
                
                # Unblock the next line if DUT is sequential
                ###self.resrmod_queue.put(response_rmod)

                # Unlock the next block if DUT is sequential
                """
                if request_dut.YOUR_RESET_SIGNAL == 0 and self.enable_scoreboarding == False:
                    self.enable_scoreboarding = True
                    self.resdut_queue.get()
                """                

                if self.enable_scoreboarding:  
                    try:
                        # Unlock the next two lines (writing of aux queues) when DUT is sequential.
                        ##response_rmod = self.resrmod_queue.get()
                        ##response_dut = self.resdut_queue.get()

                        """
                        # Specular validation for possible negative values
                        if(response_dut.POSSIBLE_NEGATIVE_SIGNAL.signed_integer < 0):
                            response_dut.POSSIBLE_NEGATIVE_SIGNAL=response_dut.POSSIBLE_NEGATIVE_SIGNAL.signed_integer
                        """

                        """
                        # This is an scorboarding proposal:

                        ## Save conditions
                        condition_1 = response_dut.result_signal_1 == response_rmod.result_signal_1
                        condition_N = response_dut.result_signal_N == response_rmod.result_signal_N

                        # Make assertions
                        assert condition_1, f'TEST FAILED result_signal_1 dut({hex(response_dut.result_signal_1)}), rmod({hex(response_rmod.result_signal_1)})'
                        assert condition_N, f'TEST FAILED result_signal_N dut({hex(response_dut.result_signal_N)}), rmod({hex(response_rmod.result_signal_N)})'

                        # Save on report file if necessary (watch Misces/UVMEnvReport.py for help)
                        if condition_1:
                            report.write(message=f'[TEST PASSED] {tr_dut}', component=self, level=pyuvm.INFO)
                        else:
                            report.write(message=f'[TEST FAILED] {tr_dut}', component=self, level=pyuvm.ERROR)
                        """
                    except ValueError as ex:
                        self.logger.error(f'{ex}')
                        pass

        self.logger.info('Final general scoreboarding')

        # Uncomment this block when DUT is sequential
        """
        # Get the last result (after last cycle) to be able to compare with reference model.
        # This process is made checking the aux queues.
        # (for now, is repeated code)
        while not self.resdut_queue.empty() and not self.resrmod_queue.empty():
            response_rmod = self.resrmod_queue.get()
            response_dut = self.resdut_queue.get()

            # Specular validation for possible negative values
            #if(response_dut.POSSIBLE_NEGATIVE_SIGNAL.signed_integer < 0):
            #    response_dut.POSSIBLE_NEGATIVE_SIGNAL=response_dut.POSSIBLE_NEGATIVE_SIGNAL.signed_integer
            
            ## Save conditions
            condition_1 = response_dut.result_signal_1 == response_rmod.result_signal_1
            condition_N = response_dut.result_signal_N == response_rmod.result_signal_N

            # Make assertions
            assert condition_1, f'TEST FAILED result_signal_1 dut({hex(response_dut.result_signal_1)}), rmod({hex(response_rmod.result_signal_1)})'
            assert condition_N, f'TEST FAILED result_signal_N dut({hex(response_dut.result_signal_N)}), rmod({hex(response_rmod.result_signal_N)})'

            # Save on report file if necessary (watch Misces/UVMEnvReport.py for help)
            if condition_1:
                report.write(message=f'[TEST PASSED] {tr_dut}', component=self, level=pyuvm.INFO)
            else:
                report.write(message=f'[TEST FAILED] {tr_dut}', component=self, level=pyuvm.ERROR)
        """

    def report_phase(self):
        super().report_phase()

        """You can generate report actions here"""


    def write(self, t):
        if(isinstance(t, uvm_sequence_item)):
            self.tr = t.copy()
            # Uncomment the next two lines if DUT is sequential
            ##if self.tr.get_transaction().request.YOUR_RESET_SIGNAL == 0:
            ##    self.resdut_queue.put(self.tr.get_transaction().response)

        else:
            self.tr = dict_to_namespace(t)

        self.logger.info(f'Received from Monitor in WRITE')

        """
        Analyze here each transaction with DUT if necessary. Recommended to use assertions.
        assert <condition>, 'Error message'
        """
        

        
            
