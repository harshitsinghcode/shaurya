// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VFEATURE_ENGINE__SYMS_H_
#define VERILATED_VFEATURE_ENGINE__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vfeature_engine.h"

// INCLUDE MODULE CLASSES
#include "Vfeature_engine___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vfeature_engine__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vfeature_engine* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vfeature_engine___024root      TOP;

    // CONSTRUCTORS
    Vfeature_engine__Syms(VerilatedContext* contextp, const char* namep, Vfeature_engine* modelp);
    ~Vfeature_engine__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
