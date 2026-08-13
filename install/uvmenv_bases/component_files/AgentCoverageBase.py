############################
###    COMPONENT FILE    ###
############################

# ====================
# Python imports
# ====================
import pyuvm
from pyuvm import uvm_subscriber, uvm_tlm_analysis_fifo, uvm_get_port
from cocotb_coverage.coverage import CoverPoint, CoverCross, coverage_db

# ====================
# UVMEnv imports
# ====================
from UVMEnvReport import report



# ============================================================
# Every sequence items are into Seqitem/ of each Test.
#
# Use: 
#     uvmenv component list seqitem <TestName>
# to show the available scoreboards on your specific Environment.
#
# Import the Scoreboards you need, i.e.:
# import SitDefault
# ============================================================
import SitDefault

class Coverage(uvm_subscriber):
    def __init__(self, name, parent):
        super().__init__(name, parent)
        self.__num_transactions = 0

    # Write as many CoverPoints and CoverCross as you need
COVER_POINTS
    def __sample_coverage(self, tr: SitDefault):
        pass


    def build_phase(self):
        super().build_phase()
        self.dut_result_fifo = uvm_tlm_analysis_fifo('dut_result_fifo', self)
        self.result_get_port = uvm_get_port('result_get_port', self)
        
    def connect_phase(self):
        super().connect_phase()
        self.result_get_port.connect(self.dut_result_fifo.get_export)
        self.result_export = self.dut_result_fifo.analysis_export

    def check_phase(self):
        super().check_phase()

        while self.result_get_port.can_get():
            success_dut, tr_dut = self.result_get_port.try_get()

            if not success_dut:
                self.logger.critical(f'Fail getting transaction info: (dut:{success_dut})')
            else:
                ''' You can write actions/signals checking here '''

    def report_phase(self):
        super().report_phase()
        report.write(message=f'Processed {self.__num_transactions} transactions', component=self, level=pyuvm.INFO)
        coverage_db.export_to_xml(filename='OSimon/coverage_report.xml')

    
    def write(self, t):
        self.__tr = t

        self.__num_transactions += 1
        self.__sample_coverage(self.__tr)




