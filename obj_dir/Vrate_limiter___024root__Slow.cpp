// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vrate_limiter.h for the primary calling header

#include "Vrate_limiter__pch.h"
#include "Vrate_limiter__Syms.h"
#include "Vrate_limiter___024root.h"

void Vrate_limiter___024root___ctor_var_reset(Vrate_limiter___024root* vlSelf);

Vrate_limiter___024root::Vrate_limiter___024root(Vrate_limiter__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vrate_limiter___024root___ctor_var_reset(this);
}

void Vrate_limiter___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vrate_limiter___024root::~Vrate_limiter___024root() {
}
