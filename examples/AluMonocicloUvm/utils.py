#########################
###    CONFIG FILE    ###
#########################

import json
from types import SimpleNamespace
from cocotb.binary import BinaryValue


# Function to load configuration from config.json file.
# @param [filename]: Path of .json file.
def load_config(filename):
    with open(filename, 'r') as config_file:
        config = json.load(config_file, object_hook=lambda d: SimpleNamespace(**d))
    return config


# Function to get binary representation from certain integer
# @param [value]: Integer value to convert.
# @param [bitsize]: Signal bit length.
def to_bin_repr(value: int, bitsize: int) -> BinaryValue:
    twos_complement_value = value & ((1 << bitsize) - 1)
    return BinaryValue(value=twos_complement_value, n_bits=bitsize, bigEndian=False)


# Function handle special values like 'x', 'z', 'u', 'w' in transaction signals.
# @param [value]: Value to process.
def process_unkn_val(value):
    if 'x' in str(value): return 'X'
    elif 'z' in str(value): return 'Z'
    elif 'u' in str(value): return 'U'
    elif 'w' in str(value): return 'W'


config = load_config('config.json')

