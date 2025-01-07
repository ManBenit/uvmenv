// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VRM_MYFSM__SYMS_H_
#define VERILATED_VRM_MYFSM__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vrm_MyFSM.h"

// INCLUDE MODULE CLASSES
#include "Vrm_MyFSM___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vrm_MyFSM__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vrm_MyFSM* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vrm_MyFSM___024root            TOP;

    // CONSTRUCTORS
    Vrm_MyFSM__Syms(VerilatedContext* contextp, const char* namep, Vrm_MyFSM* modelp);
    ~Vrm_MyFSM__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
