#!/bin/bash

############################################################################################################
# Installer to Debian based Linux distros.
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

IS_UPDATE=0
IS_PY10_OR_MINOR=0


function main(){
    # Firstly, get parameter 'update' value
     if [ "$1" == "update" ];then
        IS_UPDATE=1
    fi

    # PRE-INSTALLING PROCESS
    # Then, verify if UVMEnv is already installed (without update)
    if [ -d $MAIN_DIR ] && [[ $IS_UPDATE -eq 0 ]]; then
        printWarning "UVMEnv is already installed"
        exit 0
    fi

    # When is set the 'update' option, verify the previous existence of UVMEnv
     if [ ! -d $MAIN_DIR ] && [[ $IS_UPDATE -eq 1 ]]; then
        printError "UVMEnv is not installed for updating it"
        exit 0
    fi

    # Make a general update/upgrade
    sudo apt update && sudo apt upgrade -y

    # INSTALLING PROCESS
    installSystemRequirements

    # Get the installed Python version and create virtual environment if version is <= 3.10
    getPythonVersion
    if [ $IS_PY10_OR_MINOR -eq 0 ]; then
        activatePythonVenv
    fi

    installPythonDependencies
   
    # Create UVMEnv main structure if is installation and remove bases/tools from structure is is update
    if [[ $IS_UPDATE -eq 1 ]]; then
        # Update UVMEnv repository
        git pull origin main
        rm -rf $BASES_DIR
        rm -rf $TOOLS_DIR
    else 
        createMainStructure
    fi
    
    installSimulators
    createFrameworkEnv

    #Finally, show message
    if [[ $IS_UPDATE -eq 1 ]]; then
        printInfo "UVMEnv has been succesfully UPDATED"
    else
        printInfo "UVMEnv has been succesfully INSTALLED"
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




function installSystemRequirements(){
    # Necesary libraries for tools
    printInfo "############### Verifying prerequisites... ###############"
    sudo apt install -y git tree help2man perl python3 python3-pip make autoconf g++ flex bison ccache gperf
    sudo apt install -y libgoogle-perftools-dev numactl perl-doc
    sudo apt install -y libfl2  # Ubuntu only (ignore if gives error)
    sudo apt install -y libfl-dev  # Ubuntu only (ignore if gives error)
    sudo apt install -y zlib1g zlib1g-dev #zlibc  # Ubuntu only (ignore if gives error)
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

function activatePythonVenv(){
    # Install venv module if not exists
    if python$PY_VERSION -m venv --help > /dev/null 2>&1; then
        sudo apt install python$PY_VERSION-venv
    fi

    python$PY_VERSION -m venv $VENV_DIR
    source $VENV_DIR/bin/activate
}

function installPythonDependencies(){
    local upgrade="--upgrade"

    # Si no es actualización, solo instala
    if [[ $IS_UPDATE -eq 0 ]]; then
        upgrade=""
    fi

    python$PY_VERSION -m pip install $upgrade cocotb
    python$PY_VERSION -m pip install $upgrade cocotb-coverage
    python$PY_VERSION -m pip install $upgrade pyuvm
    python$PY_VERSION -m pip install $upgrade pyfiglet
    python$PY_VERSION -m pip install $upgrade colorama
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

function installSimulators(){
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


