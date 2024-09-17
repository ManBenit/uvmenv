#!/bin/bash
###############################################
# Command which will be used to handle UVMEnv #
###############################################




########################################################################################
################               CONSTANTS                               #################
########################################################################################

#************** DIRECTORIES **************#
# Main paths
TOOLS_DIR=/home/$(whoami)/UVMEnv/tools
BASES_DIR=/home/$(whoami)/UVMEnv/bases
BASES_REPRESENT_DIR=$BASES_DIR/representative_files
BASES_COMPONENT_DIR=$BASES_DIR/component_files
BASES_COMMAND_DIR=$BASES_DIR/command_files
BASES_CONFIG_DIR=$BASES_DIR/config_files
PROJECT_DIR=$(pwd)

# UVMEnv paths for writing base of representative files of UVM structure
# (Used when full verification construction will be done and when build the project)
DUT_HDL_DIR=$PROJECT_DIR/HDLSrc
TBENCH_DIR=$PROJECT_DIR/UVM_TB
OUTSIM_DIR=$PROJECT_DIR/OSimon
ENVIRONMENT_DIR=$TBENCH_DIR/Envmnt
BFM_DIR=$PROJECT_DIR/Itface

# UVM paths
SCOREBOARD_DIR=$ENVIRONMENT_DIR/Scorbd
REFMODEL_DIR=$ENVIRONMENT_DIR/RefMdl
AGENTS_DIR=$ENVIRONMENT_DIR/Agents
MISCELANEOUS_DIR=$TBENCH_DIR/Misces
SEQUENCES_DIR=$TBENCH_DIR/Seqnce
SEQITEMS_DIR=$TBENCH_DIR/SeqItm
REFMODELIMPL_DIR=$REFMODEL_DIR/_impl
BFMIMPL_DIR=$BFM_DIR/_impl


#************** FILES **************#
CONFIG_FILE=$PROJECT_DIR/config.json
RUN_FILE=$TOOLS_DIR/run.sh

# *** BASES *** #
# Command files
PORT_GETTER_FILEBASE=$BASES_COMMAND_DIR/getPortsBase.py
SIGNAL_GETTER_FILEBASE=$BASES_COMMAND_DIR/getSignalsBase.py

# Component files
AGENT_FILEBASE=$BASES_COMPONENT_DIR/AgentBase.py
AGENT_COVCOL_FILEBASE=$BASES_COMPONENT_DIR/AgentCoverageCollectorBase.py
AGENT_DRIVER_FILEBASE=$BASES_COMPONENT_DIR/AgentDriverBase.py
AGENT_MONITOR_FILEBASE=$BASES_COMPONENT_DIR/AgentMonitorBase.py
BFM_IMPL_FILEBASE=$BASES_COMPONENT_DIR/BFMImplBase.py
REFMODEL_FILEBASE=$BASES_COMPONENT_DIR/RefmodelBase.py
REFMODEL_IMPL_FILEBASE=$BASES_COMPONENT_DIR/RefmodelImplBase.py
SCOREBOARD_FILEBASE=$BASES_COMPONENT_DIR/ScoreboardBase.py
SEQITEM_FILEBASE=$BASES_COMPONENT_DIR/SeqItemBase.py
SEQITEM_REQUEST_FILEBASE=$BASES_COMPONENT_DIR/SeqItemRequestBase.py
SEQITEM_RESPONSE_FILEBASE=$BASES_COMPONENT_DIR/SeqItemResponseBase.py
SEQUENCE_FILEBASE=$BASES_COMPONENT_DIR/SequenceBase.py

# Config files
PATHS_FILEBASE=$BASES_CONFIG_DIR/PathsFileBase.py
UTIL_FILEBASE=$BASES_CONFIG_DIR/UtilsFileBase.py

# Representative files
BFM_FILEBASE=$BASES_REPRESENT_DIR/BFMBase.py
ENVIRONMENT_FILEBASE=$BASES_REPRESENT_DIR/EnvironmentBase.py
TEST_FILEBASE=$BASES_REPRESENT_DIR/TestBase.py
TOP_FILEBASE=$BASES_REPRESENT_DIR/TopBase.py




### Bash colors ####
C_RED="\e[31m"
C_BLUE="\e[34m"
C_CYAN="\e[36m"
C_GREEN="\e[32m"
C_YELLOW="\e[33m"
C_WHITE="\e[37m"
C_N="\e[39m"
####################



########################################################################################
################               MAIN MENU                               #################
########################################################################################
function main(){
    case $1 in
        --test)
            echo $(getCurrentDir)
            echo $(getCurrentDir "/home/manbenit/Github/Webos/")
        ;;

        -n|--new)
            echo "Project name (NoSpaces):"
            read projectName

            echo "Top level module (file name, not extension):"
            read topModule

            #echo -e "Used HDL languaje:\n1)SystemVerilog\n2)Verilog"
            #read langOption

            createNewEnv $projectName $topModule $2 #$langOption
        ;;

        -s|--search)
            searchProjects
        ;;

        --show-signals)
            ensureEnvironment
            bndRemove="n"

            if [ "$(find $DUT_HDL_DIR -type f \( -name "*.v" -o -name "*.sv" \) | sed -E 's/.*\/([^\/]+)\..*/\1/' | sort | uniq)" == "" ]; then
                printWarning "HDL directory is empty"
                exit 0
            fi

            shift
            if [ "$1" == "-r" ]; then
                deleteSignalsCsv
                bndRemove="r"
                #echo "refresh"
                shift
            fi

            if [ "$1" == "" ]; then
                showAllSignals $bndRemove
            else
                showSignals n $1
            fi
        ;;

        --show-modules)
            ensureEnvironment

            if [ "$(find $DUT_HDL_DIR -type f \( -name "*.v" -o -name "*.sv" \) | sed -E 's/.*\/([^\/]+)\..*/\1/' | sort | uniq)" == "" ]; then
                printWarning "HDL directory is empty"
                exit 0
            fi

            showModules
        ;;


        --new-agent)
            ensureEnvironment
            shift
            createNewAgent $@
        ;;

        --del-agent)
            ensureEnvironment
            shift
            deleteAgent $@
        ;;

        --show-agents)
            ensureEnvironment
            showAgents
        ;;


        --new-seqitem)
            ensureEnvironment
            shift
            createNewSeqItem $@
        ;;

        --del-seqitem)
            ensureEnvironment
            shift
            deleteSequenceItem $@
        ;;

        --show-seqitems)
            ensureEnvironment
            showSequeceItems
        ;;


        --new-sequence)
            ensureEnvironment
            shift
            createNewSequence $@
        ;;

        --del-sequence)
            ensureEnvironment
            shift
            deleteSequence $@
        ;;

        --show-sequences)
            ensureEnvironment
            showSequences
        ;;


        --new-refmodel)
            ensureEnvironment
            shift
            createNewRefModel $@
        ;;

        --show-refmodel)
            ensureEnvironment
            showRefModel
        ;;


        --new-bfm)
            ensureEnvironment
            shift
            createNewBFMImplementation $@
        ;;

        --show-bfm)
            ensureEnvironment
            showBfm
        ;;

        -h|--help)
            showHelp
        ;;

        run)
            ensureEnvironment

            if [ "$(find $DUT_HDL_DIR -type f \( -name "*.v" -o -name "*.sv" \) | sed -E 's/.*\/([^\/]+)\..*/\1/' | sort | uniq)" == "" ]; then
                printWarning "HDL directory is empty"
                exit 0
            fi

            $RUN_FILE
        ;;

        *)
            printError "Option not available"
        ;;
    esac
}


#######################################################################################################
################               INTERFACE UTIL FUNCTIONS                               #################
#######################################################################################################
function printError(){
    echo -e "${C_RED}$1${C_N}"
}

function printInfo(){
    echo -e "${C_GREEN}$1${C_N}"
}

function printWarning(){
    echo -e "${C_YELLOW}$1${C_N}"
}

# $1: Option.
# $2: Description.
function printOption(){
    echo -e "     ${C_CYAN}$1${C_N}:\n\t$2"
}



#######################################################################################################
################               FRAMEWORK UTIL FUNCTIONS                               #################
#######################################################################################################
# pwd | awk -F'/' '{print $NF}'
# Separar por el "field separator" /, luego imprimir el último elemento (nombre del directorio actual)
function validateCurrentProject(){
    if [ -f config.json ] && [ "$(jq -r '.id' config.json | base64 --decode)" == "uvm:$(pwd | awk -F'/' '{print $NF}'):env" ]; then
        echo 0
    fi
} 

# $1: Module name of HDLSrc
function validateExistingHDLModule(){
    # Search all source files
    ## Find all .v and .sv files: find $DUT_HDL_DIR -type f \( -name "*.v" -o -name "*.sv" \)
    ## Delete absolute path to get only name: sed -E 's/.*\/([^\/]+)\..*/\1/'
    ## Order and get unique copies of names: sort | uniq
    local module=$(find $DUT_HDL_DIR -type f \( -name "*.v" -o -name "*.sv" \) | sed -E 's/.*\/([^\/]+)\..*/\1/' | sort | uniq | grep $1)

    if [ "$module" == "" ]; then
        printError "Module $1 does not exist"
        exit 1
    fi
}

function ensureEnvironment(){
    local is_uvmenv=$(validateCurrentProject)

    if [ ! $is_uvmenv ];then
        printError "You need using a valid project to run this option."
        exit 0
    fi
}

function deleteSignalsCsv(){
    cd $DUT_HDL_DIR
    if [ -f .allSignals.csv ]; then
        rm -f .allSignals.csv 
    fi
    cd $PROJECT_DIR
}

# $1: An specific path. 
function getCurrentDir(){
    if [ $1 ]; then
        echo $1
        return
    fi
    echo $(pwd)
}


#######################################################################################################
################                     COMMANDS FUNCTIONS                               #################
#######################################################################################################
function showHelp(){
    echo -e "Usage: \t uvmenv ${C_CYAN}<OPTION>${C_N}"
    echo -e "\n  OPTION:"
    printOption "-n|--new"          "Creates a new UVMEnv project."
    printOption "-s|--search"       "Looks for a valid UVMEnv project into current directory."
    printOption "--show-signals"    "Show inputs/outputs of modules into HDLSrc directory.\n\tShows particular signals if module_file is set.\n\tRefresh signals if -r is put."
    printOption "--show-modules"    "Show list of modules into HDLSrc directory."
    
    printOption "--new-agent"       "Create an structure for an agent into Agents/agent_name."
    printOption "--del-agent"       "Delete an agent into Agents directory."
    printOption "--show-agents"     "Show agents into Agents directory."
    
    printOption "--new-seqitem"     "Create an structure for a sequence item into SeqItm directory."
    printOption "--del-seqitem"     "Delete a sequence item into SeqItm directory."
    printOption "--show-seqitems"   "Show all sequence items into SeqItm directory."

    printOption "--new-sequence"    "Create an structure for a sequence into Seqnce directory."
    printOption "--del-sequence"    "Delete a sequence into Seqnce directory."
    printOption "--show-sequences"  "Show all sequences into Seqnce directory."

    printOption "--new-refmodel"    "Create an structure for a reference model into RefMdl/_impl directory."
    printOption "--show-refmodels"  "Show all reference models into RefMdl/_impl directory."

    printOption "--new-bfm"         "Create an structure for a Bus Functional Model into Itface/_impl directory."
    printOption "--show-bfm"        "Show all BFM interfaces into Itface/_impl directory."

    printOption "run"               "Starts verification process."
    printOption "-h|--help"         "Shows ${C_GREEN}uvmenv${C_N} command help."
    echo ""
}


#############################################################
##                 ENVIRONMENT HANDLING                    ##
#############################################################
# $1: Project name.
# $2: Project top module.
#*** $3: Usar o no el workspace.
function createNewEnv(){
    local config_content=""

    if [ $3 ] && [ "$3" == "ws" ]; then
        echo "**Use workspace"
    fi
    
    # Create directories structure
    mkdir $PROJECT_DIR/$1

    cd $PROJECT_DIR/$1

    # Create UVMenv structure directories
    mkdir HDLSrc OSimon UVM_TB # $DUT_HDL_DIR $OUTSIM_DIR $TBENCH_DIR
    mkdir Itface Itface/_impl # $BFM_DIR $BFMIMPL_DIR
    mkdir UVM_TB/Envmnt UVM_TB/Misces # $ENVIRONMENT_DIR $MISCELANEOUS_DIR
    mkdir UVM_TB/Seqnce UVM_TB/SeqItm # $SEQUENCES_DIR $SEQITEMS_DIR
    mkdir UVM_TB/Envmnt/RefMdl UVM_TB/Envmnt/RefMdl/_impl # $REFMODEL_DIR $REFMODELIMPL_DIR
    mkdir UVM_TB/Envmnt/Agents UVM_TB/Envmnt/Scorbd # $AGENTS_DIR $SCOREBOARD_DIR

    # Create config file
    config_content+="{\n"
    config_content+="\t\"id\": \"$(echo "uvm:$1:env" | base64)\",\n"
    config_content+="\t\"name\": \"$1\",\n"
    config_content+="\t\"simtool\": \"verilator\",\n"
    config_content+="\t\"top_module\": \"$2\",\n"
    config_content+="\t\"uvm_components\": {\n"
    config_content+="\t\t\"itface\":{\n"
    config_content+="\t\t\t\"bfm_impl\":\"\"\n"
    config_content+="\t\t},\n"
    config_content+="\t\t\"refmdl\":{\n"
    config_content+="\t\t\t\"refmdl_impl\":\"\"\n"
    config_content+="\t\t}\n"
    config_content+="\t}\n"
    config_content+="}\n"
    echo -e $config_content > config.json


    # Create UVMenv structure files - Make each manager of UVM level
    ### Write script of utils
    cp $UTIL_FILEBASE utils.py

    ### Write script of paths
    cp $PATHS_FILEBASE paths.py

    ### Write Top
    cp $TOP_FILEBASE Top_$2.py

    ### Write Test
    cp $TEST_FILEBASE UVM_TB/Test.py

    ### Write Environment
    cp $ENVIRONMENT_FILEBASE UVM_TB/Envmnt/Environment.py

    ### Write Scoreboard
    cp $SCOREBOARD_FILEBASE UVM_TB/Envmnt/Scorbd/Scoreboard.py

    ### Write interface for BFM
    cp $BFM_FILEBASE Itface/BFM.py 

    ##### Write interface for Reference model
    cp $REFMODEL_FILEBASE UVM_TB/Envmnt/RefMdl/RefModel.py

    cd $PROJECT_DIR
}

function searchProjects(){
    local is_valid=$(validateCurrentProject)
    if [ $is_valid ]; then
        printInfo "You are currently into a uvmenv project"
    else
        for i in $(ls $PROJECT_DIR); do
            if [ -d $i ] && [ -f $i/config.json ] && [ "$(jq -r '.id' $i/config.json | base64 --decode)" == "uvm:$i:env" ]; then
                echo $i
            fi
        done
    fi
}

function showModules(){
    #local modules_dir=($(find $DUT_HDL_DIR -type f \( -name "*.v" -o -name "*.sv" \) | sort | uniq))
    local modules_dir=($(find $DUT_HDL_DIR -type f \( -name "*.v" -o -name "*.sv" \) | sed -E 's/.*\/([^\/]+)\..*/\1/' | sort | uniq))
    #readarray -t modules_dir <<< "$(ls -F $DUT_HDL_DIR | grep -v "/" | grep -E "sv|v")"

    for archivo in "${modules_dir[@]}"; do
        nom=$(echo $archivo | cut -d'.' -f1)
        if [ "$nom" == "$(jq -r '.top_module' $CONFIG_FILE)" ]; then
            echo -e "${C_CYAN}$nom [Top]${C_N}"
        else
            echo "$nom"
        fi
    done
}


#############################################################
##                    SIGNALS HANDLING                     ##
#############################################################
# $1: r|n option.
function showAllSignals(){
    # Files with absolute path
    local modules_list=($(find $DUT_HDL_DIR -type f \( -name "*.v" -o -name "*.sv" \) | sort | uniq))
    # Files with only name
    local modules_dir=($(find $DUT_HDL_DIR -type f \( -name "*.v" -o -name "*.sv" \) | sed -E 's/.*\/([^\/]+)\..*/\1/' | sort | uniq))
    local aux_hdl_dir=$DUT_HDL_DIR/auxHDL
    local count=0

    local module_name=""
    local model_file=""
    local write_option="a"

    if [ "$1" == "r" ]; then
        rm -f $DUT_HDL_DIR/.allSignals.csv
        
        # Make the auxiliar directory and copy files of design
        mkdir $aux_hdl_dir
        for m in "${modules_list[@]}"; do 
            cp $m $aux_hdl_dir
        done

        cp $SIGNAL_GETTER_FILEBASE $aux_hdl_dir/signals.py

        cd $aux_hdl_dir

        for archivo in "${modules_dir[@]}"; do
            verilator -Wno-WIDTHEXPAND -Wno-fatal --trace --x-assign unique --x-initial unique -cc --hierarchical $archivo --top-module $(echo $archivo | cut -d'.' -f1) >> verilator.log
            
            if [ $count -gt 0 ]; then
                write_option="a"
            else
                write_option="w"
            fi
            python3 signals.py $1 obj_dir/V$(echo $archivo | cut -d'.' -f1).h $write_option
            count=$((i+1))
        done

        mv .allSignals.csv $DUT_HDL_DIR

        count=0
        cd $PROJECT_DIR
        rm -rf $aux_hdl_dir
    fi



    cd $DUT_HDL_DIR
    # Copy signals getter file 
    if [ ! -f signals.py ]; then
        cp $SIGNAL_GETTER_FILEBASE signals.py
    fi

    for archivo in "${modules_dir[@]}"; do
        printInfo "\tSignals of $(echo $archivo | cut -d'.' -f1)"
        python3 signals.py n V$(echo $archivo | cut -d'.' -f1)
        printInfo ""
    done
 
    rm signals.py
    cd $PROJECT_DIR
}

# $1: r|n|i option.
# $2: File which will be analyzed
function showSignals(){
    validateExistingHDLModule $2

    cd $DUT_HDL_DIR
    if [ ! -f signals.py ]; then
        cp $SIGNAL_GETTER_FILEBASE signals.py
    fi

    python3 signals.py $1 V$(echo $2 | cut -d'.' -f1)
    printInfo ""

    rm signals.py
    cd $PROJECT_DIR
}



#############################################################
##                      AGENT HANDLING                     ##
#############################################################
# $1: Agent attribute -> standard (s), passive (p), active (a), node (n).
# $2: Agent alias name (Recommended: snake_case).
# $3: Name of HDL module.
function createNewAgent(){
    local has_active_part
    local has_passive_part
    local is_node_agnt

    if [ $# -lt 3 ]; then
        printError "Missing parameters"
        printInfo "Usage: uvmenv --new-agent <attr> <agent_name> <module_name>"
        exit 0
    fi

    # Verify if agent exists
    if [ -d $AGENTS_DIR/$2 ]; then
        printWarning "Agent already exists"
        exit 0
    fi

    # Verify if module_name exists
    validateExistingHDLModule $3

    # Check attributes
    if [ "$1" == "a" ]; then
        has_active_part=0
    fi

    if [ "$1" == "p" ]; then
        has_passive_part=0
    fi

    if [ "$1" == "s" ]; then
        has_active_part=0
        has_passive_part=0
    fi

    if [ "$1" == "n" ]; then
        has_active_part=0
        has_passive_part=0
        is_node_agnt=0

        echo "Origin module:"
        read origin

        echo "Destiny module:"
        read destiny

        validateExistingHDLModule $origin
        validateExistingHDLModule $destiny
    fi


    # Write files
    mkdir $AGENTS_DIR/$2
    touch $AGENTS_DIR/$2/.a_$1
    cp $AGENT_FILEBASE $AGENTS_DIR/$2/__init__.py

    echo -e "{\n\t\"module\":\"$3\"\n}" > $AGENTS_DIR/$2/.a_$1

    if [ $has_active_part ]; then
        # Request signals as information
        ### Currently, list of signals is done o the Top module
        local signals_list=($(showSignals i $3))

        # Prepare information variables
        local inputs=""

        local sig_type
        local sig_len
        local sig_name
        ## Make structure for inputs and outputs
        for i in ${signals_list[@]}; do
            sig_type=$(echo $i | cut -d',' -f1)
            sig_len=$(echo $i | cut -d',' -f2)
            sig_name=$(echo $i | cut -d',' -f3)
            if [ "$sig_type" == "INPUT" ]; then
                inputs+="\\t\\t\\t\\t$sig_name = op.$sig_name,\\n"
            fi
        done

        # Post-processing for the last comma of response structure
        inputs=${inputs::-3}

        sed -r "s|BFM_SET|$inputs|g" $AGENT_DRIVER_FILEBASE > $AGENTS_DIR/$2/Driver.py
    fi

    if [ $has_passive_part ]; then
        cp $AGENT_MONITOR_FILEBASE $AGENTS_DIR/$2/Monitor.py
        cp $AGENT_COVCOL_FILEBASE $AGENTS_DIR/$2/CoverageCollector.py
    fi

    if [ $is_node_agnt ]; then
        echo -e "{\n\t\"origin_module\":\"$origin\",\n\t\"dest_module\":\"$destiny\"\n}" > $AGENTS_DIR/$2/.a_$1
    fi
}

function showAgents(){
    local agent_type=""
    local agent_info=""
    
    local agents_list=($(ls -F $AGENTS_DIR | grep / | awk '{ gsub(/\/$/, ""); print }' ))
    for agent in "${agents_list[@]}"; do
        agent_info+="$agent: "

        #agent_type=$( ls $AGENTS_DIR/$agent | grep -E '^Agent_.*\.py$' | sed -n 's/^Agent_\(.\)\.py$/\1/p' )
        if [ -f $AGENTS_DIR/$agent/.a_a ]; then
            agent_info+="Active agent [$(jq -r '.module' $AGENTS_DIR/$agent/.a_a)]"
        elif [ -f $AGENTS_DIR/$agent/.a_p ]; then
            agent_info+="Passive agent [$(jq -r '.module' $AGENTS_DIR/$agent/.a_p)]"
        elif [ -f $AGENTS_DIR/$agent/.a_s ]; then
            agent_info+="Standard agent [$(jq -r '.module' $AGENTS_DIR/$agent/.a_s)]"
        elif [ -f $AGENTS_DIR/$agent/.a_n ]; then
            agent_info+="Node agent [$(jq -r '.origin_module' $AGENTS_DIR/$agent/.a_n) --> $(jq -r '.dest_module' $AGENTS_DIR/$agent/.a_n)]"
        else
            agent_info+="UNKNOWN agent"
        fi

        echo "$agent_info"
        agent_info=""
    done
}

# $1: Agent alias name (which represents agent directory)
function deleteAgent(){
    if [ $# -lt 1 ]; then
        printError "Missing parameters"
        printInfo "Usage: uvmenv --del-agent <agent_name>"
        exit 0
    fi

    # Verify if agent exists
    if [ ! -d $AGENTS_DIR/$1 ]; then
        printError "Agent $1 does not exist"
        exit 0
    fi

    rm -r $AGENTS_DIR/$1
}


#############################################################
##               SEQUENCE ITEM HANDLING                    ##
#############################################################
# $1: Sequence item alias name (Recommended: snake_case).
# $2: Name of HDL module.
function createNewSeqItem(){
    if [ $# -lt 2 ]; then
        printError "Missing parameters"
        printInfo "Usage: uvmenv --new-seqitem <seqitem_name> <module>"
        exit 0
    fi

    # Verify if sequence item exists
    if [ -d $SEQITEMS_DIR/$1 ]; then
        printWarning "Sequence item already exists"
        exit 0
    fi

    validateExistingHDLModule $2

    mkdir $SEQITEMS_DIR/$1

    # Request signals as information
    local signals_list=($(showSignals i $2))

    # Prepare information variables
    local res_input_lines=""
    local res_output_lines=""
    local res_input_lines_str=""
    local res_output_lines_str=""
    local req_input_lines=""
    local req_rand_input_lines=""
    local req_input_lines_str=""

    local sig_type
    local sig_len
    local sig_name
    ## Make response and request structure before writing files
    for i in ${signals_list[@]}; do
        sig_type=$(echo $i | cut -d',' -f1)
        sig_len=$(echo $i | cut -d',' -f2)
        sig_name=$(echo $i | cut -d',' -f3)

        if [ "$sig_type" == "INPUT" ]; then
            res_input_lines+="\\t\\t\\t\\t'$sig_name': self.ins['$sig_name'],\\n"
            res_input_lines_str+="\\t\\t\\t\\t'$sig_name': self.ins['$sig_name'].integer,\\n"
            req_input_lines+="\\t\\tself.$sig_name = 0\\n"
            req_rand_input_lines+="\\t\\tself.$sig_name = random.randint(0, $(echo '2^'$sig_len' - 1' | bc))\\n"
            req_input_lines_str+="\\t\\t\\t'$sig_name': self.$sig_name,\\n"
        elif [ "$sig_type" == "OUTPUT" ]; then
            res_output_lines+="\\t\\t\\t\\t'$sig_name': self.outs['$sig_name'],\\n"
            res_output_lines_str+="\\t\\t\\t\\t'$sig_name': self.outs['$sig_name'].integer,\\n"
        fi
    done

    # Post-processing for the last comma of response structure
    # (Delete comma, inv slash and 'n' (3 chars), after add \n)
    req_input_lines_str=${req_input_lines_str::-3}
    res_input_lines=${res_input_lines::-3}
    res_output_lines=${res_output_lines::-3}
    res_input_lines_str=${res_input_lines_str::-3}
    res_output_lines_str=${res_output_lines_str::-3}


    # Generate module initializer
    cp $SEQITEM_FILEBASE $SEQITEMS_DIR/$1/__init__.py

    # Generate Request.py
    #cp $BASES_DIR/SeqItemRequestBase.py $AGENTS_DIR/$1/Request.py
    sed -r "s|ATTRIB_SIGNALS|$req_input_lines|g" $SEQITEM_REQUEST_FILEBASE > $SEQITEMS_DIR/$1/tmpReq1.py
    sed -r "s|RANDOM_SIGNALS|$req_rand_input_lines|g" $SEQITEMS_DIR/$1/tmpReq1.py > $SEQITEMS_DIR/$1/tmpReq2.py
    sed -r "s|ATTRIB_STR_SIGNALS|$req_input_lines_str|g" $SEQITEMS_DIR/$1/tmpReq2.py > $SEQITEMS_DIR/$1/Request.py
    rm $SEQITEMS_DIR/$1/tmpReq*.py

    # Generate Response.py
    #cp $BASES_DIR/SeqItemResponseBase.py $AGENTS_DIR/$1/Response.py
    sed -r "s|THE_INPUTS|$res_input_lines|g" $SEQITEM_RESPONSE_FILEBASE > $SEQITEMS_DIR/$1/tmpRes1.py
    sed -r "s|THE_OUTPUTS|$res_output_lines|g" $SEQITEMS_DIR/$1/tmpRes1.py > $SEQITEMS_DIR/$1/tmpRes2.py #$SEQITEMS_DIR/$1/Response.py
    sed -r "s|THE_STR_INPUTS|$res_input_lines_str|g" $SEQITEMS_DIR/$1/tmpRes2.py > $SEQITEMS_DIR/$1/tmpRes3.py
    sed -r "s|THE_STR_OUTPUTS|$res_output_lines_str|g" $SEQITEMS_DIR/$1/tmpRes3.py > $SEQITEMS_DIR/$1/Response.py
    rm $SEQITEMS_DIR/$1/tmpRes*.py
}

function showSequeceItems(){
    local seqitems_list=($(ls -F $SEQITEMS_DIR | grep / | awk '{ gsub(/\/$/, ""); print }' ))

    for sitm in "${seqitems_list[@]}"; do
        echo $sitm
    done
}

# $1: Sequence item alias name (which represents a sequence item directory)
function deleteSequenceItem(){
    if [ $# -lt 1 ]; then
        printError "Missing parameters"
        printInfo "Usage: uvmenv --del-seqitem <seqitem_name>"
        exit 0
    fi

    # Verify if seqitem exists
    if [ ! -d $SEQITEMS_DIR/$1 ]; then
        printError "Sequence item $1 does not exist"
        exit 0
    fi

    rm -r $SEQITEMS_DIR/$1
}


#############################################################
##                   SEQUENCES HANDLING                    ##
#############################################################
# $1: Sequence class name (Recommended: PascalCase).
function createNewSequence(){
    if [ $# -lt 1 ]; then
        printError "Missing parameters"
        printInfo "Usage: uvmenv --new-sequence <SequenceName>"
        exit 0
    fi

    # Verify if sequence item exists
    if [ -f $SEQUENCES_DIR/$1.py ]; then
        printWarning "Sequence already exists"
        exit 0
    fi

    sed -r "s|CLASS_NAME|$1|g" $SEQUENCE_FILEBASE > $SEQUENCES_DIR/$1.py  
}

function showSequences(){
    local seqs_list=($(ls -F $SEQUENCES_DIR | grep -v / ))

    for seq in "${seqs_list[@]}"; do
        echo $seq | cut -d'.' -f1
    done
}

# $1: Sequence name 
function deleteSequence(){
    if [ $# -lt 1 ]; then
        printError "Missing parameters"
        printInfo "Usage: uvmenv --del-sequence <SequenceName>"
        exit 0
    fi

    # Verify if sequence exists
    if [ ! -f $SEQUENCES_DIR/$1.py ]; then
        printError "Sequence $1 does not exist"
        exit 0
    fi

    rm -r $SEQUENCES_DIR/$1.py
}


#############################################################
##                BFM IMPLEMENTATION HANDLING              ##
#############################################################
# $1: BFM class name with 'Impl' suffix (Recommended: PascalCaseImpl).
function createNewBFMImplementation(){
    if [ $# -lt 1 ]; then
        printError "Missing parameters"
        printInfo "Usage: uvmenv --new-bfm <BfmNameImpl>"
        exit 0
    fi

    # Verify if sequence item exists
    if [ -f $BFMIMPL_DIR/$1.py ]; then
        printWarning "BFM implementation already exists"
        exit 0
    fi

    # Request signals as information
    ### Currently, list of signals is done o the Top module
    local signals_list=($(showSignals i $(jq -r '.top_module' $CONFIG_FILE)))

    # Prepare information variables
    local parameters_of_set=""
    local init_values_on_set=""
    local inputs_of_get=""
    local outputs_of_get=""

    local sig_type
    local sig_len
    local sig_name
    ## Make structure for inputs and outputs
    for i in ${signals_list[@]}; do
        sig_type=$(echo $i | cut -d',' -f1)
        sig_len=$(echo $i | cut -d',' -f2)
        sig_name=$(echo $i | cut -d',' -f3)
        if [ "$sig_type" == "INPUT" ]; then
            parameters_of_set+="$sig_name,"
            init_values_on_set+="\\t\\tself.dut.$sig_name.value = $sig_name\\n"
            inputs_of_get+="\\t\\t\\t'$sig_name': self.dut.$sig_name.value,\\n"
        elif [ "$sig_type" == "OUTPUT" ]; then
            outputs_of_get+="\\t\\t\\t'$sig_name': self.dut.$sig_name.value,\\n"
        fi
    done

    # Post-processing for the last comma of response structure
    # (Delete last comma)
    parameters_of_set=${parameters_of_set::-1}
    # (Delete comma, inv slash and 'n' (3 chars), after add \n)
    inputs_of_get=${inputs_of_get::-3}
    outputs_of_get=${outputs_of_get::-3}

    # Generate ImplementationFile.py
    ## Change class name
    sed -r "s|CLASS_NAME|$1|g" $BFM_IMPL_FILEBASE > $BFMIMPL_DIR/tmp1.py  

    ## Change set method (parameters and inits)
    sed -r "s|PARAMETERS|$parameters_of_set|g" $BFMIMPL_DIR/tmp1.py > $BFMIMPL_DIR/tmp2.py  
    sed -r "s|INIT_VALUES|$init_values_on_set|g" $BFMIMPL_DIR/tmp2.py > $BFMIMPL_DIR/tmp3.py  
    rm $BFMIMPL_DIR/tmp1.py
    rm $BFMIMPL_DIR/tmp2.py

    ## Change get method (ins and outs sets)
    sed -r "s|GET_INS|$inputs_of_get|g" $BFMIMPL_DIR/tmp3.py > $BFMIMPL_DIR/tmp2.py  
    sed -r "s|GET_OUTS|$outputs_of_get|g" $BFMIMPL_DIR/tmp2.py > $BFMIMPL_DIR/$1.py  
    rm $BFMIMPL_DIR/tmp3.py
    rm $BFMIMPL_DIR/tmp2.py
}

function showBfm(){
    local bfmimpl_list=($(ls -F $BFMIMPL_DIR | grep -v / ))

    for bfm in "${bfmimpl_list[@]}"; do
        echo $bfm | cut -d'.' -f1
    done
}


#############################################################
##                 REFERENCE MODEL HANDLING                ##
#############################################################
# $1: Reference model class name with 'Model' suffix (Recommended: PascalCaseModel).
function createNewRefModel(){
    if [ $# -lt 1 ]; then
        printError "Missing parameters"
        printInfo "Usage: uvmenv --new-refmodel <RefNameModel>"
        exit 0
    fi

    # Verify if sequence item exists
    if [ -f $REFMODELIMPL_DIR/$1.py ]; then
        printWarning "Reference model implementation already exists"
        exit 0
    fi

    # Request signals as information
    ### Currently, list of signals is done o the Top module
    local signals_list=($(showSignals i $(jq -r '.top_module' $CONFIG_FILE)))

    # Prepare information variables
    local parameters=""

    local sig_type
    local sig_len
    local sig_name
    ## Make response and request structure before writing files
    local sig_type
    local sig_len
    local sig_name
    ## Make structure for inputs and outputs
    for i in ${signals_list[@]}; do
        sig_type=$(echo $i | cut -d',' -f1)
        sig_len=$(echo $i | cut -d',' -f2)
        sig_name=$(echo $i | cut -d',' -f3)

        if [ "$sig_type" == "INPUT" ]; then
            parameters+="$sig_name,"
        fi
    done

    # (Delete last comma)
    parameters=${parameters::-1}


    # Generate ImplementationFile.py
    ## Change class name
    sed -r "s|CLASS_NAME|$1|g" $REFMODEL_IMPL_FILEBASE > $REFMODELIMPL_DIR/tmp1.py  

    ## Change set method (parameters and inits)
    sed -r "s|PARAMETERS|$parameters|g" $REFMODELIMPL_DIR/tmp1.py > $REFMODELIMPL_DIR/$1.py 
    rm $REFMODELIMPL_DIR/tmp1.py

}

function showRefModel(){
    local refmodelimpl_list=($(ls -F $REFMODELIMPL_DIR | grep -v / ))

    for refm in "${refmodelimpl_list[@]}"; do
        echo $refm | cut -d'.' -f1
    done
}



main "$@"; exit


