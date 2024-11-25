############################
###    COMPONENT FILE    ###
############################

from RefModel import RefModel
from utils import dict_to_namespace


class CLASS_NAME(RefModel):
    def makeTest(self, *, PARAMETERS): 
        self.params = locals()
        self.params.pop('self', None)

        """Write here your model handling""" 

        # Finally return the result to compare 
        # (assign your correct values)
        return dict_to_namespace({
RETURNS
        })

    def __str__(self):
        return f'\t[{self.__class__.__name__}]: '+', '.join(f'{key}={value}' for key, value in self.params.items())






############################
###    COMPONENT FILE    ###
############################

from RefModel import RefModel
from utils import dict_to_namespace


class CLASS_NAME(RefModel):
    def __init__(self, name, parent, abstract_param='default'):
        super().__init__(name, parent, abstract_param)


    def makeTest(self, *, PARAMETERS): 
        self.params = locals()
        self.params.pop('self', None)


        """Write here your model handling""" 


        # Finally return the result to compare 
        # (assign your correct values)
        return dict_to_namespace({
RETURNS
        })

    def __str__(self):
        return f'\t[{self.__class__.__name__}]: '+', '.join(f'{key}={value}' for key, value in self.params.items())


