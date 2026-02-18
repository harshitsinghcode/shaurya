// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VRATE_LIMITER__SYMS_H_
#define VERILATED_VRATE_LIMITER__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vrate_limiter.h"

// INCLUDE MODULE CLASSES
#include "Vrate_limiter___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vrate_limiter__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vrate_limiter* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vrate_limiter___024root        TOP;

    // CONSTRUCTORS
    Vrate_limiter__Syms(VerilatedContext* contextp, const char* namep, Vrate_limiter* modelp);
    ~Vrate_limiter__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
