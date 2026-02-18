// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vrate_limiter.h for the primary calling header

#include "Vrate_limiter__pch.h"
#include "Vrate_limiter__Syms.h"
#include "Vrate_limiter___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vrate_limiter___024root___dump_triggers__act(Vrate_limiter___024root* vlSelf);
#endif  // VL_DEBUG

void Vrate_limiter___024root___eval_triggers__act(Vrate_limiter___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrate_limiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrate_limiter___024root___eval_triggers__act\n"); );
    // Body
    vlSelf->__VactTriggered.set(0U, ((IData)(vlSelf->clk) 
                                     & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__clk__0))));
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vrate_limiter___024root___dump_triggers__act(vlSelf);
    }
#endif
}
