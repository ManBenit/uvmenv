############################
###    COMPONENT FILE    ###
############################

from pyuvm import uvm_component, uvm_tlm_analysis_fifo, uvm_get_port

class CoverageCollector(uvm_component):
    def __init__(self, name, parent):
        super().__init__(name, parent)

        # Define your own coverage sets
        self.incov = set()
        self.outcov = set()


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

    
    def write(self, t):
        self.tr = t.copy()
        self.logger.info(f'Received from Monitor in WRITE')

        """
        Analyze here each transaction with DUT. Recommended to use assertions.
        assert <condition>, 'Error message'
        """


