// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vrm_MyFSM__pch.h"

//============================================================
// Constructors

Vrm_MyFSM::Vrm_MyFSM(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vrm_MyFSM__Syms(contextp(), _vcname__, this)}
    , i_clk{vlSymsp->TOP.i_clk}
    , i_rst_n{vlSymsp->TOP.i_rst_n}
    , i_x{vlSymsp->TOP.i_x}
    , o_y{vlSymsp->TOP.o_y}
    , o_state{vlSymsp->TOP.o_state}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vrm_MyFSM::Vrm_MyFSM(const char* _vcname__)
    : Vrm_MyFSM(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vrm_MyFSM::~Vrm_MyFSM() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vrm_MyFSM___024root___eval_debug_assertions(Vrm_MyFSM___024root* vlSelf);
#endif  // VL_DEBUG
void Vrm_MyFSM___024root___eval_static(Vrm_MyFSM___024root* vlSelf);
void Vrm_MyFSM___024root___eval_initial(Vrm_MyFSM___024root* vlSelf);
void Vrm_MyFSM___024root___eval_settle(Vrm_MyFSM___024root* vlSelf);
void Vrm_MyFSM___024root___eval(Vrm_MyFSM___024root* vlSelf);

void Vrm_MyFSM::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vrm_MyFSM::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vrm_MyFSM___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vrm_MyFSM___024root___eval_static(&(vlSymsp->TOP));
        Vrm_MyFSM___024root___eval_initial(&(vlSymsp->TOP));
        Vrm_MyFSM___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vrm_MyFSM___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vrm_MyFSM::eventsPending() { return false; }

uint64_t Vrm_MyFSM::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vrm_MyFSM::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vrm_MyFSM___024root___eval_final(Vrm_MyFSM___024root* vlSelf);

VL_ATTR_COLD void Vrm_MyFSM::final() {
    Vrm_MyFSM___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vrm_MyFSM::hierName() const { return vlSymsp->name(); }
const char* Vrm_MyFSM::modelName() const { return "Vrm_MyFSM"; }
unsigned Vrm_MyFSM::threads() const { return 1; }
void Vrm_MyFSM::prepareClone() const { contextp()->prepareClone(); }
void Vrm_MyFSM::atClone() const {
    contextp()->threadPoolpOnClone();
}
