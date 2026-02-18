// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vrisk_firewall.h for the primary calling header

#include "Vrisk_firewall__pch.h"
#include "Vrisk_firewall___024root.h"

VL_ATTR_COLD void Vrisk_firewall___024root___eval_static(Vrisk_firewall___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrisk_firewall__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrisk_firewall___024root___eval_static\n"); );
}

VL_ATTR_COLD void Vrisk_firewall___024root___eval_initial(Vrisk_firewall___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrisk_firewall__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrisk_firewall___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
}

VL_ATTR_COLD void Vrisk_firewall___024root___eval_final(Vrisk_firewall___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrisk_firewall__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrisk_firewall___024root___eval_final\n"); );
}

VL_ATTR_COLD void Vrisk_firewall___024root___eval_settle(Vrisk_firewall___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrisk_firewall__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrisk_firewall___024root___eval_settle\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vrisk_firewall___024root___dump_triggers__act(Vrisk_firewall___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrisk_firewall__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrisk_firewall___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vrisk_firewall___024root___dump_triggers__nba(Vrisk_firewall___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrisk_firewall__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrisk_firewall___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vrisk_firewall___024root___ctor_var_reset(Vrisk_firewall___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrisk_firewall__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrisk_firewall___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->price = VL_RAND_RESET_I(32);
    vlSelf->safe_to_trade = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_RAND_RESET_I(1);
}
