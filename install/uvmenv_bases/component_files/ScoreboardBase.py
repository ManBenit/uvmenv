############################
###    COMPONENT FILE    ###
############################

# ====================
# Python imports
# ====================
import sys
import pyuvm
from queue import Queue
from pyuvm import uvm_scoreboard, uvm_tlm_analysis_fifo, uvm_get_port, uvm_sequence_item

# ====================
# UVMEnv imports
# ====================
from SignalsReader import get_dut_signames
from UVMEnvReport import report
from utils import config
ISDUTSEQ = config.dut_design.type == 'sequential'


# You can define the maximum size for auxiliar queues (ensure is more than total of sequences).
# (thery are used only when verifying sequential designs)
# (Maybe next deprecation)
NUM_SEQUENCES=10


class CLASS_NAME(uvm_scoreboard):
    def __init__(self, name, parent):
        super().__init__(name, parent)
        # Auxiliar queues when DUT is sequential (Maybe next deprecation)
        self.reqdut_queue = Queue(maxsize=NUM_SEQUENCES)
        self.resdut_queue = Queue(maxsize=NUM_SEQUENCES)
        self.resrmod_queue = Queue(maxsize=NUM_SEQUENCES)
        self.enable_scoreboarding = not ISDUTSEQ


    def build_phase(self):
        super().build_phase()
        # Create UVM FIFOs (they includes its exports)
        self.dut_result_fifo = uvm_tlm_analysis_fifo('dut_result_fifo', self)
        self.refmodel_result_fifo = uvm_tlm_analysis_fifo('refmodel_result_fifo', self)

        # Create ports for FIFOs
        self.dut_result_get_port = uvm_get_port('dut_result_get_port', self)
        self.refmodel_result_get_port = uvm_get_port('refmodel_result_get_port', self)
        
    def connect_phase(self):
        # Connect ports with FIFOs exports
        self.dut_result_get_port.connect(self.dut_result_fifo.get_export)
        self.refmodel_result_get_port.connect(self.refmodel_result_fifo.get_export)

        # Expose FIFOs' analysis exports
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
                if ISDUTSEQ:
                    self.resrmod_queue.put(response_rmod) # (Maybe next deprecation)
                    if request_dut.YOUR_RESET_SIGNAL == 0 and self.enable_scoreboarding == False:
                        self.enable_scoreboarding = True
                        self.resdut_queue.get()

                if self.enable_scoreboarding:  
                    try:
                        if ISDUTSEQ:
                            tr_rmod = self.resrmod_queue.get()
                            tr_dut = self.resdut_queue.get()

                        # ====================================================
                        #  (Maybe next deprecation)
                        # Specular validation for possible negative values
                        # # if(tr_dut.POSSIBLE_NEGATIVE_SIGNAL.signed_integer < 0):
                        # #     tr_dut.POSSIBLE_NEGATIVE_SIGNAL=tr_dut.POSSIBLE_NEGATIVE_SIGNAL.signed_integer
                        # ====================================================

                        # ====================================================
                        # Scorboarding proposal (using available UVMEnv tools)
                        # Edit as you need
                        # ====================================================
                        # You can use the mechanism of general assertions and use filters:
                        # # for signame in get_dut_signames(): # You can filter, i.e. type='INPUT'
                        # #     assert getattr(tr_dut, signame) == getattr(tr_rmod, signame), \
                        # #         f'FAILED [{signame}]: DUT({hex(getattr(tr_dut, signame))}) | RefModel({hex(getattr(tr_rmod, signame))})'

                        # # # You can also validate signals individually:
                        # # cond = tr_dut.SIGNAL_NAME == tr_rmod.SIGNAL_NAME
                        # # assert cond, \
                        # #     f'FAILED [SIGNAL_NAME]: DUT({hex(tr_dut.SIGNAL_NAME)}) | RefModel({hex(tr_rmod.SIGNAL_NAME)})'
                        
                        # # # You can use the report mechanism in any moment
                        # # if cond:
                        # #     report.write(message=f'[TEST PASSED] SIGNAL_NAME', component=self, level=pyuvm.INFO)
                        # # else:
                        # #     report.write(message=f'[TEST FAILED] {tr_dut}', component=self, level=pyuvm.ERROR)
                        # #     report.write(
                        # #         message=f'DUT({hex(tr_dut.SIGNAL_NAME)}) | RefModel({hex(tr_rmod.SIGNAL_NAME)}) [SIGNAL_NAME]', 
                        # #         component=self, 
                        # #         level=pyuvm.INFO
                        # #     )
                        # ====================================================
                    except ValueError as ex:
                        self.logger.error(f'{ex}')
                        pass

        self.logger.info('Final general scoreboarding')

        if ISDUTSEQ:
            # (Maybe next deprecation)
            # Get the last result (after last cycle) to be able to compare with reference model.
            # This process is made checking the aux queues.
            # (for now, is repeated code)
            # # while not self.resdut_queue.empty() and not self.resrmod_queue.empty():
            # #     response_rmod = self.resrmod_queue.get()
            # #     response_dut = self.resdut_queue.get()

            # #     # Specular validation for possible negative values
            # #     #if(response_dut.POSSIBLE_NEGATIVE_SIGNAL.signed_integer < 0):
            # #     #    response_dut.POSSIBLE_NEGATIVE_SIGNAL=response_dut.POSSIBLE_NEGATIVE_SIGNAL.signed_integer
                
            # #     ## Save conditions
            # #     condition_1 = response_dut.result_signal_1 == response_rmod.result_signal_1
            # #     condition_N = response_dut.result_signal_N == response_rmod.result_signal_N

            # #     # Make assertions
            # #     assert condition_1, f'TEST FAILED result_signal_1 dut({hex(response_dut.result_signal_1)}), rmod({hex(response_rmod.result_signal_1)})'
            # #     assert condition_N, f'TEST FAILED result_signal_N dut({hex(response_dut.result_signal_N)}), rmod({hex(response_rmod.result_signal_N)})'

            # #     # Save on report file if necessary (watch Misces/UVMEnvReport.py for help)
            # #     if condition_1:
            # #         report.write(message=f'[TEST PASSED] {tr_dut}', component=self, level=pyuvm.INFO)
            # #     else:
            # #         report.write(message=f'[TEST FAILED] {tr_dut}', component=self, level=pyuvm.ERROR)
            ''''''

    def report_phase(self):
        super().report_phase()

        ''' You can write reporting actions here '''


    def write(self, t):
        self.__tr = t
        if ISDUTSEQ:
            # (Maybe next deprecation)
            # # if self.__tr.get_transaction().request.YOUR_RESET_SIGNAL == 0:
            # #     self.resdut_queue.put(self.__tr.get_transaction().response)
            ''''''

        # You can analyze here each transaction if necessary:
        #assert <condition>, 'Error message'
        


sys.modules[__name__] = CLASS_NAME

        
            
