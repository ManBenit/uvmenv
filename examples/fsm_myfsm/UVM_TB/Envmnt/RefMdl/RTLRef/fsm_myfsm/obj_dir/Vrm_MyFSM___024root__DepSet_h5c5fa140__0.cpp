// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vrm_MyFSM.h for the primary calling header

#include "Vrm_MyFSM__pch.h"
#include "Vrm_MyFSM___024root.h"

void Vrm_MyFSM___024root___eval_act(Vrm_MyFSM___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vrm_MyFSM__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrm_MyFSM___024root___eval_act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vrm_MyFSM___024root___nba_sequent__TOP__0(Vrm_MyFSM___024root* vlSelf);

void Vrm_MyFSM___024root___eval_nba(Vrm_MyFSM___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vrm_MyFSM__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrm_MyFSM___024root___eval_nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vrm_MyFSM___024root___nba_sequent__TOP__0(vlSelf);
    }
}

extern const VlUnpacked<CData/*1:0*/, 16> Vrm_MyFSM__ConstPool__TABLE_hee287fa9_0;
extern const VlUnpacked<CData/*0:0*/, 16> Vrm_MyFSM__ConstPool__TABLE_h137fee09_0;

VL_INLINE_OPT void Vrm_MyFSM___024root___nba_sequent__TOP__0(Vrm_MyFSM___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vrm_MyFSM__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrm_MyFSM___024root___nba_sequent__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*3:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    // Body
    __Vtableidx1 = (((IData)(vlSelfRef.i_x) << 3U) 
                    | (((IData)(vlSelfRef.rm_MyFSM__DOT__state) 
                        << 1U) | (IData)(vlSelfRef.i_rst_n)));
    vlSelfRef.rm_MyFSM__DOT__state = Vrm_MyFSM__ConstPool__TABLE_hee287fa9_0
        [__Vtableidx1];
    vlSelfRef.o_y = Vrm_MyFSM__ConstPool__TABLE_h137fee09_0
        [__Vtableidx1];
    vlSelfRef.o_state = vlSelfRef.rm_MyFSM__DOT__state;
}

void Vrm_MyFSM___024root___eval_triggers__act(Vrm_MyFSM___024root* vlSelf);

bool Vrm_MyFSM___024root___eval_phase__act(Vrm_MyFSM___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vrm_MyFSM__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrm_MyFSM___024root___eval_phase__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<2> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vrm_MyFSM___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vrm_MyFSM___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vrm_MyFSM___024root___eval_phase__nba(Vrm_MyFSM___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vrm_MyFSM__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrm_MyFSM___024root___eval_phase__nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vrm_MyFSM___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vrm_MyFSM___024root___dump_triggers__nba(Vrm_MyFSM___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vrm_MyFSM___024root___dump_triggers__act(Vrm_MyFSM___024root* vlSelf);
#endif  // VL_DEBUG

void Vrm_MyFSM___024root___eval(Vrm_MyFSM___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vrm_MyFSM__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrm_MyFSM___024root___eval\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vrm_MyFSM___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("rm_MyFSM.v", 9, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelfRef.__VactIterCount))) {
#ifdef VL_DEBUG
                Vrm_MyFSM___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("rm_MyFSM.v", 9, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vrm_MyFSM___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vrm_MyFSM___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vrm_MyFSM___024root___eval_debug_assertions(Vrm_MyFSM___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vrm_MyFSM__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrm_MyFSM___024root___eval_debug_assertions\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY((vlSelfRef.i_clk & 0xfeU))) {
        Verilated::overWidthError("i_clk");}
    if (VL_UNLIKELY((vlSelfRef.i_rst_n & 0xfeU))) {
        Verilated::overWidthError("i_rst_n");}
    if (VL_UNLIKELY((vlSelfRef.i_x & 0xfeU))) {
        Verilated::overWidthError("i_x");}
}
#endif  // VL_DEBUG
