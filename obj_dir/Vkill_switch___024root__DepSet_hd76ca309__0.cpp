// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vkill_switch.h for the primary calling header

#include "Vkill_switch__pch.h"
#include "Vkill_switch___024root.h"

void Vkill_switch___024root___eval_act(Vkill_switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vkill_switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vkill_switch___024root___eval_act\n"); );
}

VL_INLINE_OPT void Vkill_switch___024root___nba_sequent__TOP__0(Vkill_switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vkill_switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vkill_switch___024root___nba_sequent__TOP__0\n"); );
    // Body
    if (vlSelf->reset) {
        vlSelf->system_halted = 0U;
    } else if (((IData)(vlSelf->software_panic) | (vlSelf->latency_us 
                                                   > vlSelf->max_latency))) {
        vlSelf->system_halted = 1U;
    }
}

void Vkill_switch___024root___eval_nba(Vkill_switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vkill_switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vkill_switch___024root___eval_nba\n"); );
    // Body
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vkill_switch___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vkill_switch___024root___eval_triggers__act(Vkill_switch___024root* vlSelf);

bool Vkill_switch___024root___eval_phase__act(Vkill_switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vkill_switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vkill_switch___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vkill_switch___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vkill_switch___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vkill_switch___024root___eval_phase__nba(Vkill_switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vkill_switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vkill_switch___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vkill_switch___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vkill_switch___024root___dump_triggers__nba(Vkill_switch___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vkill_switch___024root___dump_triggers__act(Vkill_switch___024root* vlSelf);
#endif  // VL_DEBUG

void Vkill_switch___024root___eval(Vkill_switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vkill_switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vkill_switch___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vkill_switch___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("kill_switch.v", 1, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vkill_switch___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("kill_switch.v", 1, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vkill_switch___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vkill_switch___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vkill_switch___024root___eval_debug_assertions(Vkill_switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vkill_switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vkill_switch___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->reset & 0xfeU))) {
        Verilated::overWidthError("reset");}
    if (VL_UNLIKELY((vlSelf->software_panic & 0xfeU))) {
        Verilated::overWidthError("software_panic");}
}
#endif  // VL_DEBUG
