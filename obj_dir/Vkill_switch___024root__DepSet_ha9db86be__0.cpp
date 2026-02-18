// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vkill_switch.h for the primary calling header

#include "Vkill_switch__pch.h"
#include "Vkill_switch__Syms.h"
#include "Vkill_switch___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vkill_switch___024root___dump_triggers__act(Vkill_switch___024root* vlSelf);
#endif  // VL_DEBUG

void Vkill_switch___024root___eval_triggers__act(Vkill_switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vkill_switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vkill_switch___024root___eval_triggers__act\n"); );
    // Body
    vlSelf->__VactTriggered.set(0U, ((IData)(vlSelf->clk) 
                                     & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__clk__0))));
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vkill_switch___024root___dump_triggers__act(vlSelf);
    }
#endif
}
