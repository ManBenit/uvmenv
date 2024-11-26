############################
###    COMPONENT FILE    ###
############################

from pyuvm import uvm_scoreboard, uvm_tlm_analysis_fifo, uvm_get_port



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
        self.dut_result_fifo = uvm_tlm_analysis_fifo("dut_result_fifo", self)
        self.refmodel_result_fifo = uvm_tlm_analysis_fifo("refmodel_result_fifo", self)

        self.dut_result_get_port = uvm_get_port("dut_result_get_port", self)
        self.refmodel_result_get_port = uvm_get_port("refmodel_result_get_port", self)
        
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
            success, tr = self.dut_result_get_port.try_get()

            if not success:
                self.logger.critical('[SCB] Fail getting transaction info')
            else:
                self.logger.info('Analysing TLM on check_phase')

        self.logger.info('Final general scoreboarding. If necessary')
    

    def write(self, t):
        self.tr = t.copy()
        self.logger.info(f'Received from Monitor: {self.tr}')
        

        
            