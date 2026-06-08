############################
###    COMPONENT FILE    ###
############################

import sys
from pyuvm import uvm_sequence_item
from Request import Request
from Response import Response


class SitDefault(uvm_sequence_item):
    def __init__(self, name):
        super().__init__(name)
        self.response = Response()
        self.request = Request()

sys.modules[__name__] = SitDefault

