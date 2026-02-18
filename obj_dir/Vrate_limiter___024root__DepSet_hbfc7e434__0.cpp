// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vrate_limiter.h for the primary calling header

#include "Vrate_limiter__pch.h"
#include "Vrate_limiter___024root.h"

void Vrate_limiter___024root___eval_act(Vrate_limiter___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrate_limiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrate_limiter___024root___eval_act\n"); );
}

VL_INLINE_OPT void Vrate_limiter___024root___nba_sequent__TOP__0(Vrate_limiter___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrate_limiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrate_limiter___024root___nba_sequent__TOP__0\n"); );
    // Init
    SData/*15:0*/ __Vdly__rate_limiter__DOT__clock_ticks;
    __Vdly__rate_limiter__DOT__clock_ticks = 0;
    SData/*15:0*/ __Vdly__rate_limiter__DOT__tokens;
    __Vdly__rate_limiter__DOT__tokens = 0;
    // Body
    __Vdly__rate_limiter__DOT__tokens = vlSelf->rate_limiter__DOT__tokens;
    __Vdly__rate_limiter__DOT__clock_ticks = vlSelf->rate_limiter__DOT__clock_ticks;
    __Vdly__rate_limiter__DOT__clock_ticks = (0xffffU 
                                              & ((IData)(1U) 
                                                 + (IData)(vlSelf->rate_limiter__DOT__clock_ticks)));
    if ((0x3e8U == (IData)(vlSelf->rate_limiter__DOT__clock_ticks))) {
        if ((0x64U > (IData)(vlSelf->rate_limiter__DOT__tokens))) {
            __Vdly__rate_limiter__DOT__tokens = (0xffffU 
                                                 & ((IData)(1U) 
                                                    + (IData)(vlSelf->rate_limiter__DOT__tokens)));
        }
        __Vdly__rate_limiter__DOT__clock_ticks = 0U;
    }
    if (((IData)(vlSelf->trade_request) & (0U < (IData)(vlSelf->rate_limiter__DOT__tokens)))) {
        __Vdly__rate_limiter__DOT__tokens = (0xffffU 
                                             & ((IData)(vlSelf->rate_limiter__DOT__tokens) 
                                                - (IData)(1U)));
        vlSelf->trade_approved = 1U;
    } else {
        vlSelf->trade_approved = 0U;
    }
    vlSelf->rate_limiter__DOT__clock_ticks = __Vdly__rate_limiter__DOT__clock_ticks;
    vlSelf->rate_limiter__DOT__tokens = __Vdly__rate_limiter__DOT__tokens;
}

void Vrate_limiter___024root___eval_nba(Vrate_limiter___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrate_limiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrate_limiter___024root___eval_nba\n"); );
    // Body
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vrate_limiter___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vrate_limiter___024root___eval_triggers__act(Vrate_limiter___024root* vlSelf);

bool Vrate_limiter___024root___eval_phase__act(Vrate_limiter___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrate_limiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrate_limiter___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vrate_limiter___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vrate_limiter___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vrate_limiter___024root___eval_phase__nba(Vrate_limiter___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrate_limiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrate_limiter___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vrate_limiter___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vrate_limiter___024root___dump_triggers__nba(Vrate_limiter___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vrate_limiter___024root___dump_triggers__act(Vrate_limiter___024root* vlSelf);
#endif  // VL_DEBUG

void Vrate_limiter___024root___eval(Vrate_limiter___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrate_limiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrate_limiter___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vrate_limiter___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("rate_limiter.v", 1, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vrate_limiter___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("rate_limiter.v", 1, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vrate_limiter___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vrate_limiter___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vrate_limiter___024root___eval_debug_assertions(Vrate_limiter___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrate_limiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrate_limiter___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->trade_request & 0xfeU))) {
        Verilated::overWidthError("trade_request");}
}
#endif  // VL_DEBUG
