#################################
###    REPRESENTATIVE FILE    ###
#################################

from pyuvm import uvm_env

"""
Import all Scoreboard classes you need.
Use: 
	uvmenv --show-scoreboards
to show the available scoreboards on your project.
Example:
"""
#from  Scoreboard import Scoreboard

"""
Import all Agent classes from your agents, with an specific alias for each.
Use: 
	uvmenv --show-agents
to show the available agents on your project.
Example:
"""
#from  your_agnt import Agent as YourAlias


class Environment(uvm_env):
	def __init__(self, name, parent):
		super().__init__(name, parent)

	def build_phase(self):
		self.scoreboard = Scoreboard("scoreboard", self)
		"""
		Instenciate here your agent modules.
		Example:
		"""
		#self.agent = YourAlias("agent", self)
		
		

	def connect_phase(self):
		super().connect_phase()
		"""
		Subscribe your scoreboard as listeners of your agent monitor:
		"""
		#self.agent.monitor.send.subscribers.append(self.scoreboard)

		"""
		Connect your scoreboard result_export with all your monitors ports:
		"""
		#self.agent.monitor.send.connect(self.scoreboard.result_export)

