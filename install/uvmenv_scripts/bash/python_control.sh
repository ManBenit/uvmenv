#!/bin/bash

# Main paths
HOME_DIR=/home/$(whoami)
VENV_DIR=$HOME_DIR/.UVMEnv_virtualenv

IS_PY10_OR_MINOR=1
PY_VERSION="3.10"

function getPythonVersion(){
    local pyv_major=$(python3 --version | awk '{print $2}' | cut -d'.' -f1)
    local pyv_minor=$(python3 --version | awk '{print $2}' | cut -d'.' -f2)
    PY_VERSION=$pyv_major.$pyv_minor

    if [ "$pyv_major" -gt 3 ] || { [ "$pyv_major" -eq 3 ] && [ "$pyv_minor" -gt 10 ]; }; then
        echo "false"
    else
        echo "true"
    fi
}

# $1: Python version
function activatePythonVenv(){
    python$1 -m venv $VENV_DIR
    source $VENV_DIR/bin/activate
}


case $1 in
    "getPythonVersion")
        getPythonVersion
        ;;
    "activatePythonVenv")
        activatePythonVenv
        ;;
esac

