#!/bin/bash

############################################################################################################
# Uninstaller to Debian based Linux distros.
############################################################################################################

# Installation paths
MAIN_DIR=/home/$(whoami)/.UVMEnv
REPOS_DIR=$MAIN_DIR/repos
BASES_DIR=$MAIN_DIR/bases
TOOLS_DIR=$MAIN_DIR/tools
COMMAND=/usr/bin/uvmenv


### Bash colors ####
C_RED="\e[31m"
C_BLUE="\e[34m"
C_CYAN="\e[36m"
C_GREEN="\e[32m"
C_YELLOW="\e[33m"
C_WHITE="\e[37m"
C_N="\e[39m"
####################

REMOVE_ALL=0

function main(){
    if [ "$1" == "all" ];then
        REMOVE_ALL=1
    fi

    if [[ $REMOVE_ALL -eq 1 ]]; then
        uninstallTools
        uninstallPrerequisites
    fi

    rm -rf $MAIN_DIR
    sudo rm $COMMAND
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


function uninstallPrerequisites(){
    pip3 uninstall -y cocotb 
    pip3 uninstall -y pyuvm
    sudo apt autoremove -y
}

function uninstallTools(){
    printInfo "############## Uninstalling jq... ##############"
    sudo apt purge --remove -y jq

    printInfo "############## Uninstalling GTKWave... ##############"
    sudo apt purge --remove -y gtkwave

    ## Uninstall icarus
    printInfo "############## Uninstalling Icarus... ##############"
    cd $REPOS_DIR/iverilog
    sudo make -j $(nproc) clean 
    #make distclean

    ## Uninstall verilator
    printInfo "############## Uninstalling Verilator... ##############"
    cd $REPOS_DIR/verilator
    sudo make -j $(nproc) clean
    #make distclean

    sudo rm -rf /usr/local/bin/verilator*
    sudo rm -rf /usr/local/bin/iverilog*
    sudo rm -rf /usr/local/bin/vvp
}


main "$@"; exit

