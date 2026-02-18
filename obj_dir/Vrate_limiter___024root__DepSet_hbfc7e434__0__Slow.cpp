// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vrate_limiter.h for the primary calling header

#include "Vrate_limiter__pch.h"
#include "Vrate_limiter___024root.h"

VL_ATTR_COLD void Vrate_limiter___024root___eval_static__TOP(Vrate_limiter___024root* vlSelf);

VL_ATTR_COLD void Vrate_limiter___024root___eval_static(Vrate_limiter___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrate_limiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrate_limiter___024root___eval_static\n"); );
    // Body
    Vrate_limiter___024root___eval_static__TOP(vlSelf);
}

VL_ATTR_COLD void Vrate_limiter___024root___eval_static__TOP(Vrate_limiter___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrate_limiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrate_limiter___024root___eval_static__TOP\n"); );
    // Body
    vlSelf->rate_limiter__DOT__tokens = 0x64U;
    vlSelf->rate_limiter__DOT__clock_ticks = 0U;
}

VL_ATTR_COLD void Vrate_limiter___024root___eval_initial(Vrate_limiter___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrate_limiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrate_limiter___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
}

VL_ATTR_COLD void Vrate_limiter___024root___eval_final(Vrate_limiter___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrate_limiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrate_limiter___024root___eval_final\n"); );
}

VL_ATTR_COLD void Vrate_limiter___024root___eval_settle(Vrate_limiter___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrate_limiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrate_limiter___024root___eval_settle\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vrate_limiter___024root___dump_triggers__act(Vrate_limiter___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrate_limiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrate_limiter___024root___dump_triggers__act\n"); );
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
VL_ATTR_COLD void Vrate_limiter___024root___dump_triggers__nba(Vrate_limiter___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrate_limiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrate_limiter___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vrate_limiter___024root___ctor_var_reset(Vrate_limiter___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrate_limiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrate_limiter___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->trade_request = VL_RAND_RESET_I(1);
    vlSelf->trade_approved = VL_RAND_RESET_I(1);
    vlSelf->rate_limiter__DOT__tokens = VL_RAND_RESET_I(16);
    vlSelf->rate_limiter__DOT__clock_ticks = VL_RAND_RESET_I(16);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_RAND_RESET_I(1);
}
