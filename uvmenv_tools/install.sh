#!/bin/bash

############################################################################################################
# Installer to Ubuntu based Linux distros.
############################################################################################################

# Installation paths
MAIN_DIR=/opt/UVMEnv
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


function main(){
    apt update && apt upgrade -y

    createInstallingStructure
    installPrerequisites
    cloneRepositories
    installTools
    createCommand

}

function createCommand(){
    ln -s $TOOLS_DIR/command.sh $COMMAND
}


function createInstallingStructure(){
    mkdir $MAIN_DIR
    mkdir $REPOS_DIR $BASES_DIR $TOOLS_DIR

    # Copy file bases
    cp -r uvmenv_bases/* $BASES_DIR

    # Copy tools
    cp -r uvmenv_tools/* $TOOLS_DIR
}

function installPrerequisites(){
    # Necesary libraries for tools
    echo -e "\n\n${C_GREEN}############### Verifying prerequisites... ###############${C_N}"
    apt install -y git tree help2man perl python3 python3-pip make autoconf g++ flex bison ccache
    apt install -y libgoogle-perftools-dev numactl perl-doc
    apt install -y libfl2  # Ubuntu only (ignore if gives error)
    apt install -y libfl-dev  # Ubuntu only (ignore if gives error)
    apt install -y zlib1g zlib1g-dev #zlibc  # Ubuntu only (ignore if gives error)
    pip3 install cocotb
    pip3 install pyuvm
}

function cloneRepositories(){
    git clone https://github.com/steveicarus/iverilog.git $REPOS_DIR/iverilog
    git clone https://github.com/verilator/verilator.git $REPOS_DIR/verilator
}

function installTools(){
    echo -e "\n\n${C_GREEN}############### Installing jq... ###############${C_N}"
    apt install -y jq

    echo -e "\n\n${C_GREEN}############### Installing GTKWave... ###############${C_N}"
    apt install -y gtkwave

    echo -e "\n\n${C_GREEN}############### Installing Icarus... ###############${C_N}"
    installIcarus

    echo -e "\n\n${C_GREEN}############### Installing Verilator... ###############${C_N}"
    installVerilator
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
    make install
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

    make install
}


main "$@"; exit


