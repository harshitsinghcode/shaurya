// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vfeature_engine.h for the primary calling header

#include "Vfeature_engine__pch.h"
#include "Vfeature_engine___024root.h"

VL_ATTR_COLD void Vfeature_engine___024root___eval_static__TOP(Vfeature_engine___024root* vlSelf);

VL_ATTR_COLD void Vfeature_engine___024root___eval_static(Vfeature_engine___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfeature_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfeature_engine___024root___eval_static\n"); );
    // Body
    Vfeature_engine___024root___eval_static__TOP(vlSelf);
}

VL_ATTR_COLD void Vfeature_engine___024root___eval_static__TOP(Vfeature_engine___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfeature_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfeature_engine___024root___eval_static__TOP\n"); );
    // Body
    vlSelf->feature_engine__DOT__last_price = 0U;
}

VL_ATTR_COLD void Vfeature_engine___024root___eval_initial(Vfeature_engine___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfeature_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfeature_engine___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
}

VL_ATTR_COLD void Vfeature_engine___024root___eval_final(Vfeature_engine___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfeature_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfeature_engine___024root___eval_final\n"); );
}

VL_ATTR_COLD void Vfeature_engine___024root___eval_settle(Vfeature_engine___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfeature_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfeature_engine___024root___eval_settle\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vfeature_engine___024root___dump_triggers__act(Vfeature_engine___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfeature_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfeature_engine___024root___dump_triggers__act\n"); );
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
VL_ATTR_COLD void Vfeature_engine___024root___dump_triggers__nba(Vfeature_engine___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfeature_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfeature_engine___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vfeature_engine___024root___ctor_var_reset(Vfeature_engine___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfeature_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfeature_engine___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->new_price = VL_RAND_RESET_I(32);
    vlSelf->price_delta = VL_RAND_RESET_I(32);
    vlSelf->feature_engine__DOT__last_price = VL_RAND_RESET_I(32);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_RAND_RESET_I(1);
}
