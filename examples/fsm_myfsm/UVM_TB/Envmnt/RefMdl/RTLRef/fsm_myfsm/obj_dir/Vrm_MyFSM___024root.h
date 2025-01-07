// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vrm_MyFSM.h for the primary calling header

#ifndef VERILATED_VRM_MYFSM___024ROOT_H_
#define VERILATED_VRM_MYFSM___024ROOT_H_  // guard

#include "verilated.h"


class Vrm_MyFSM__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vrm_MyFSM___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(i_clk,0,0);
    VL_IN8(i_rst_n,0,0);
    VL_IN8(i_x,0,0);
    VL_OUT8(o_y,0,0);
    VL_OUT8(o_state,1,0);
    CData/*1:0*/ rm_MyFSM__DOT__state;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__i_clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__i_rst_n__0;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<2> __VactTriggered;
    VlTriggerVec<2> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vrm_MyFSM__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vrm_MyFSM___024root(Vrm_MyFSM__Syms* symsp, const char* v__name);
    ~Vrm_MyFSM___024root();
    VL_UNCOPYABLE(Vrm_MyFSM___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
