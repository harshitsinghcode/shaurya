// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vrate_limiter.h for the primary calling header

#ifndef VERILATED_VRATE_LIMITER___024ROOT_H_
#define VERILATED_VRATE_LIMITER___024ROOT_H_  // guard

#include "verilated.h"


class Vrate_limiter__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vrate_limiter___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(trade_request,0,0);
    VL_OUT8(trade_approved,0,0);
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VactContinue;
    SData/*15:0*/ rate_limiter__DOT__tokens;
    SData/*15:0*/ rate_limiter__DOT__clock_ticks;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vrate_limiter__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vrate_limiter___024root(Vrate_limiter__Syms* symsp, const char* v__name);
    ~Vrate_limiter___024root();
    VL_UNCOPYABLE(Vrate_limiter___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
