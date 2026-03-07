#########################
###    CONFIG FILE    ###
#########################

import sys
import os

PROJECT_PATH=os.getcwd()

# Directory structure paths ##########################################
sys.path.append(f'{PROJECT_PATH}')
sys.path.append(f'{PROJECT_PATH}/Itface')
sys.path.append(f'{PROJECT_PATH}/Itface/_impl')
sys.path.append(f'{PROJECT_PATH}/UVM_TB')

sys.path.append(f'{PROJECT_PATH}/UVM_TB/SeqItm')
sys.path.append(f'{PROJECT_PATH}/UVM_TB/Seqnce')
sys.path.append(f'{PROJECT_PATH}/UVM_TB/Envmnt')
sys.path.append(f'{PROJECT_PATH}/UVM_TB/Misces')

sys.path.append(f'{PROJECT_PATH}/UVM_TB/Envmnt/Agents')
sys.path.append(f'{PROJECT_PATH}/UVM_TB/Envmnt/Scorbd')
sys.path.append(f'{PROJECT_PATH}/UVM_TB/Envmnt/CovgCo')
sys.path.append(f'{PROJECT_PATH}/UVM_TB/Envmnt/RefMdl')
sys.path.append(f'{PROJECT_PATH}/UVM_TB/Envmnt/RefMdl/_impl')
######################################################################






