#########################
###    CONFIG FILE    ###
#########################

import yaml
from types import SimpleNamespace
from cocotb.types import LogicArray


# Method to convert a dictionary into namespace data, for easier management in dev and correct work of load_config.
# @param [d]: Dictionary to be converted.
# @return: SimpleNamespace object if dictionary, List if .yamls contains list (-) or simple type.
def __dict_to_namespace(data):
    if isinstance(data, dict):
        return SimpleNamespace(**{k: __dict_to_namespace(v) for k, v in data.items()})
    elif isinstance(data, list):
        return [__dict_to_namespace(item) for item in data]
    else:
        return data

# Function to load configuration from config.json file.
# @param [filename]: Path of .json file.
def load_config(filename):
    with open(filename, 'r') as config_file:
        # Load YAML as standar dict (safe_load)
        config_dict = yaml.safe_load(config_file)
        
        # Make soncersion to SimpleNamespace
        config = __dict_to_namespace(config_dict)
        
    return config


# Function to get binary representation from certain integer
# @param [value]: Integer value to convert.
# @param [bitsize]: Signal bit length.
def to_bin_repr(value: int, bitsize: int) -> LogicArray:
    mask = (1 << bitsize) - 1
    if value < 0:
        return LogicArray.from_signed(value, bitsize)
    else:
        return LogicArray.from_unsigned(value & mask, bitsize)


# Function handle special values like 'x', 'z', 'u', 'w' in transaction signals.
# @param [value]: Value to process.
def process_unkn_val(value):
    if 'x' in str(value): return 'X'
    elif 'z' in str(value): return 'Z'
    elif 'u' in str(value): return 'U'
    elif 'w' in str(value): return 'W'


config = load_config('config.yml')

