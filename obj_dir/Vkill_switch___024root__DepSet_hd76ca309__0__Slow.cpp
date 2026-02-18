// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vkill_switch.h for the primary calling header

#include "Vkill_switch__pch.h"
#include "Vkill_switch___024root.h"

VL_ATTR_COLD void Vkill_switch___024root___eval_static(Vkill_switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vkill_switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vkill_switch___024root___eval_static\n"); );
}

VL_ATTR_COLD void Vkill_switch___024root___eval_initial(Vkill_switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vkill_switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vkill_switch___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
}

VL_ATTR_COLD void Vkill_switch___024root___eval_final(Vkill_switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vkill_switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vkill_switch___024root___eval_final\n"); );
}

VL_ATTR_COLD void Vkill_switch___024root___eval_settle(Vkill_switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vkill_switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vkill_switch___024root___eval_settle\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vkill_switch___024root___dump_triggers__act(Vkill_switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vkill_switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vkill_switch___024root___dump_triggers__act\n"); );
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
VL_ATTR_COLD void Vkill_switch___024root___dump_triggers__nba(Vkill_switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vkill_switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vkill_switch___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vkill_switch___024root___ctor_var_reset(Vkill_switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vkill_switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vkill_switch___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->reset = VL_RAND_RESET_I(1);
    vlSelf->software_panic = VL_RAND_RESET_I(1);
    vlSelf->latency_us = VL_RAND_RESET_I(32);
    vlSelf->max_latency = VL_RAND_RESET_I(32);
    vlSelf->system_halted = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_RAND_RESET_I(1);
}
