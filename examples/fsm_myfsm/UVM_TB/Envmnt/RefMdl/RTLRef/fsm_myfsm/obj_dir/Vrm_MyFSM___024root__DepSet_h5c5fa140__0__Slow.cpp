// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vrm_MyFSM.h for the primary calling header

#include "Vrm_MyFSM__pch.h"
#include "Vrm_MyFSM___024root.h"

VL_ATTR_COLD void Vrm_MyFSM___024root___eval_static(Vrm_MyFSM___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vrm_MyFSM__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrm_MyFSM___024root___eval_static\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vrm_MyFSM___024root___eval_initial(Vrm_MyFSM___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vrm_MyFSM__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrm_MyFSM___024root___eval_initial\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__i_clk__0 = vlSelfRef.i_clk;
    vlSelfRef.__Vtrigprevexpr___TOP__i_rst_n__0 = vlSelfRef.i_rst_n;
}

VL_ATTR_COLD void Vrm_MyFSM___024root___eval_final(Vrm_MyFSM___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vrm_MyFSM__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrm_MyFSM___024root___eval_final\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vrm_MyFSM___024root___dump_triggers__stl(Vrm_MyFSM___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vrm_MyFSM___024root___eval_phase__stl(Vrm_MyFSM___024root* vlSelf);

VL_ATTR_COLD void Vrm_MyFSM___024root___eval_settle(Vrm_MyFSM___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vrm_MyFSM__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrm_MyFSM___024root___eval_settle\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY((0x64U < __VstlIterCount))) {
#ifdef VL_DEBUG
            Vrm_MyFSM___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("rm_MyFSM.v", 9, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vrm_MyFSM___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vrm_MyFSM___024root___dump_triggers__stl(Vrm_MyFSM___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vrm_MyFSM__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrm_MyFSM___024root___dump_triggers__stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vrm_MyFSM___024root___stl_sequent__TOP__0(Vrm_MyFSM___024root* vlSelf);

VL_ATTR_COLD void Vrm_MyFSM___024root___eval_stl(Vrm_MyFSM___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vrm_MyFSM__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrm_MyFSM___024root___eval_stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vrm_MyFSM___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD void Vrm_MyFSM___024root___stl_sequent__TOP__0(Vrm_MyFSM___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vrm_MyFSM__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrm_MyFSM___024root___stl_sequent__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.o_state = vlSelfRef.rm_MyFSM__DOT__state;
}

VL_ATTR_COLD void Vrm_MyFSM___024root___eval_triggers__stl(Vrm_MyFSM___024root* vlSelf);

VL_ATTR_COLD bool Vrm_MyFSM___024root___eval_phase__stl(Vrm_MyFSM___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vrm_MyFSM__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrm_MyFSM___024root___eval_phase__stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vrm_MyFSM___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        Vrm_MyFSM___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vrm_MyFSM___024root___dump_triggers__act(Vrm_MyFSM___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vrm_MyFSM__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrm_MyFSM___024root___dump_triggers__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge i_clk)\n");
    }
    if ((2ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @(negedge i_rst_n)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vrm_MyFSM___024root___dump_triggers__nba(Vrm_MyFSM___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vrm_MyFSM__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrm_MyFSM___024root___dump_triggers__nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge i_clk)\n");
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @(negedge i_rst_n)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vrm_MyFSM___024root___ctor_var_reset(Vrm_MyFSM___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vrm_MyFSM__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrm_MyFSM___024root___ctor_var_reset\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->i_clk = VL_RAND_RESET_I(1);
    vlSelf->i_rst_n = VL_RAND_RESET_I(1);
    vlSelf->i_x = VL_RAND_RESET_I(1);
    vlSelf->o_y = VL_RAND_RESET_I(1);
    vlSelf->o_state = VL_RAND_RESET_I(2);
    vlSelf->rm_MyFSM__DOT__state = VL_RAND_RESET_I(2);
    vlSelf->__Vtrigprevexpr___TOP__i_clk__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__i_rst_n__0 = VL_RAND_RESET_I(1);
}
