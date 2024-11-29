#########################
###    CONFIG FILE    ###
#########################

import json
import logging
import pyuvm
from types import SimpleNamespace


# Class encapsulating the reporting mechanism.
# It is singleton to avoid duplicated information on report file
class UVMEnvReport(metaclass=pyuvm.Singleton):
    # Define minimum global reporting level.
    ## Acording to UVM: It will be reported all levels equal os greater than generalReportLevel.
    generalReportLevel = logging.DEBUG

    _instances = {}
    def __call__(self):
        if self not in self._instances:
            self._instances[self] = super(UVMEnvReport, self).__call__()
        return self._instances[self]

    @classmethod
    def clear_singletons(self, keep):
        classes = list(self._instances.keys())
        for del_self in classes:
            if del_self not in keep:
                del (self._instances[del_self])


    def __init__(self, log_file="OSimon/uvmenv_report.log"):
        # Logger configuration
        self.logger = logging.getLogger("UVMEnvReport")
        self.logger.setLevel(self.generalReportLevel)

        # File handler creation
        file_handler = logging.FileHandler(log_file)
        file_handler.setLevel(self.generalReportLevel)

        # Formatting creation
        formatter = logging.Formatter('%(asctime)s | %(levelname)s | %(message)s')
        formatter.format
        file_handler.setFormatter(formatter)

        # Add new handler to logger
        self.logger.addHandler(file_handler)

        self._add_custom_loglevels()

    
    # The only method available to call since UVM components.
    # @param [message]: Message to be showed at console and report file.
    # @param [component]: Preferred to be 'self', will pint the component full hierarchy.
    # @param [level]: Must be an integer, is got from pyuvm library or custom defined.
    def write(self, message, component, level):
        if not isinstance(level, int):
            raise TypeError("UVMEnv reporting: level must be an integer")
        
        # Método para escribir en el archivo de log
        self.logger.log(level, f'[{component}] | {message}')

    """
    # HOW TO USE write METHOD.

    
    ## Into component from you want to write, you must import the next:
    import pyuvm
    from utils import report

    ## You are able to define your own logging levels 
    ## (remember the values specified at python logger module)
    ## (remember only uvm_component classes have logger by themselves)
    ## so add them using _add_custom_loglevels method.

    ## Since you can create your levels, you can print them like classical levels:
    self.logger.log(pyuvm.INFO, 'An info message')
    self.logger.log(26, 'A level message')

    ## also you can use getLevelName method, but it is deprecated:
    self.logger.log(logging.getLevelName('MYLEVEL'), 'A level message')

    # Then you can writing at UVMEnv report file like:
    report.write('This is report message', self, logging.getLevelName('MYLEVEL')) # But deprecated
    report.write('This is report message', self, 26)
    report.write('This is report message', self, pyuvm.WARNING)
    """

    def _add_custom_loglevels(self):
        from pyuvm import logging
        """
        Add your own logging levels here, example
        logging.addLevelName(26, 'MYLEVEL') # This is a level in range of INFO level
        """




# Singleton instance of reporting mechanism, ready for using.
report = UVMEnvReport()


# Method to load configuration from config.json file.
# @param [filename]: Path of .json file. 
def load_config(filename):
    with open(filename, 'r') as config_file:
        config = json.load(config_file, object_hook=lambda d: SimpleNamespace(**d))
    return config


# Method to extract a certain range of bits from a certain integer data.
# @param [number]: Integer data to be analyzed.
# @param: [high]: The must significant bit of range you want.
# @param: [low]: The less significant bit of range you want.
# @return: Tuple with extracted range with integer and binary representation.
def extract_bits_from_integer(number, high, low):
    # Shift to right by 'low' positions
    shifted = number >> low
    # Create a mask to extract 'hi - lo + 1' bits
    mask = (1 << (high - low + 1)) - 1
    # Apply mask
    extracted = shifted & mask
    return (extracted, bin(extracted))


# Method to convert a dictionary into namespace data, for easier management in dev.
# @param [d]: Dictionary to be converted.
# @return: SimpleNamespace object with dictionary data.
def dict_to_namespace(d):
    for key, value in d.items():
        if isinstance(value, dict):
            d[key] = dict_to_namespace(value)
    return SimpleNamespace(**d)




