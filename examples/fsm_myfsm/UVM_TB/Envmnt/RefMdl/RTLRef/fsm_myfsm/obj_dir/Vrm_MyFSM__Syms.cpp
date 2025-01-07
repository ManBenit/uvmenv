// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vrm_MyFSM__pch.h"
#include "Vrm_MyFSM.h"
#include "Vrm_MyFSM___024root.h"

// FUNCTIONS
Vrm_MyFSM__Syms::~Vrm_MyFSM__Syms()
{
}

Vrm_MyFSM__Syms::Vrm_MyFSM__Syms(VerilatedContext* contextp, const char* namep, Vrm_MyFSM* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
{
        // Check resources
        Verilated::stackCheck(20);
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-12);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
}
