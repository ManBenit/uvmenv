#!/bin/bash

HOME_DIR=$(echo $UVMENV_HOME)
IS_DEEP=0
PROC_MESSAGE="DELETED"

# =============================================
# Bash colors
# =============================================
C_RED="\e[31m"
C_BLUE="\e[34m"
C_CYAN="\e[36m"
C_GREEN="\e[32m"
C_YELLOW="\e[33m"
C_WHITE="\e[37m"
C_N="\e[39m"
# =============================================

# ===========================
# Preprocessing
# ===========================
if [ ! -n "$HOME_DIR" ];then
    echo "Missing env installation path, check UVMENV_HOME"
    exit 1
fi


read -p "UVMEnv will be $PROC_MESSAGE from $HOME_DIR, continue? (y/n): " opc
if [ "$opc" != "Y" ] && [ "$opc" != "y" ]; then
    echo -e "${C_GEEN}Aborted process ${S_N}"
    exit 0;
fi


# =============================================
# Installation paths
# =============================================
REPO_PATH=$(pwd)
MAIN_DIR=$HOME_DIR/uvmenv
VENV_DIR=$HOME_DIR/uvmenv_virtualenv
BINS_DIR=$HOME_DIR/bin
REPOS_DIR=$MAIN_DIR/repos
BASES_DIR=$MAIN_DIR/bases
TOOLS_DIR=$MAIN_DIR/tools
SCRIPTS_DIR=$MAIN_DIR/scripts
# =============================================




function main(){
    set -eE
    trap 'handleError ${LINENO} "$BASH_COMMAND" $?' ERR

    # PRE-UNINSTALLING PROCESS
    ## Then, verify if UVMEnv is not installed (without update)
    if [ ! -d $HOME_DIR ]; then
        printWarning "UVMEnv is not installed"
        return 0
    fi

    # Currently only deletes UVMEnv installation 
    # (which includes encapsulated Verilator and Icarus)
    uninstallVerilator
    uninstallIcarus
    uninstallUVMEnv

    printInfo "Now you can delete the \"UVMEnv config\" block from your .bashrc"
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

function handleError(){
    local failed_line=$1
    local failed_command=$2
    local exit_value=$3

    createUVMEnvInstallDirs --del-full
    printInfo "============================================="
    printError "Error during installation"
    printInfo "Failed command: $failed_command,"
    printInfo "... at line $failed_line."
    printError "Exit value: $exit_value."
    printInfo "============================================="

    exit $exit_value
}


function uninstallUVMEnv(){
    rm -rf $HOME_DIR
}



function uninstallIcarus(){
    printInfo "#=================== Removing encapsulated Icarus Verilog... ===================#"
    cd $REPOS_DIR/iverilog

    make -j $(nproc) uninstall
    make -j $(nproc) clean
    make -j $(nproc) distclean
}

function uninstallVerilator(){
    printInfo "#=================== Removing encapsulated Verilator... ===================#"

    cd $REPOS_DIR/verilator

    make -j $(nproc) uninstall
    make -j $(nproc) clean
    make -j $(nproc) distclean
}




main "$@"; exit $?

