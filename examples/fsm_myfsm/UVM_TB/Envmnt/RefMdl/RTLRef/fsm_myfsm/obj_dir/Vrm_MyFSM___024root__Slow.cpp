// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vrm_MyFSM.h for the primary calling header

#include "Vrm_MyFSM__pch.h"
#include "Vrm_MyFSM__Syms.h"
#include "Vrm_MyFSM___024root.h"

void Vrm_MyFSM___024root___ctor_var_reset(Vrm_MyFSM___024root* vlSelf);

Vrm_MyFSM___024root::Vrm_MyFSM___024root(Vrm_MyFSM__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vrm_MyFSM___024root___ctor_var_reset(this);
}

void Vrm_MyFSM___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vrm_MyFSM___024root::~Vrm_MyFSM___024root() {
}
