#!/bin/bash

############################################################################################################
# Uninstaller to Debian based Linux distros.
############################################################################################################

### Installation paths ####
REPO_PATH=$(pwd)
HOME_DIR=/home/$(whoami)
MAIN_DIR=$HOME_DIR/.UVMEnv
VENV_DIR=$HOME_DIR/.UVMEnv_virtualenv
REPOS_DIR=$MAIN_DIR/repos
BASES_DIR=$MAIN_DIR/bases
TOOLS_DIR=$MAIN_DIR/tools
COMMAND=/usr/bin/uvmenv
###########################

### Bash colors ####
C_RED="\e[31m"
C_BLUE="\e[34m"
C_CYAN="\e[36m"
C_GREEN="\e[32m"
C_YELLOW="\e[33m"
C_WHITE="\e[37m"
C_N="\e[39m"
####################

PY_VERSION=""

REMOVE_ALL=0
IS_PY10_OR_MINOR=0


function main(){
    # Firstly, get parameter 'all' value
    if [ "$1" == "all" ];then
        REMOVE_ALL=1
    fi

    # Verify if UVMEnv is already uninstalled
     if [ ! -d $MAIN_DIR ]; then
        printWarning "UVMEnv is currently uninstalled"
        exit 0
    fi

    # UNINSTALLING PROCESS
    # Remove simulators, python dependencies and system installation if 'all' is set (hard uninstalling)
    if [[ $REMOVE_ALL -eq 1 ]]; then
        uninstallSimulators

        getPythonVersion
        if [ $IS_PY10_OR_MINOR -eq 1 ]; then
            uninstallPythonDependencies
        else
            rm -rf $VENV_DIR
        fi
        
        # Autoremove system unused packages
        sudo apt autoremove -y
    fi
    
    # Remove UVMEnv install directory and command
    rm -rf $MAIN_DIR
    if [ $IS_PY10_OR_MINOR -eq 0 ]; then
        rm -rf $VENV_DIR
    fi
    sudo rm $COMMAND

    #Finally, show message
    if [[ $REMOVE_ALL -eq 1 ]]; then
        printInfo "UVMEnv has been HARD removed"
    else
        printInfo "UVMEnv has been removed"
    fi
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




function uninstallSimulators(){
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

function getPythonVersion(){
    local pyv_major=$(python3 --version | awk '{print $2}' | cut -d'.' -f1)
    local pyv_minor=$(python3 --version | awk '{print $2}' | cut -d'.' -f2)
    PY_VERSION=$pyv_major.$pyv_minor

    if [ "$pyv_major" -gt 3 ] || { [ "$pyv_major" -eq 3 ] && [ "$pyv_minor" -gt 10 ]; }; then
        IS_PY10_OR_MINOR=0
    else
        IS_PY10_OR_MINOR=1
    fi
}

function uninstallPythonDependencies(){
    python$PY_VERSION -m pip uninstall -y cocotb
    python$PY_VERSION -m pip uninstall -y cocotb-coverage
    python$PY_VERSION -m pip uninstall -y pyuvm
    python$PY_VERSION -m pip uninstall -y pyfiglet
    python$PY_VERSION -m pip uninstall -y colorama
}


main "$@"; exit

