#!/bin/bash

############################################################################################################
# Installer to Ubuntu based Linux distros.
############################################################################################################

# Installation paths
BASE_DIR=/opt/UVMEnv
REPOS_DIR=$BASE_DIR/repos
BASES_DIR=$BASE_DIR/bases
TOOLS_DIR=$BASE_DIR/tools


### Bash colors ####
C_RED="\e[31m"
C_BLUE="\e[34m"
C_GREEN="\e[32m"
C_N="\e[39m"
####################


# Path where repositories will be clonned and environment log files will be witten.
# $(pwd) by default
INSTALL_DIR=$(pwd)

function main(){
    mkdir $BASE_DIR
    mkdir $REPOS_DIR $BASES_DIR $TOOLS_DIR

    # Descargar archivos y colocarlos en la ruta base
    # CONTINUE_HERE

    cd $INSTALL_DIR

    sudo apt update
    sudo apt upgrade
    installPrerequisites
    cloneRepositories
    installTools

    #sudo mv env.txt /usr/bin/uvmenv
    #sudo chmod 755 /usr/bin/uvmenv

    #sudo mkdir /opt/uvmenv/
}


function createInstallStructure(){
    
}

function installPrerequisites(){
    echo -e "${C_GREEN}Verifying prerequisites...${C_N}"
    sudo apt install -y git tree help2man perl python3 python3-pip make autoconf g++ flex bison ccache
    sudo apt install -y libgoogle-perftools-dev numactl perl-doc
    sudo apt install -y libfl2  # Ubuntu only (ignore if gives error)
    sudo apt install -y libfl-dev  # Ubuntu only (ignore if gives error)
    sudo apt install -y zlib1g zlib1g-dev #zlibc  # Ubuntu only (ignore if gives error)
    pip3 install cocotb
    pip3 install pyuvm
}

function cloneRepositories(){
    git clone https://github.com/steveicarus/iverilog.git
    git clone https://github.com/verilator/verilator.git
}

function installTools(){
    echo -e "${C_GREEN}Installing jq...${C_N}"
    sudo apt install -y jq

    echo -e "${C_GREEN}Installing GTKWave...${C_N}"
    sudo apt install -y gtkwave

    echo -e "${C_GREEN}Installing Icarus...${C_N}"
    installIcarus

    echo -e "${C_GREEN}Installing Verilator...${C_N}"
    installVerilator
}


function installIcarus(){
    cd iverilog

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

    cd ..
}

function installVerilator(){
    cd verilator

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

    cd ..
}


main "$@"; exit


