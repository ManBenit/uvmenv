#################################
###    REPRESENTATIVE FILE    ###
#################################

import importlib
from pyuvm import uvm_env
from utils import load_config

"""
Import all Scoreboard classes you need.
Use: 
    uvmenv --show-scoreboards
to show the available scoreboards on your project.
Example:
from  YourScoreboard import YourScoreboard
"""
from DefaultScoreboard import DefaultScoreboard


"""
Import all Agent classes from your agents, with an specific alias for each.
Use: 
    uvmenv --show-agents
to show the available agents on your project.
Example:
from  your_agnt import Agent as YourAgentAlias
"""
from default_agent import Agent as DefaultAgent


class Environment(uvm_env):
    def __init__(self, name, parent):
        super().__init__(name, parent)

    
    def build_phase(self):
        super().build_phase()

        self._import_refmdl()
          
        """
        Instanciate here your scoreboard modules
        Example:
        self.scoreboard = YourScoreboard('YourScoreboard', self)
        """
        self.scoreboard = DefaultScoreboard('DefaultScoreboard', self)

        """
        Instenciate here your agent modules.
        Example:
        self.agent = YourAgentAlias('DefaultAgent', self)
        """
        self.agent = DefaultAgent('DefaultAgent', self)

    def connect_phase(self):
        super().connect_phase()

        """
        Subscribe your scoreboard as listeners of your agent monitors and reference model:
        self.agent.monitor.send.subscribers.append(self.scoreboard)
        self.refmodel.send.subscribers.append(self.scoreboard)
        """
        self.agent.monitor.send.subscribers.append(self.scoreboard)
        self.refmodel.send.subscribers.append(self.scoreboard)

        """
        Connect your scoreboard result_export with all your monitors and reference model ports:
        self.agent.monitor.send.connect(self.scoreboard.dut_result_export)
        self.refmodel.send.connect(self.scoreboard.refmodel_result_export)
        """
        self.agent.monitor.send.connect(self.scoreboard.dut_result_export)
        self.refmodel.send.connect(self.scoreboard.refmodel_result_export)

    
    def _import_refmdl(self):
        # Get an specific value from .json
        config = load_config('config.json')
        implementation_class = config.uvm_components.refmdl.refmdl_impl

        # Convert value into Python implementation that you want to use
        try:
            module = importlib.import_module(implementation_class)
            clazz = getattr(module, implementation_class)
            self.refmodel = clazz('reference_model', self)
        except Exception as e:
            self.logger.critical(f'Failed to load RefModel implementation: {e}')
            return


