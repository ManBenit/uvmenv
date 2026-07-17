#################################
###    REPRESENTATIVE FILE    ###
#################################

# ====================
# Python imports
# ====================
import sys
import importlib
from pyuvm import uvm_env

# ====================
# UVMEnv imports
# ====================
from utils import config



# ============================================================
# Every scoreboards are into Scorbd/ of each Environment.
#
# Use: 
#     uvmenv component list scorebd <TestName> <EnvName>
# to show the available scoreboards on your specific Environment.
#
# Import the Scoreboards you need, i.e.:
# import ScbDefault
# ============================================================
import ScbDefault


# ============================================================
# Every agents are into Agents/ of each Environment.
#
# Use: 
#     uvmenv component list agent <TestName> <EnvName>
# to show the available agents on your specific Environment.
#
# Import the Agents you need, i.e.:
# import agnt_default as AgentDefault
# ============================================================
import agnt_default as AgentDefault


class EnvDefault(uvm_env):
    def __init__(self, name, parent):
        super().__init__(name, parent)

    
    def build_phase(self):
        super().build_phase()

        self.__import_refmdl()
          
        # ====================================================
        # Instance here your scoreboard modules, i.e.:
        # self.scoreboard = ScbDefault('ScbDefault', self)
        # ====================================================
        self.scoreboard = ScbDefault('ScbDefault', self)

        # ====================================================
        # Instance here your agent modules, i.e.:
        # self.agent = AgentDefault('AgentDefault', self)
        # ====================================================
        self.agent = AgentDefault('AgentDefault', self)

    def connect_phase(self):
        super().connect_phase()

        # Subscribe your scoreboard as listeners of your agent monitors and reference model:
        self.agent.monitor.send.subscribers.append(self.scoreboard)
        self.refmodel.send.subscribers.append(self.scoreboard)

        # Connect your scoreboard result_export with all your monitors and reference model ports:
        self.agent.monitor.send.connect(self.scoreboard.dut_result_export)
        self.refmodel.send.connect(self.scoreboard.refmodel_result_export)

    
    def __import_refmdl(self):
        # Get an specific value from .json
        implementation_class = config.uvm_components.refmdl.refmdl_impl

        # Convert value into Python implementation that you want to use
        try:
            module = importlib.import_module(implementation_class)
            self.refmodel = module('reference_model', self)
        except Exception as e:
            self.logger.critical(f'Failed to load RefModel implementation: {e}')
            return

sys.modules[__name__] = EnvDefault
