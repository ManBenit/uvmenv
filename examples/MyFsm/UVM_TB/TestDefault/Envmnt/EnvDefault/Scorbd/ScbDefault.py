############################
###    COMPONENT FILE    ###
############################

# ====================
# Python imports
# ====================
import sys
import pyuvm
from collections import deque
from pyuvm import uvm_scoreboard, uvm_tlm_analysis_fifo, uvm_get_port

# ====================
# UVMEnv imports
# ====================
from SignalsReader import get_dut_signames
from UVMEnvReport import report
from utils import config
ISDUTSEQ = config.dut_design.type == 'sequential'



class ScbDefault(uvm_scoreboard):
    def __init__(self, name, parent):
        super().__init__(name, parent)
        # Auxiliar queues to syncronize DUT data
        self.pending_dut   = deque()
        self.pending_rmod  = deque()
        self.sync_dut_ins  = deque()
        self.sync_dut_outs = deque()


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

        # Save data on history queues
        while self.dut_result_get_port.can_get() and self.refmodel_result_get_port.can_get():
            success_dut,  tr_dut  = self.dut_result_get_port.try_get()
            success_rmod, tr_rmod = self.refmodel_result_get_port.try_get()

            self.pending_dut.append(tr_dut)
            self.pending_rmod.append(tr_rmod)

            if not success_dut or not success_rmod:
                self.logger.critical(f'Fail getting transaction info: (dut:{success_dut},rmod:{success_rmod})')

        if ISDUTSEQ:
            # Delete the last ref model transaction because it is duplicated
            self.pending_rmod.pop()

            # Syncronize DUT inputs and outputs for scoreboarding (Current support, only when response is got on the next immediate cycle)
            for i in range( len(self.pending_dut) ):
                pending_dut_ins  = self.pending_dut[i].get_ins_only()
                pending_dut_outs = self.pending_dut[i].get_outs_only()
                if i == 0:
                    self.sync_dut_ins.append(pending_dut_ins)
                elif i > 0 and i < len(self.pending_dut)-1:
                    self.sync_dut_ins.append(pending_dut_ins)
                    self.sync_dut_outs.append(pending_dut_outs)
                else:
                    self.sync_dut_outs.append(pending_dut_outs)
        else:
            for i in range( len(self.pending_dut) ):
                self.sync_dut_ins.append( self.pending_dut[i].get_ins_only() )
                self.sync_dut_outs.append( self.pending_dut[i].get_outs_only() )

        # Ensure data pending lists have a coherent size for scoreboarding
        assert len(self.sync_dut_ins) == len(self.sync_dut_outs), \
            f'FAILED: DUT Ins({len(self.sync_dut_ins)}) | DUT Outs({len(self.sync_dut_outs)})'
        assert len(self.sync_dut_outs) == len(self.pending_rmod), \
            f'FAILED: DUT Out({len(self.sync_dut_outs)}) | RefModel({len(self.pending_rmod)})'
        

        # ====================================================
        # Scorboarding proposal (using available UVMEnv tools)
        # Edit as you need
        # ====================================================
        # You can use the mechanism of general assertions and use filters:
        for prefmod, dutin, dutout in zip(self.pending_rmod, self.sync_dut_ins, self.sync_dut_outs):
            for signame in get_dut_signames(type='INPUT'): # You can filter
                assert dutin.get(signame) == getattr(prefmod, signame), \
                    f'FAILED [{signame}]: DUT({hex(dutin.get(signame))}) | RefModel({hex(getattr(prefmod, signame))})'
            for signame in get_dut_signames(type='OUTPUT'): # You can filter
                assert dutout.get(signame) == getattr(prefmod, signame), \
                    f'FAILED [{signame}]: DUT({hex(dutout.get(signame))}) | RefModel({hex(getattr(prefmod, signame))})'
        
        # # You can also validate signals individually:
        # cond = tr_dut.SIGNAL_NAME == tr_rmod.SIGNAL_NAME
        # assert cond, \
        #     f'FAILED [SIGNAL_NAME]: DUT({hex(tr_dut.SIGNAL_NAME)}) | RefModel({hex(tr_rmod.SIGNAL_NAME)})'
        # ''''''
                            
        # # You can use the report mechanism in any moment
        # if cond:
        #     report.write(message=f'[TEST PASSED] SIGNAL_NAME', component=self, level=pyuvm.INFO)
        # else:
        #     report.write(message=f'[TEST FAILED] {tr_dut}', component=self, level=pyuvm.ERROR)
        #     report.write(
        #         message=f'DUT({hex(tr_dut.SIGNAL_NAME)}) | RefModel({hex(tr_rmod.SIGNAL_NAME)}) [SIGNAL_NAME]', 
        #         component=self, 
        #         level=pyuvm.INFO
        #     )
        # ====================================================

    def report_phase(self):
        super().report_phase()

        ''' You can write reporting actions here '''


    def write(self, t):
        pass


sys.modules[__name__] = ScbDefault

        
            
