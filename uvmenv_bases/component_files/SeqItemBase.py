############################
###    COMPONENT FILE    ###
############################

from .Request import Request
from .Response import Response


class SequenceItem:
	def __init__(self):
		self.request = Request('sitmreq_SEQITEM_NAME')
		self.response = Response('sitmres_SEQITEM_NAME')


