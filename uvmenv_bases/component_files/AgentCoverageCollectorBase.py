############################
###    COMPONENT FILE    ###
############################

from pyuvm import uvm_component, uvm_tlm_analysis_fifo, uvm_get_port

"""
Import all sequece item responses from SeqItm directory, with an specific alias for each.
Use: 
    uvmenv --show-seqitems
to show the available sequence items on your project.
Example:
from your_seqitem import Response as YourResponseAlias
"""



class CoverageCollector(uvm_component):
    def __init__(self, name, parent):
        super().__init__(name, parent)
        self.tr = YourResponseAlias("tr")

        # Define your own coverage sets
        self.incov = set()
        self.outcov = set()

    def build_phase(self):
        super().build_phase()
        self.dut_result_fifo = uvm_tlm_analysis_fifo("dut_result_fifo", self)
        self.result_get_port = uvm_get_port("result_get_port", self)

    def connect_phase(self):
        super().connect_phase()
        self.result_get_port.connect(self.dut_result_fifo.get_export)
        self.result_export = self.dut_result_fifo.analysis_export

    def check_phase(self):
        super().check_phase()

        while self.result_get_port.can_get():
            success, tr = self.result_get_port.try_get()

            if not success:
                self.logger.critical('Fail getting transaction info')
            else:
                self.logger.info('Analysing TLM on check_phase')
                inputs = tr.get_response().request
                outputs = tr.get_response().response

                """Write here inputs and outputs handling"""
        
        """ Write here results processing after getting all signals """
        self.logger.info('Final general coverage')

    
    def write(self, t):
        self.tr = t.copy()
        self.logger.info(f'Received from Monitor in WRITE: {self.tr}')


