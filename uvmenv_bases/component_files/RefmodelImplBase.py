############################
###    COMPONENT FILE    ###
############################

from RefModel import RefModel


class CLASS_NAME(RefModel):
	def makeTest(self, *, PARAMETERS): 
		self.params = locals()
		self.params.pop('self', None)

		"""Write here your golden model handling""" 

		# Finally return the result to compare 
		return None 

	def __str__(self):
		return f'\t[{self.__class__.__name__}]: '+', '.join(f'{key}={value}' for key, value in self.params.items())


