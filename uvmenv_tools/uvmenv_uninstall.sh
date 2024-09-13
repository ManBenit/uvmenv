#!/bin/bash

############################################################################################################
# Installer to Ubuntu based Linux distros.
############################################################################################################

### Bash colors ####
C_RED="\e[31m"
C_BLUE="\e[34m"
C_GREEN="\e[32m"
C_N="\e[39m"
####################


# Path where repositories will be clonned and environment log files will be witten.
# $(pwd) by default
INSTALL_DIR=$(pwd)



function uninstallPrerequisites(){
    pip3 uninstall cocotb pyuvm
    sudo apt autoremove -y
}

function deleteRepositories(){
    rm -rf https://github.com/steveicarus/iverilog.git
    rm -rf https://github.com/verilator/verilator.git
}

function uninstallTools(){
    echo -e "${C_GREEN}Uninstalling jq...${C_N}"
    sudo apt purge --remove -y jq

    echo -e "${C_GREEN}Uninstalling GTKWave...${C_N}"
    sudo apt purge --remove -y gtkwave

    ## Uninstall icarus
    echo -e "${C_GREEN}Uninstalling Icarus...${C_N}"
    cd iverilog
    sudo make -j $(nproc) clean 
    #sudo make distclean
    cd ..
    rm -rf iverilog

    ## Uninstall verilator
    echo -e "${C_GREEN}Uninstalling Verilator...${C_N}"
    cd verilator
    sudo make -j $(nproc) clean
    #sudo make distclean
    cd ..
    rm -rf verilator


}



############## MAIN ##############
cd $INSTALL_DIR

uninstallTools
deleteRepositories
uninstallPrerequisites


sudo rm /usr/bin/uvmenv
##################################

