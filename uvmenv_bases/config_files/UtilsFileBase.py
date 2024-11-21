#########################
###    CONFIG FILE    ###
#########################

import json
from types import SimpleNamespace

# Method to load configuration from config.json file.
def load_config(filename):
	with open(filename, 'r') as config_file:
		config = json.load(config_file, object_hook=lambda d: SimpleNamespace(**d))
	return config


# Method to extract a certain range of bits from a certain integer data.
# return: Tuple with extracted range with integer representation and binary representation.
def extract_bits_from_integer(number, high, low):
	# Shift to right by 'low' positions
	shifted = number >> low
	# Create a mask to extract 'hi - lo + 1' bits
	mask = (1 << (high - low + 1)) - 1
	# Apply mask
	extracted = shifted & mask
	return (extracted, bin(extracted))


# Method to convert a dictionary into namespace data, for easier management into development.
# return: SimpleNamespace object with dictionary data.
def dict_to_namespace(d):
	for key, value in d.items():
		if isinstance(value, dict):
			d[key] = dict_to_namespace(value)
	return SimpleNamespace(**d)
