// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vkill_switch.h for the primary calling header

#ifndef VERILATED_VKILL_SWITCH___024ROOT_H_
#define VERILATED_VKILL_SWITCH___024ROOT_H_  // guard

#include "verilated.h"


class Vkill_switch__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vkill_switch___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(reset,0,0);
    VL_IN8(software_panic,0,0);
    VL_OUT8(system_halted,0,0);
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VactContinue;
    VL_IN(latency_us,31,0);
    VL_IN(max_latency,31,0);
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vkill_switch__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vkill_switch___024root(Vkill_switch__Syms* symsp, const char* v__name);
    ~Vkill_switch___024root();
    VL_UNCOPYABLE(Vkill_switch___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
