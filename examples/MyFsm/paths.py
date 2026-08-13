#########################
###    CONFIG FILE    ###
#########################

# ====================
# Python imports
# ====================
import sys
import os

PROJECT_PATH=os.getcwd()

def loadProjectPaths():
    sys.path.append(PROJECT_PATH)

    sys.path.append(os.path.join(PROJECT_PATH, 'Itface'))
    sys.path.append(os.path.join(PROJECT_PATH, 'Itface', '_impl'))
    sys.path.append(os.path.join(PROJECT_PATH, 'UVM_TB'))
    sys.path.append(os.path.join(PROJECT_PATH, 'HDLSrc'))

    for testPath in os.listdir(os.path.join(PROJECT_PATH, 'UVM_TB')):
        if os.path.isdir(os.path.join(PROJECT_PATH, 'UVM_TB', testPath)):
            sys.path.append(os.path.join(PROJECT_PATH, 'UVM_TB', testPath))
            sys.path.append(os.path.join(PROJECT_PATH, 'UVM_TB', testPath, 'Seqnce'))
            sys.path.append(os.path.join(PROJECT_PATH, 'UVM_TB', testPath, 'Misces'))

            sys.path.append(os.path.join(PROJECT_PATH, 'UVM_TB', testPath, 'SeqItm'))
            for seqitemPath in os.listdir(os.path.join(PROJECT_PATH, 'UVM_TB', testPath, 'SeqItm')):
                if os.path.isdir(os.path.join(PROJECT_PATH, 'UVM_TB', testPath, 'SeqItm', seqitemPath)):
                    sys.path.append(os.path.join(PROJECT_PATH, 'UVM_TB', testPath, 'SeqItm', seqitemPath))

            sys.path.append(os.path.join(PROJECT_PATH, 'UVM_TB', testPath, 'Envmnt'))
            for envPath in os.listdir(os.path.join(PROJECT_PATH, 'UVM_TB', testPath, 'Envmnt')):
                if os.path.isdir(os.path.join(PROJECT_PATH, 'UVM_TB', testPath, 'Envmnt', envPath)):
                    sys.path.append(os.path.join(PROJECT_PATH, 'UVM_TB', testPath, 'Envmnt', envPath, 'Scorbd'))
                    sys.path.append(os.path.join(PROJECT_PATH, 'UVM_TB', testPath, 'Envmnt', envPath, 'RefMdl'))
                    sys.path.append(os.path.join(PROJECT_PATH, 'UVM_TB', testPath, 'Envmnt', envPath, 'RefMdl', '_impl'))

                    sys.path.append(os.path.join(PROJECT_PATH, 'UVM_TB', testPath, 'Envmnt', envPath, 'Agents'))
                    for agentPath in os.listdir(os.path.join(PROJECT_PATH, 'UVM_TB', testPath, 'Envmnt', envPath, 'Agents')):
                        if os.path.isdir(os.path.join(PROJECT_PATH, 'UVM_TB', testPath, 'Envmnt', envPath, 'Agents', agentPath)):
                            sys.path.append(os.path.join(PROJECT_PATH, 'UVM_TB', testPath, 'Envmnt', envPath, 'Agents', agentPath))




