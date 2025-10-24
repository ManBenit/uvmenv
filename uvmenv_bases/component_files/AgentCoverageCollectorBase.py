############################
###    COMPONENT FILE    ###
############################

from pyuvm import uvm_component, uvm_tlm_analysis_fifo, uvm_get_port
from cocotb_coverage.coverage import CoverPoint, CoverCross, coverage_db

from utils import dict_to_namespace
from default_seqitem import Response as DefaultSeqitemResponse

class CoverageCollector(uvm_component):
    def __init__(self, name, parent):
        super().__init__(name, parent)
        self.num_transactions = 0

    # Usage of coverage decorators
    """Write as many CoverPoints and CoverCross as you need"""
    # Unlock this block !
    """@CoverPoint('SOME NAME 1',
                xf=lambda tr: tr.SIGNAL_NAME,
                bins=[
                    BINS_VALUES_HERE
                ])
    @CoverPoint('SOME NAME 2',
                xf=lambda tr: tr.SIGNAL_NAME,
                bins=[
                    BINS_VALUES_HERE
                ])
    @CoverCross('SOME_NAME', items=['SOME NAME 1', 'SOME NAME 2'])
    def _sample_coverage(self, tr: DefaultSeqitemResponse):
        pass"""


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

        """You can check actions here"""

    def report_phase(self):
        coverage_db.export_to_xml(filename='OSimon/coverage_report.xml')

    
    def write(self, t):
        self.tr = t.copy()
        self.logger.info(f'Received from Monitor in WRITE')

        # Unlock this block !
        """transaction = dict_to_namespace({
            # Write here the signals involved in the transaction with the next specified format:
            # Resquest
            'SIGNAL_NAME': t.ins['SIGNAL_NAME'],
            # Response
            'SIGNAL_NAME': t.ins['SIGNAL_NAME']
        })

        self.num_transactions += 1
        self._sample_coverage(transaction)"""




