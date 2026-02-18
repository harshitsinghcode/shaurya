// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vrisk_firewall.h for the primary calling header

#include "Vrisk_firewall__pch.h"
#include "Vrisk_firewall__Syms.h"
#include "Vrisk_firewall___024root.h"

void Vrisk_firewall___024root___ctor_var_reset(Vrisk_firewall___024root* vlSelf);

Vrisk_firewall___024root::Vrisk_firewall___024root(Vrisk_firewall__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vrisk_firewall___024root___ctor_var_reset(this);
}

void Vrisk_firewall___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vrisk_firewall___024root::~Vrisk_firewall___024root() {
}
