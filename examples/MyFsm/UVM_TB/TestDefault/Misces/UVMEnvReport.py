#########################
###    CONFIG FILE    ###
#########################

# ====================
# Python imports
# ====================
import pyuvm
from pyuvm import logging


# ====================================================
# HOW TO USE UVMEnv REPORTING MECHANISM
# ====================================================
# On the component from you want to write, you must import the next:
# import pyuvm
# from UVMEnvReport import report
#
# You are able to define your own logging levels 
# (remember the values specified at python logger module)
# (remember only uvm_component classes have logger by themselves)
# so add them using __add_custom_loglevels method.
#
# Since you can create your levels, you can print them like defined levels:
# self.logger.log(pyuvm.INFO, 'An info message') # This is defined
# self.logger.log(26, 'A level message') # This is custom
#
# Also, you can use getLevelName method, but it is deprecated:
# self.logger.log(logging.getLevelName('MYLEVEL'), 'A level message')
#
# Then you can write at UVMEnv report file like this:
# report.write('This is report message', self, logging.getLevelName('MYLEVEL')) # But deprecated
# report.write('This is report message', self, 26) # Using custom logging level
# report.write('This is report message', self, pyuvm.WARNING) # Using defined levels
#
# Finally, use: 
#     uvmenv project report
# to show the generated report file.
# ====================================================


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


    def __init__(self, log_file='OSimon/uvmenv_report.log'):
        # Logger configuration
        self.logger = logging.getLogger('UVMEnvReport')
        self.logger.setLevel(self.generalReportLevel)

        # File handler creation
        file_handler = logging.FileHandler(log_file)
        file_handler.setLevel(self.generalReportLevel)

        # Formatting creation
        formatter = logging.Formatter('%(asctime)s - %(levelname)s %(message)s')
        formatter.format
        file_handler.setFormatter(formatter)

        # Add new handler to logger
        self.logger.addHandler(file_handler)

        self.__add_custom_loglevels()

    
    # The only method available to call since UVM components.
    # @param [message]: Message to be showed at console and report file.
    # @param [component]: Preferred to be 'self', will pint the component full hierarchy.
    # @param [level]: Must be an integer, is got from pyuvm library or custom defined.
    def write(self, message, component, level):
        if not isinstance(level, int):
            raise TypeError('UVMEnv reporting: level must be an integer')
        
        # Write on report file (implies watching the message also on log output)
        self.logger.log(level, f'[{component}]: {message}')

    def __add_custom_loglevels(self):
        ''' Add your own logging levels here '''
        
        # i.e, this is a level in range of INFO level:
        # logging.addLevelName(26, 'MYLEVEL')
        


# Singleton instance of reporting mechanism, ready for using.
report = UVMEnvReport()


