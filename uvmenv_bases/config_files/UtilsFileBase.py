#########################
###    CONFIG FILE    ###
#########################

import json
from types import SimpleNamespace


def load_config(filename):
	with open(filename, 'r') as config_file:
		config = json.load(config_file, object_hook=lambda d: SimpleNamespace(**d))
	return config

