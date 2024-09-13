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
    uninstallTools
    deleteRepositories
    uninstallPrerequisites

    rm $COMMAND
}



function uninstallPrerequisites(){
    pip3 uninstall cocotb pyuvm
    apt autoremove -y
}

function deleteRepositories(){
    rm -rf $REPOS_DIR/iverilog
    rm -rf $REPOS_DIR/verilator
}

function uninstallTools(){
    echo -e "\n\n${C_YELLOW}############## Uninstalling jq... ##############${C_N}"
    apt purge --remove -y jq

    echo -e "\n\n${C_YELLOW}############## Uninstalling GTKWave... ##############${C_N}"
    apt purge --remove -y gtkwave

    ## Uninstall icarus
    echo -e "\n\n${C_YELLOW}############## Uninstalling Icarus... ##############${C_N}"
    cd $REPOS_DIR/iverilog
    make -j $(nproc) clean 
    #make distclean

    ## Uninstall verilator
    echo -e "\n\n${C_YELLOW}############## Uninstalling Verilator... ##############${C_N}"
    cd $REPOS_DIR/verilator
    make -j $(nproc) clean
    #make distclean
}


main "$@"; exit

