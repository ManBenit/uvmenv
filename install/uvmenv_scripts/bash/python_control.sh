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


# $1: Python version (x.xx)
# $2: Write option ('a' for append, 'w' for write)
# $3: Get option ('r' for refresh, 'i' for internal and 'n' for normal options)
# $4: File of iteration
function runSignalsGetter(){
    if (( $(echo "$2 >= 3.11" | bc -l) )); then
        activatePythonVenv $1
    fi
    python$1 signals.py $3 obj_dir/V$(echo $4 | cut -d'.' -f1).h $2
}


case $1 in
    "runUVMEnvProject")
        runUVMEnvProject $2 $3
        ;;
    "runSignalsGetter")
        runSignalsGetter $2 $3 $4 $5
        ;;
    *)
        echo "[python_control] Unknown command: $1"
        ;;
esac

