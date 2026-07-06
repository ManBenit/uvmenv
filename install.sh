#!/bin/bash

# =============================================
# Installation paths
# =============================================
REPO_PATH=$(pwd)
HOME_DIR=/home/$(whoami)
MAIN_DIR=$HOME_DIR/.UVMEnv
VENV_DIR=$HOME_DIR/.UVMEnv_virtualenv
REPOS_DIR=$MAIN_DIR/repos
BASES_DIR=$MAIN_DIR/bases
TOOLS_DIR=$MAIN_DIR/tools
SCRIPTS_DIR=$MAIN_DIR/scripts
COMMAND=/usr/bin/uvmenv
# =============================================


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



function main(){
    local final_msg="INSTALLED"
    PKG_MNGR=$(get_pkg_mngr)
    PY_VERSION=$(python3 --version | awk '{print $2}' | cut -d'.' -f1-2)

    printInfo "Current Python version: $PY_VERSION"

    if [ "$EUID" -eq 0 ]; then
        printWarning "You should run as NON root, only write root password if necessary during installation"
        exit 1
    fi

    # Firstly, get parameter 'update' value
     if [ "$1" == "update" ];then
        IS_UPDATE=1
        final_msg="UPDATED"
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


    # ===========================
    # Main installation process
    # ===========================
    # System requirements
    installSystemRequirements

    # Python dependencies
    activatePythonVenv
    installPythonDependencies

    # Create UVMEnv main structure if is installation and remove bases/tools from structure is is update
    if [[ $IS_UPDATE -eq 1 ]]; then
        updateUVMEnvRepository
        rm -rf $BASES_DIR
        rm -rf $TOOLS_DIR
    else
        createUVMEnvInstallDirs
    fi
    
    installExternalDependencies

    installUVMEnv   

    #Finally, show message # TODO: review efectivity
    if [ "$?" -eq 0  ]; then
        printInfo "UVMEnv has been succesfully $final_msg"
    else
    createUVMEnvInstallDirs -del
        printError "Something went wront during UVMEnv installation"
    fi
}

# =============================================
# Installation utils
# =============================================
function printError(){
    echo -e "${C_RED}$1${C_N}"
}

function printInfo(){
    echo -e "${C_GREEN}$1${C_N}"
}

function printWarning(){
    echo -e "${C_YELLOW}$1${C_N}"
}

function get_pkg_mngr(){
    local container_name="$1"

    # Try to read os-release
    local os_info=$(cat /etc/os-release 2>/dev/null)

    # If os_info is not defined, then assign "unknown" value
    if [ -z "$os_info" ]; then
        echo "unknown"
        return 0
    fi

    # Extract ID and ID_LIKE by using "source" into a subshell,
    # this avoid troubles with regular expressions
    local id_brand
    id_brand=$(echo "$os_info" | (source /dev/stdin; echo "${ID} ${ID_LIKE}") 2>/dev/null)

    # Convert everything to lowercase
    id_brand=$(echo "$id_brand" | tr '[:upper:]' '[:lower:]')

    case "$id_brand" in
        *ubuntu*|*debian*)                           echo "apt" ;;
        *rhel*|*fedora*|*centos*|*rocky*|*almalinux*) echo "dnf" ;;
        *arch*)                                      echo "pacman" ;;
        *suse*|*opensuse*)                           echo "zypper" ;;
        *alpine*)                                    echo "apk" ;;
        *)                                           echo "unknown" ;;
    esac
}


# =============================================
# System requirements
# =============================================
function installSystemRequirements(){
    # Let's suppose apt
    local jsonlib_name="nlohmann-json3-dev"
    local ymllib_name="libyaml-cpp-dev"
    local pybind_name="pybind11-dev"

    if [ $PKG_MNGR == "dnf" ] || [ $PKG_MNGR == "zypper" ]; then
        jsonlib_name="nlohmann-json-devel"
        ymllib_name="yaml-cpp-devel"
        pybind_name="pybind11-devel"
    fi

    if [ $PKG_MNGR == "pacman" ] || [ $PKG_MNGR == "apk" ]; then
        jsonlib_name="nlohmann-json"
        ymllib_name="yaml-cpp"
        pybind_name="pybind11"
    fi

    printInfo "############### Verifying prerequisites... ###############"
    sudo $PKG_MNGR install -y $jsonlib_name
    sudo $PKG_MNGR install -y $ymllib_name
    sudo $PKG_MNGR install -y $pybind_name
    sudo $PKG_MNGR install -y git tree jq help2man perl python3 python3-pip make autoconf g++ flex bison ccache gperf
    sudo $PKG_MNGR install -y libgoogle-perftools-dev numactl perl-doc
    

    if [ "$PKG_MNGR" == "apt" ]; then
        sudo $PKG_MNGR install -y libfl2  # Ubuntu only (ignore if gives error)
        sudo $PKG_MNGR install -y libfl-dev  # Ubuntu only (ignore if gives error)
        sudo $PKG_MNGR install -y zlib1g zlib1g-dev #zlibc  # Ubuntu only (ignore if gives error)
    fi
}


# =============================================
# UVMEnv installation handling
# =============================================
function installUVMEnv(){
    # Go to current dir (UVMEnv repository)
    cd $REPO_PATH

    #TODO: change to rsync
    # Copy tools
    cp -r ./install/uvmenv_tools/* $TOOLS_DIR

    # Copy bases
    cp -r ./install/uvmenv_bases/* $BASES_DIR

    # Copy system scripts
    cp -r ./install/uvmenv_scripts/* $SCRIPTS_DIR

    # Compile UVMEnv

    # Create completion (ln -s)

    # Create command (ln -s)
    #if [ ! -L $COMMAND ]; then
    #    sudo ln -s $TOOLS_DIR/command.sh $COMMAND
    #fi    

    # Delete generated compilation from repo
}

# $1: Deletion option (-del)
function createUVMEnvInstallDirs(){
    if [ "$1" == "-del" ]; then
        rm -rf $BASES_DIR
        rm -rf $REPOS_DIR
        rm -rf $TOOLS_DIR
        rm -rf $SCRIPTS_DIR
        rm -rf $VENV_DIR
    else
        mkdir -p $BASES_DIR
        mkdir -p $REPOS_DIR
        mkdir -p $TOOLS_DIR
        mkdir -p $SCRIPTS_DIR
    fi
}

function updateUVMEnvRepository(){
    local script_name="install.sh"
    local remote_branch="origin/main"

    # Get local hash if installer
    local local_hash=$(git hash-object "$script_name")

    # Get remote hash of installer
    local remote_hash=$(git show "$remote_branch:$script_name" 2>/dev/null | git hash-object --stdin)

    # Compare both of them
    if [[ "$local_hash" != "$remote_hash" ]]; then
        printWarning "Installer has changes from remote, please run:"
        printInfo "git pull origin main"
        printWarning "and try again the update."
        exit 1
    fi

    # If installer has no changes, make pull normally
    git pull origin main
}


# =============================================
# Python dependencies
# =============================================
function activatePythonVenv(){
    # Verify Python version
    # Return if is <=3.10 cause is not necesary a virtualenv
    local comp=$(echo "$PY_VERSION > 3.10" | bc -l)
    if [[ $comp -eq 0 ]]; then
        return
    fi

    # Install venv module if not exists
    if python$PY_VERSION -m venv --help > /dev/null 2>&1; then
        sudo $PKG_MNGR install python$PY_VERSION-venv
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
    python$PY_VERSION -m pip install $upgrade pytest
}


# =============================================
# External tools dependencies
# =============================================
# This function requires have created REPOS_DIR
function installExternalDependencies(){
    # GTKWave
    if [ "$(which gtkwave)" == "" ] || [[ $IS_UPDATE -eq 1 ]]; then
        printInfo "############### Installing GTKWave... ###############"
        installGtkwave
    fi

    # Simulators
    if [ "$(which iverilog)" == "" ] || [[ $IS_UPDATE -eq 1 ]]; then
        printInfo "############### Installing Icarus... ###############"
        installIcarus
    fi

    if [ "$(which verilator)" == "" ] || [[ $IS_UPDATE -eq 1 ]]; then
        printInfo "############### Installing Verilator... ###############"
        installVerilator
    fi
}


function installGtkwave(){
    sudo $PKG_MNGR install -y gtkwave #TODO: Install from repository)
}

function installIcarus(){
    if [ ! -d $REPOS_DIR/iverilog ]; then
        git clone https://github.com/steveicarus/iverilog.git $REPOS_DIR/iverilog
    fi
    
    cd $REPOS_DIR/iverilog

    # Remove previous compilation if update
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
    if [ ! -d $REPOS_DIR/verilator ]; then
        git clone https://github.com/verilator/verilator.git $REPOS_DIR/verilator
    fi
    
    cd $REPOS_DIR/verilator

    # Remove previous compilation if update
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



