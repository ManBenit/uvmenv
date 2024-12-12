#!/bin/bash

############################################################################################################
# Installer to Ubuntu based Linux distros.
############################################################################################################

REPO_PATH=$(pwd)
# Installation paths
MAIN_DIR=/home/$(whoami)/.UVMEnv
REPOS_DIR=$MAIN_DIR/repos
BASES_DIR=$MAIN_DIR/bases
TOOLS_DIR=$MAIN_DIR/tools
COMMAND=/usr/bin/uvmenv
DOTLOCAL_BIN=/home/$(whoami)/.local/bin


### Bash colors ####
C_RED="\e[31m"
C_BLUE="\e[34m"
C_CYAN="\e[36m"
C_GREEN="\e[32m"
C_YELLOW="\e[33m"
C_WHITE="\e[37m"
C_N="\e[39m"
####################


function main(){
    # Firstly, get the update option
    local is_update
    if [ "$1" == "update" ];then
        is_update=1
    fi


    sudo apt update && sudo apt upgrade -y

    if [ -d $MAIN_DIR ] && [ ! $is_update ]; then
        echo -e "${C_YELLOW}UVMEnv is already installed${C_N}"
        exit 0
    fi


    if [ $is_update ]; then
        pip3 install --upgrade cocotb
        pip3 install --upgrade pyuvm
        rm -rf $MAIN_DIR

        mkdir $MAIN_DIR
        mkdir $REPOS_DIR

        installIcarus
        installVerilator
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
    pip3 install cocotb
    pip3 install pyuvm
}


function installTools(){
    printInfo "############### Installing jq... ###############"
    sudo apt install -y jq

    printInfo "############### Installing GTKWave... ###############"
    sudo apt install -y gtkwave

    printInfo "############### Installing Icarus... ###############"
    if [ "$(which iverilog)" == "" ]; then
        installIcarus
    fi

    printInfo "############### Installing Verilator... ###############"
    if [ "$(which verilator)" == "" ]; then
        installVerilator
    fi
}


function installIcarus(){
    cd $REPOS_DIR/iverilog

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

function installVerilator(){
    cd $REPOS_DIR/verilator

    local shell=$(ps -p $$ | grep -E 'ksh|bash|zsh|tcsh|sh|csh' | awk '{print $4}')
    if [ "$shell" == "bash" ]; then
        unset VERILATOR_ROOT
    else
        unsetenv VERILATOR_ROOT
    fi
    
    git pull         # Make sure git repository is up-to-date

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


