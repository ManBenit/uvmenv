############################
###    COMPONENT FILE    ###
############################

from pyuvm import uvm_agent, uvm_sequencer, ConfigDB
from .Driver import Driver
from .Monitor import Monitor
from .CoverageCollector import CoverageCollector

class Agent(uvm_agent):
    def __init__(self, name, parent):
        super().__init__(name, parent)


    def build_phase(self):
        super().build_phase()
        self.driver = Driver('driver', self)
        self.monitor = Monitor('monitor', self)
        self.seqr = uvm_sequencer('seqr', self)
        ConfigDB().set(None, '*', 'SEQR', self.seqr)
        self.coverage = CoverageCollector('coverage', self)

    def connect_phase(self):
        super().connect_phase()
        self.monitor.send.subscribers.append(self.coverage)

        self.monitor.send.connect(self.coverage.result_export)
        self.driver.seq_item_port.connect(self.seqr.seq_item_export)


