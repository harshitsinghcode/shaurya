// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vfeature_engine.h for the primary calling header

#ifndef VERILATED_VFEATURE_ENGINE___024ROOT_H_
#define VERILATED_VFEATURE_ENGINE___024ROOT_H_  // guard

#include "verilated.h"


class Vfeature_engine__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vfeature_engine___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VactContinue;
    VL_IN(new_price,31,0);
    VL_OUT(price_delta,31,0);
    IData/*31:0*/ feature_engine__DOT__last_price;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vfeature_engine__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vfeature_engine___024root(Vfeature_engine__Syms* symsp, const char* v__name);
    ~Vfeature_engine___024root();
    VL_UNCOPYABLE(Vfeature_engine___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
