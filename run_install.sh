#!/bin/bash

IDIR=UVMEnvInstall
HOME_DIR="${HOME}/$IDIR"
IS_UPDATE=0
PROC_MESSAGE="INSTALLED"

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
for arg in "$@"; do
    case $arg in
        --home)
            shift
            if [ "$1" == "" ]; then
                echo -e "${C_RED}Wrong installation path ${S_N}"
                exit 1
            fi

            if [ ! -d $1 ];then
                echo -e "${C_RED}Directory $1 does not exists ${S_N}"
                exit 1
            fi

            HOME_DIR=$1/$IDIR
            shift
            ;;
        --update)
            IS_UPDATE=1
            PROC_MESSAGE="UPDATED"
            shift

            case $1 in
                all);;
                verilator);;
                icarus);;
                gtkwave);;
                cocotb);;
                pyuvm);;
                *)
                    # Unknown option, ignore it or handle it as needed
                    ;;
            esac
            ;;
        *)
            # Unknown option, ignore it or handle it as needed
            ;;
    esac
done


read -p "UVMEnv will be $PROC_MESSAGE at $HOME_DIR, continue? (y/n): " opc
if [ "$opc" != "Y" ] && [ "$opc" != "y" ]; then
    echo -e "${C_GEEN}Aborted installation ${S_N}"
    exit 0;
fi

# =============================================
# Installation paths
# =============================================
REPO_PATH=$(pwd)
MAIN_DIR=$HOME_DIR/uvmenv
VENV_DIR=$HOME_DIR/uvmenv_virtualenv
REPOS_DIR=$MAIN_DIR/repos
BASES_DIR=$MAIN_DIR/bases
TOOLS_DIR=$MAIN_DIR/tools
SCRIPTS_DIR=$MAIN_DIR/scripts
COMMAND=/usr/bin/uvmenv
# =============================================





function main(){
    # ===========================
    # Begin installation process
    # ===========================
    set -eE
    trap 'handleError ${LINENO} "$BASH_COMMAND" $?' ERR

    # Verify if exists Python and GCC
    if [ "$(python3 --version)" == "" ]; then
        printError "You need Python 3.10 or later"
        exit 0
    fi
    if [ "$(gcc --version)" == "" ]; then
        printError "You need GCC 13 or later"
        exit 0
    fi

    PKG_MNGR=$(get_pkg_mngr)
    PY_VERSION=$(python3 --version | awk '{print $2}' | cut -d'.' -f1-2)
    CC_VERSION=$(gcc --version | awk 'NR==1' | awk '{print $3}' | cut -d'.' -f1-2)

    # If already exists Python and GCC, validate a properly version
    printInfo "Current Python version: $PY_VERSION"
    printInfo "Current GCC version: $CC_VERSION"

    local valMinPy=$(echo "$PY_VERSION < 3.10" | bc -l)
    local valMinCc=$(echo "$CC_VERSION < 13"   | bc -l)
    if [[ $valMinPy -eq 1 ]]; then
        printError "Min Python version unsatisfied (Required 3.10 or later)"
        return 1
    fi
    if [[ $valMinCc -eq 1 ]]; then
        printError "Min GCC version unsatisfied (Required 13 or later)"
        return 1
    fi

    if [ "$EUID" -eq 0 ]; then
        printWarning "You should run as NON root, only write root password if necessary during installation"
        return 1
    fi

    # PRE-INSTALLING PROCESS
    ## Then, verify if UVMEnv is already installed (without update)
    if [ -d $HOME_DIR ] && [[ $IS_UPDATE -eq 0 ]]; then
        printWarning "UVMEnv is already installed"
        return 0
    fi

    ## When is set the '--update' option, verify the previous existence of UVMEnv
    if [ ! -d $HOME_DIR ] && [[ $IS_UPDATE -eq 1 ]]; then
        printError "UVMEnv is not installed for updating it"
        return 0
    fi

    ## Validate package manager to define the instruction to install system requirements
    INSTALL_CMD="sudo $PKG_MNGR install -y"
    case "$PKG_MNGR" in
        "pacman")
            INSTALL_CMD="sudo pacman -S --noconfirm"
            ;;
        "apk")
            INSTALL_CMD="sudo apk add"
    esac



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
        #updateUVMEnvRepository
        rm -rf $BASES_DIR
        rm -rf $TOOLS_DIR
        rm -rf $HOME_DIR/bin
        createUVMEnvInstallDirs
    else
        createUVMEnvInstallDirs
    fi
    
    installExternalDependencies

    installUVMEnv

    #Finally, show message
    printInfo "UVMEnv has been succesfully $PROC_MESSAGE"
    printWarning "You must add these lines on your .bashrc:"
    printWarning "export PATH=$HOME_DIR/bin:\$PATH"
    printWarning "export UVMENV_HOME=$HOME_DIR"
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

function handleError(){
    local failed_line=$1
    local failed_command=$2
    local exit_value=$3

    createUVMEnvInstallDirs -del
    printInfo "============================================="
    printError "Error during installation"
    printInfo "Failed command: $failed_command,"
    printInfo "... at line $failed_line."
    printError "Exit value: $exit_value."
    printInfo "============================================="

    exit $exit_value
}


# =============================================
# System requirements
# =============================================
function installSystemRequirements(){
    # Assume apt
    ## Mandatory installation
    local ymllib_name="libyaml-cpp-dev"
    local pybind_name="pybind11-dev"
    local gral_tools="git tree jq make help2man perl python3-pip autoconf g++ flex bison ccache gperf"
    # local install_cmd="sudo $PKG_MNGR install -y"

    ## Optional installation
    local perftools_pkg="libgoogle-perftools-dev"
    local numa_pkg="numactl"
    local perldoc_pkg="perl-doc"

    # Define package names
    ## Mandatory installation
    case "$PKG_MNGR" in
        "dnf"|"zypper")
            ymllib_name="yaml-cpp-devel"
            pybind_name="pybind11-devel"
            gral_tools="git tree jq make help2man perl python3-pip autoconf gcc-c++ flex bison ccache gperf"
            ;;
        "pacman")
            ymllib_name="yaml-cpp"
            pybind_name="pybind11"
            gral_tools="git tree jq make help2man perl python-pip autoconf gcc flex bison ccache gperf"
            # install_cmd="sudo pacman -S --noconfirm"
            ;;
        "apk")
            ymllib_name="yaml-cpp"
            pybind_name="pybind11"
            gral_tools="git tree jq make help2man perl py3-pip autoconf g++ flex bison ccache gperf"
            # install_cmd="sudo apk add"
            ;;
        "apt"|"apt-get")
            # Keep apt values
            ;;
        *)
            printError "Package manager not supported: $PKG_MNGR. Install manually."
            return 1
            ;;
    esac

    ## Optional installation
    case "$PKG_MNGR" in
        "dnf"|"zypper")
            perftools_pkg="gperftools-devel"
            numa_pkg="numactl-devel"
            perldoc_pkg="perl-doc"
            ;;
        "pacman")
            perftools_pkg="gperftools"
            numa_pkg="numactl"
            perldoc_pkg="perl" # No perl-doc, includes manpages
            ;;
        "apk")
            perftools_pkg="gperftools-dev"
            numa_pkg="numactl-dev"
            perldoc_pkg="perl-doc"
            ;;
        "apt"|"apt-get")
            # Keep apt values
            ;;
    esac

    printInfo "############### Installing system requirements... ###############"
    # Make mandatory installation
    $INSTALL_CMD $ymllib_name $pybind_name $gral_tools
    # Make optional installation
    $INSTALL_CMD $perftools_pkg $numa_pkg $perldoc_pkg
    

    if [ "$PKG_MNGR" == "apt" ] || [ "$PKG_MNGR" == "apt-get" ]; then
        sudo $PKG_MNGR install -y libfl2  # Ubuntu only (ignore if gives error)
        sudo $PKG_MNGR install -y libfl-dev  # Ubuntu only (ignore if gives error)
        sudo $PKG_MNGR install -y zlib1g zlib1g-dev #zlibc zlib1g zlib1g-dev liblz4 liblz4-dev  # Ubuntu only (ignore if gives error)
    fi
}


# =============================================
# UVMEnv installation handling
# =============================================
function installUVMEnv(){
    # Go to current dir (UVMEnv repository)
    cd $REPO_PATH

    # Copy tools
    cp -r ./install/uvmenv_tools/* $TOOLS_DIR

    # Copy bases
    cp -r ./install/uvmenv_bases/* $BASES_DIR

    # Copy system scripts
    cp -r ./install/uvmenv_scripts/* $SCRIPTS_DIR

    # Compile UVMEnv
    printInfo "Compiling UVMEnv..."
    mkdir $HOME_DIR/bin
    cd ./src
    g++ -O3 -Wall -std=c++17 \
        main.cpp $(find implements -type f -name '*.cpp') \
        -I/usr/include $(python3-config --includes) \
        -lyaml-cpp $(python3-config --ldflags --embed) \
        -o $HOME_DIR/bin/uvmenv

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
    # Always activate python virtualenv to encapsulate UVMEnv functions

    # Install venv module if not exists
    if ! python$PY_VERSION -m venv --help > /dev/null 2>&1; then
        printWarning "Module venv not found. Installing..."
        
        local venv_pkg=""

        case "$PKG_MNGR" in
            "apt"|"apt-get")
                # Explicit spec
                venv_pkg="python${PY_VERSION}-venv"
                ;;
            "dnf"|"zypper")
                # Fedora/RHEL/openSUSE include venv at python3-devel or python3
                venv_pkg="python3-devel"
                ;;
            "apk")
                # Alpine, venv is into python3
                venv_pkg="py3-virtualenv"
                ;;
            "pacman")
                # Arch includes venv at base package 'python'
                venv_pkg="python"
                ;;
        esac

        if [ -n "$venv_pkg" ]; then
            $INSTALL_CMD $venv_pkg
        else
            printError "Something went wrong while installing venv"
            exit 1
        fi
    else
        printInfo "python$PY_VERSION-venv available."
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

    if [ "$VIRTUAL_ENV" == "" ]; then
        printError "Wrong virtualenv activation"
        exit 1
    fi

    python$PY_VERSION -m pip install $upgrade cocotb
    python$PY_VERSION -m pip install $upgrade cocotb-coverage
    python$PY_VERSION -m pip install $upgrade pyuvm
    python$PY_VERSION -m pip install $upgrade pyyaml
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
        make -j $(nproc) clean
    fi

    git pull

    chmod 775 autoconf.sh
    ./autoconf.sh

    local shell=$(ps -p $$ | grep -E 'ksh|bash|zsh|tcsh|sh|csh' | awk '{print $4}')
    if [ "$shell" == "bash" ]; then
        ./configure --prefix $HOME_DIR
    else
        sh ./configure
    fi
    
    make -j $(nproc)
    make install
}

function installVerilator(){
    if [ ! -d $REPOS_DIR/verilator ]; then
        git clone https://github.com/verilator/verilator.git $REPOS_DIR/verilator
    fi
    
    cd $REPOS_DIR/verilator

    # Remove previous compilation if update
    if [[ $IS_UPDATE -eq 1 ]]; then
        make -j $(nproc) clean
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

    autoconf                           # Create ./configure script
    ./configure --prefix $HOME_DIR     # Configure and create Makefile
    make -j $(nproc)                   # Build Verilator itself (if error, try just 'make')

    #if [ $? -eq 0 ]; then
    #    echo "Run test?"
    #    read opt
    #fi

    make install
}


main "$@"; exit



