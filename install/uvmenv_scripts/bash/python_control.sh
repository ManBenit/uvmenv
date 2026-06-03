#!/bin/bash

# Main paths
USR_HOME_DIR=/home/$(whoami)
VENV_DIR=$USR_HOME_DIR/.UVMEnv_virtualenv

# $1: Python version (x.xx)
function activatePythonVenv(){
    python$1 -m venv $VENV_DIR
    source $VENV_DIR/bin/activate
}

# $1: Project directory
# $2: Python version (x.xx)
function runUVMEnvProject(){
    if (( $(echo "$2 >= 3.11" | bc -l) )); then
        activatePythonVenv $2
    fi

    cd $1
    make
}



case $1 in
    "runUVMEnvProject")
        runUVMEnvProject $2 $3
        ;;
    "runSignalsGetter")
        echo "Deprecated option"
        ;;
    *)
        echo "[python_control] Unknown command: $1"
        ;;
esac

