#!/bin/bash

function viewTreeProject(){
    tree -C | less -R
}

function runGTKWave(){
    gtkwave $OUTSIM_DIR/dut_signals.vcd &> /dev/null &
}

function viewReport(){
    less $OUTSIM_DIR/uvmenv_report.log
}




case $1 in
    "viewTreeProject")
        viewTreeProject
        ;;
    "runGTKWave")
        runGTKWave
        ;;
    "viewReport")
        viewReport
        ;;
esac

