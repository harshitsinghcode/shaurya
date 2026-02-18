// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vfeature_engine.h for the primary calling header

#include "Vfeature_engine__pch.h"
#include "Vfeature_engine___024root.h"

void Vfeature_engine___024root___eval_act(Vfeature_engine___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfeature_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfeature_engine___024root___eval_act\n"); );
}

VL_INLINE_OPT void Vfeature_engine___024root___nba_sequent__TOP__0(Vfeature_engine___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfeature_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfeature_engine___024root___nba_sequent__TOP__0\n"); );
    // Body
    vlSelf->price_delta = ((0U == vlSelf->feature_engine__DOT__last_price)
                            ? 0U : (vlSelf->new_price 
                                    - vlSelf->feature_engine__DOT__last_price));
    vlSelf->feature_engine__DOT__last_price = vlSelf->new_price;
}

void Vfeature_engine___024root___eval_nba(Vfeature_engine___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfeature_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfeature_engine___024root___eval_nba\n"); );
    // Body
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vfeature_engine___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vfeature_engine___024root___eval_triggers__act(Vfeature_engine___024root* vlSelf);

bool Vfeature_engine___024root___eval_phase__act(Vfeature_engine___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfeature_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfeature_engine___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vfeature_engine___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vfeature_engine___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vfeature_engine___024root___eval_phase__nba(Vfeature_engine___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfeature_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfeature_engine___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vfeature_engine___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vfeature_engine___024root___dump_triggers__nba(Vfeature_engine___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vfeature_engine___024root___dump_triggers__act(Vfeature_engine___024root* vlSelf);
#endif  // VL_DEBUG

void Vfeature_engine___024root___eval(Vfeature_engine___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfeature_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfeature_engine___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vfeature_engine___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("feature_engine.v", 1, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vfeature_engine___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("feature_engine.v", 1, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vfeature_engine___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vfeature_engine___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vfeature_engine___024root___eval_debug_assertions(Vfeature_engine___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfeature_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfeature_engine___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
}
#endif  // VL_DEBUG
