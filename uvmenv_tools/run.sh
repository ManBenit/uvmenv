#!/bin/bash

############################################################################################################
# 
############################################################################################################


PROJECT_DIR=$(pwd)
CONFIG_FILE=$PROJECT_DIR/config.json
DIR_HDL=$PROJECT_DIR/HDLSrc
OUTSIM_DIR=$PROJECT_DIR/OSimon

### Bash colors ####
C_RED="\e[31m"
C_BLUE="\e[34m"
C_CYAN="\e[36m"
C_GREEN="\e[32m"
C_YELLOW="\e[33m"
C_WHITE="\e[37m"
C_N="\e[39m"
####################

USED_MODEL_FILES=""
TOP_LEVEL=""


function main(){    
    local files=""
    local modules_list=($(find $DUT_HDL_DIR -type f \( -name "*.v" -o -name "*.sv" \) | sort | uniq))

    for file in $(ls ${modules_list[@]}); do
        files+="$file "
    done
    
    rm -f $OUTSIM_DIR/uvmenv_report.log
    writeMakefile "$files"

    make

    # Search and delete all __pycache__ directories
    find "$PROJECT_DIR" -type d -name "__pycache__" -exec rm -rf {} +

    rm -rf $PROJECT_DIR/sim_build
    rm -f $PROJECT_DIR/results.xml
    rm -f $PROJECT_DIR/Makefile
}


function printError(){
    echo -e "${C_RED}$1${C_N}"
}

function printInfo(){
    echo -e "${C_GREEN}$1${C_N}"
}

function printWarning(){
    echo -e "${C_YELLOW}$1${C_N}"
}



# $1: HDL source files list (as string)
function writeMakefile(){
    echo "CWD = \$(shell pwd)" > Makefile
    echo "HDL_SRC = $DIR_HDL" >> Makefile
    echo "SIM ?=  $(jq -r '.simtool' $CONFIG_FILE)" >> Makefile
    echo -e "\n" >> Makefile
    echo "VERILOG_SOURCES = $1" >> Makefile
    echo -e "\n" >> Makefile
    echo "MODULE = Top_$(jq -r '.top_module' $CONFIG_FILE)" >> Makefile
    echo "TOPLEVEL = $(jq -r '.top_module' $CONFIG_FILE)" >> Makefile
    echo "TOPLEVEL_LANG ?= verilog" >> Makefile
    echo "#COCOTB_HDL_TIMEOUT = 1ns" >> Makefile
    echo "#COCOTB_HDL_TIMEPRECISION = 1ns" >> Makefile
    echo -e "\n" >> Makefile
    echo "include \$(shell cocotb-config --makefiles)/Makefile.sim" >> Makefile

    echo -e "\n" >> Makefile
}




main "$@"; exit




