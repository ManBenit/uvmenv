#!/bin/bash

function viewTreeProject(){
    tree -C | less -R
}

# $1: Path of OSimon files
function runGTKWave(){
    gtkwave $1/dut_signals.vcd &> /dev/null &
}

# $1: Path of OSimon files
function viewReport(){
    less $1/uvmenv_report.log
}

# $1: Path for RTL files
function getRTLfiles(){
    local files=""
    local modules_list=($(find $1 -type f \( -name "*.v" -o -name "*.sv" \) | sort | uniq))

    for file in $(ls ${modules_list[@]}); do
        files+="$file "
    done

    echo "$files"
}

# $1: Path for RTL files
function validateRTLExistence(){
    echo $(find $1 -type f \( -name "*.v" -o -name "*.sv" \) | sed -E 's/.*\/([^\/]+)\..*/\1/' | sort | uniq)
}

# $1: Path for project
function cleanProject(){
    find "$1" -type d -name "__pycache__" -exec rm -rf {} +

    rm -rf $1/sim_build
    rm -f $1/results.xml
    rm -f $1/Makefile
}




case $1 in
    "viewTreeProject")
        viewTreeProject
        ;;
    "runGTKWave")
        runGTKWave $2
        ;;
    "viewReport")
        viewReport $2
        ;;

    "getRTLfiles")
        getRTLfiles $2
        ;;
    "validateRTLExistence")
        validateRTLExistence $2
        ;;

    "cleanProject")
        cleanProject $2
        ;;
    *)
        echo "[sys_commands] Unknown command: $1"
        ;;
esac

