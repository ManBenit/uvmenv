#!/bin/bash

############################################################################################################
# Installer to Debian based Linux distros.
############################################################################################################

REPO_PATH=$(pwd)
# Installation paths
HOME_DIR=/home/$(whoami)
MAIN_DIR=/home/$(whoami)/.UVMEnv
REPOS_DIR=$MAIN_DIR/repos
BASES_DIR=$MAIN_DIR/bases
TOOLS_DIR=$MAIN_DIR/tools
COMMAND=/usr/bin/uvmenv
PY_VERSION=""

### Bash colors ####
C_RED="\e[31m"
C_BLUE="\e[34m"
C_CYAN="\e[36m"
C_GREEN="\e[32m"
C_YELLOW="\e[33m"
C_WHITE="\e[37m"
C_N="\e[39m"
####################

IS_UPDATE=0
IS_PY10_OR_M=0


function main(){
    getPythonVersion
    # echo $PY_VERSION
    # # Si no es python3.10 o menor
    # if [ $IS_PY10_OR_M -eq 0 ]; then
    #     #echo "Crear virtualenv"
        
    #     bash -c "sudo apt install python$PY_VERSION-venv"
    #     bash -c "python$PY_VERSION -m venv $HOME_DIR/.UVMEnv_virtualenv"
    #     source $HOME_DIR/.UVMEnv_virtualenv/bin/activate
    #     bash -c "python$PY_VERSION -m pip install cocotb"
    # fi

    # exit 0

    # Firstly, get the "update" option
    if [ "$1" == "update" ];then
        IS_UPDATE=1
    fi

    if [ -d $MAIN_DIR ] && [[ $IS_UPDATE -eq 0 ]]; then
        printWarning "UVMEnv is already installed"
        exit 0
    fi

    if [ ! -d $MAIN_DIR ] && [[ $IS_UPDATE -eq 1 ]]; then
        printError "UVMEnv is not installed for updating it"
        exit 0
    fi


    sudo apt update && sudo apt upgrade -y

    if [[ $IS_UPDATE -eq 1 ]]; then
        # Update UVMEnv repository
        git pull
        # Update main simulation tools
        bash -c "python$PY_VERSION -m pip install --upgrade cocotb"
        bash -c "python$PY_VERSION -m pip install --upgrade cocotb-coverage"
        bash -c "python$PY_VERSION -m pip install --upgrade pyuvm"
        bash -c "python$PY_VERSION -m pip install --upgrade pyfiglet"
        bash -c "python$PY_VERSION -m pip install --upgrade colorama"
        rm -rf $BASES_DIR
        rm -rf $TOOLS_DIR

        installPrerequisites
        installTools
        createFrameworkEnv
    else 
        createMainStructure
        installPrerequisites
        installTools
        createFrameworkEnv
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

function getPythonVersion(){
    local pyv_major=$(python3 --version | awk '{print $2}' | cut -d'.' -f1)
    local pyv_minor=$(python3 --version | awk '{print $2}' | cut -d'.' -f2)
    PY_VERSION=$pyv_major.$pyv_minor

    if [ "$pyv_major" -gt 3 ] || { [ "$pyv_major" -eq 3 ] && [ "$pyv_minor" -gt 10 ]; }; then
        IS_PY10_OR_M=0
    else
        IS_PY10_OR_M=1
    fi
}


function createFrameworkEnv(){
    cd $REPO_PATH

    # Copy tools
    cp -r ./uvmenv_tools $TOOLS_DIR

    # Copy bases
    cp -r ./uvmenv_bases $BASES_DIR

    # Create command
    if [ ! -L $COMMAND ]; then
        sudo ln -s $TOOLS_DIR/command.sh $COMMAND
    fi
}


function createMainStructure(){
    mkdir $MAIN_DIR
    mkdir $REPOS_DIR

    git clone https://github.com/steveicarus/iverilog.git $REPOS_DIR/iverilog
    git clone https://github.com/verilator/verilator.git $REPOS_DIR/verilator
}

function installPrerequisites(){
    # Necesary libraries for tools
    printInfo "############### Verifying prerequisites... ###############"
    sudo apt install -y git tree help2man perl python3 python3-pip make autoconf g++ flex bison ccache gperf
    sudo apt install -y libgoogle-perftools-dev numactl perl-doc
    sudo apt install -y libfl2  # Ubuntu only (ignore if gives error)
    sudo apt install -y libfl-dev  # Ubuntu only (ignore if gives error)
    sudo apt install -y zlib1g zlib1g-dev #zlibc  # Ubuntu only (ignore if gives error)
    bash -c "python$PY_VERSION -m pip install cocotb"
    bash -c "python$PY_VERSION -m pip install cocotb-coverage"
    bash -c "python$PY_VERSION -m pip install pyuvm"
    bash -c "python$PY_VERSION -m pip install pyfiglet"
    bash -c "python$PY_VERSION -m pip install colorama"
}

function installTools(){
    echo $1
    printInfo "############### Installing jq... ###############"
    sudo apt install -y jq

    printInfo "############### Installing GTKWave... ###############"
    sudo apt install -y gtkwave

    printInfo "############### Installing Icarus... ###############"
    if [ "$(which iverilog)" == "" ] || [[ $IS_UPDATE -eq 1 ]]; then
        installIcarus
    fi

    printInfo "############### Installing Verilator... ###############"
    if [ "$(which verilator)" == "" ] || [[ $IS_UPDATE -eq 1 ]]; then
        installVerilator
    fi
}

# $1: Flag IS_UPDATE. It will be 0 or 1.
function installIcarus(){
    cd $REPOS_DIR/iverilog

    if [[ $IS_UPDATE -eq 1 ]]; then
        sudo make -j $(nproc) clean
    fi

    git pull

    chmod 775 autoconf.sh
    ./autoconf.sh

    local shell=$(ps -p $$ | grep -E 'ksh|bash|zsh|tcsh|sh|csh' | awk '{print $4}')
    if [ "$shell" == "bash" ]; then
        ./configure
    else
        sh ./configure
    fi
    
    make -j $(nproc)
    sudo make install
}

# $1: Flag IS_UPDATE. It will be set or unset.
function installVerilator(){
    cd $REPOS_DIR/verilator

    if [[ $IS_UPDATE -eq 1 ]]; then
        sudo make -j $(nproc) clean
    fi

    git pull         # Make sure git repository is up-to-date

    local shell=$(ps -p $$ | grep -E 'ksh|bash|zsh|tcsh|sh|csh' | awk '{print $4}')
    if [ "$shell" == "bash" ]; then
        unset VERILATOR_ROOT
    else
        unsetenv VERILATOR_ROOT
    fi

    # Get the last version registered on repository
    local last_version=$(git tag | tail -1)

    echo "Verilator version $last_version will be installed..."

    autoconf         # Create ./configure script
    ./configure      # Configure and create Makefile
    make -j $(nproc)  # Build Verilator itself (if error, try just 'make')

    #if [ $? -eq 0 ]; then
    #    echo "Run test?"
    #    read opt
    #fi

    sudo make install
}


main "$@"; exit


