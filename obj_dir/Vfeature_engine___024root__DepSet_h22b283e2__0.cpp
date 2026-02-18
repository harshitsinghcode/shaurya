// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vfeature_engine.h for the primary calling header

#include "Vfeature_engine__pch.h"
#include "Vfeature_engine__Syms.h"
#include "Vfeature_engine___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vfeature_engine___024root___dump_triggers__act(Vfeature_engine___024root* vlSelf);
#endif  // VL_DEBUG

void Vfeature_engine___024root___eval_triggers__act(Vfeature_engine___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vfeature_engine__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfeature_engine___024root___eval_triggers__act\n"); );
    // Body
    vlSelf->__VactTriggered.set(0U, ((IData)(vlSelf->clk) 
                                     & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__clk__0))));
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vfeature_engine___024root___dump_triggers__act(vlSelf);
    }
#endif
}
