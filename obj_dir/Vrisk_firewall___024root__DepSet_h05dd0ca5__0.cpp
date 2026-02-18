// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vrisk_firewall.h for the primary calling header

#include "Vrisk_firewall__pch.h"
#include "Vrisk_firewall___024root.h"

void Vrisk_firewall___024root___eval_act(Vrisk_firewall___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrisk_firewall__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrisk_firewall___024root___eval_act\n"); );
}

VL_INLINE_OPT void Vrisk_firewall___024root___nba_sequent__TOP__0(Vrisk_firewall___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrisk_firewall__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrisk_firewall___024root___nba_sequent__TOP__0\n"); );
    // Body
    vlSelf->safe_to_trade = (0x3e8U >= vlSelf->price);
}

void Vrisk_firewall___024root___eval_nba(Vrisk_firewall___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrisk_firewall__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrisk_firewall___024root___eval_nba\n"); );
    // Body
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vrisk_firewall___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vrisk_firewall___024root___eval_triggers__act(Vrisk_firewall___024root* vlSelf);

bool Vrisk_firewall___024root___eval_phase__act(Vrisk_firewall___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrisk_firewall__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrisk_firewall___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vrisk_firewall___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vrisk_firewall___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vrisk_firewall___024root___eval_phase__nba(Vrisk_firewall___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrisk_firewall__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrisk_firewall___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vrisk_firewall___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vrisk_firewall___024root___dump_triggers__nba(Vrisk_firewall___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vrisk_firewall___024root___dump_triggers__act(Vrisk_firewall___024root* vlSelf);
#endif  // VL_DEBUG

void Vrisk_firewall___024root___eval(Vrisk_firewall___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrisk_firewall__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrisk_firewall___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vrisk_firewall___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("risk_firewall.v", 2, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vrisk_firewall___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("risk_firewall.v", 2, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vrisk_firewall___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vrisk_firewall___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vrisk_firewall___024root___eval_debug_assertions(Vrisk_firewall___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrisk_firewall__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrisk_firewall___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
}
#endif  // VL_DEBUG
