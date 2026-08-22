#!/bin/bash

DEFAULT_SYS_EDITOR="vi"



function viewTreeProject(){
    tree -C | less -R
}

# $1: Path of OSimon files
function runGTKWave(){
    gtkwave $1/dut_signals.vcd &> /dev/null &
}

# $1: Path of OSimon files
function viewReport(){
    less +G $1/uvmenv_report.log
}

# $1: Path of OSimon files
function viewCoverage(){
    less $1/coverage_report.xml
}

# $1: Path of file
function openEditor(){
    $DEFAULT_SYS_EDITOR $1
    exit $?
}



# $1: Path for RTL files
function getRTLFullFiles(){
    local files=""
    local modules_list=($(find $1 -type f \( -name "*.v" -o -name "*.sv" \) | sort | uniq))

    for file in $(ls ${modules_list[@]}); do
        files+="$file "
    done

    echo "$files"
}

# $1: Path for RTL files
function getRTLModuleNames(){
    echo $(find $1 -type f \( -name "*.v" -o -name "*.sv" \) | sed -E 's/.*\/([^\/]+)\..*/\1/' | sort | uniq)
}



# $1: Path for project
function cleanProject(){
    find "$1" -type d -name "__pycache__" -exec rm -rf {} +

    rm -rf $1/sim_build
    rm -f $1/results.xml
    rm -f $1/Makefile
    rm -f $1/dump.vcd
    rm -f $1/timescale.v
}

# $1: File of iteration
function verilateModel(){
    verilator -Wno-WIDTHEXPAND -Wno-fatal --trace --x-assign unique --x-initial unique -cc --hierarchical $1 --top-module $(echo $1 | cut -d'.' -f1) >> verilator.log
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
    "viewCoverage")
        viewCoverage $2
        ;;
    "openEditor")
        openEditor $2
        ;;


    "getRTLFullFiles")
        getRTLFullFiles $2
        ;;
    "getRTLModuleNames")
        getRTLModuleNames $2
        ;;


    "cleanProject")
        cleanProject $2
        ;;
    "verilateModel")
        verilateModel $2
        ;;
    *)
        echo "[sys_commands] Unknown command: $1"
        ;;
esac

