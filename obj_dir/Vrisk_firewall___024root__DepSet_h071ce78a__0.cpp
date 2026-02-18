// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vrisk_firewall.h for the primary calling header

#include "Vrisk_firewall__pch.h"
#include "Vrisk_firewall__Syms.h"
#include "Vrisk_firewall___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vrisk_firewall___024root___dump_triggers__act(Vrisk_firewall___024root* vlSelf);
#endif  // VL_DEBUG

void Vrisk_firewall___024root___eval_triggers__act(Vrisk_firewall___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vrisk_firewall__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrisk_firewall___024root___eval_triggers__act\n"); );
    // Body
    vlSelf->__VactTriggered.set(0U, ((IData)(vlSelf->clk) 
                                     & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__clk__0))));
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vrisk_firewall___024root___dump_triggers__act(vlSelf);
    }
#endif
}
