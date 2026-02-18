// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VRISK_FIREWALL__SYMS_H_
#define VERILATED_VRISK_FIREWALL__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vrisk_firewall.h"

// INCLUDE MODULE CLASSES
#include "Vrisk_firewall___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vrisk_firewall__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vrisk_firewall* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vrisk_firewall___024root       TOP;

    // CONSTRUCTORS
    Vrisk_firewall__Syms(VerilatedContext* contextp, const char* namep, Vrisk_firewall* modelp);
    ~Vrisk_firewall__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
