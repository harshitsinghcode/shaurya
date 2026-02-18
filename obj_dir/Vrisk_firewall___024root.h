// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vrisk_firewall.h for the primary calling header

#ifndef VERILATED_VRISK_FIREWALL___024ROOT_H_
#define VERILATED_VRISK_FIREWALL___024ROOT_H_  // guard

#include "verilated.h"


class Vrisk_firewall__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vrisk_firewall___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_OUT8(safe_to_trade,0,0);
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VactContinue;
    VL_IN(price,31,0);
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vrisk_firewall__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vrisk_firewall___024root(Vrisk_firewall__Syms* symsp, const char* v__name);
    ~Vrisk_firewall___024root();
    VL_UNCOPYABLE(Vrisk_firewall___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
