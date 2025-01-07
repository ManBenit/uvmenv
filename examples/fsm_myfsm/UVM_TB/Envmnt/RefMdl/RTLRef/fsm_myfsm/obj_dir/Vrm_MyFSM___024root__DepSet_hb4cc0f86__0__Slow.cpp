// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vrm_MyFSM.h for the primary calling header

#include "Vrm_MyFSM__pch.h"
#include "Vrm_MyFSM__Syms.h"
#include "Vrm_MyFSM___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vrm_MyFSM___024root___dump_triggers__stl(Vrm_MyFSM___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vrm_MyFSM___024root___eval_triggers__stl(Vrm_MyFSM___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vrm_MyFSM__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrm_MyFSM___024root___eval_triggers__stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered.set(0U, (IData)(vlSelfRef.__VstlFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vrm_MyFSM___024root___dump_triggers__stl(vlSelf);
    }
#endif
}
