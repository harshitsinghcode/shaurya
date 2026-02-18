// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VKILL_SWITCH__SYMS_H_
#define VERILATED_VKILL_SWITCH__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vkill_switch.h"

// INCLUDE MODULE CLASSES
#include "Vkill_switch___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vkill_switch__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vkill_switch* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vkill_switch___024root         TOP;

    // CONSTRUCTORS
    Vkill_switch__Syms(VerilatedContext* contextp, const char* namep, Vkill_switch* modelp);
    ~Vkill_switch__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
