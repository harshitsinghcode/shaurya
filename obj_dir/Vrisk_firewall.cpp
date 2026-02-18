// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vrisk_firewall__pch.h"

//============================================================
// Constructors

Vrisk_firewall::Vrisk_firewall(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vrisk_firewall__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , safe_to_trade{vlSymsp->TOP.safe_to_trade}
    , price{vlSymsp->TOP.price}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vrisk_firewall::Vrisk_firewall(const char* _vcname__)
    : Vrisk_firewall(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vrisk_firewall::~Vrisk_firewall() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vrisk_firewall___024root___eval_debug_assertions(Vrisk_firewall___024root* vlSelf);
#endif  // VL_DEBUG
void Vrisk_firewall___024root___eval_static(Vrisk_firewall___024root* vlSelf);
void Vrisk_firewall___024root___eval_initial(Vrisk_firewall___024root* vlSelf);
void Vrisk_firewall___024root___eval_settle(Vrisk_firewall___024root* vlSelf);
void Vrisk_firewall___024root___eval(Vrisk_firewall___024root* vlSelf);

void Vrisk_firewall::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vrisk_firewall::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vrisk_firewall___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vrisk_firewall___024root___eval_static(&(vlSymsp->TOP));
        Vrisk_firewall___024root___eval_initial(&(vlSymsp->TOP));
        Vrisk_firewall___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vrisk_firewall___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vrisk_firewall::eventsPending() { return false; }

uint64_t Vrisk_firewall::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vrisk_firewall::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vrisk_firewall___024root___eval_final(Vrisk_firewall___024root* vlSelf);

VL_ATTR_COLD void Vrisk_firewall::final() {
    Vrisk_firewall___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vrisk_firewall::hierName() const { return vlSymsp->name(); }
const char* Vrisk_firewall::modelName() const { return "Vrisk_firewall"; }
unsigned Vrisk_firewall::threads() const { return 1; }
void Vrisk_firewall::prepareClone() const { contextp()->prepareClone(); }
void Vrisk_firewall::atClone() const {
    contextp()->threadPoolpOnClone();
}

//============================================================
// Trace configuration

VL_ATTR_COLD void Vrisk_firewall::trace(VerilatedVcdC* tfp, int levels, int options) {
    vl_fatal(__FILE__, __LINE__, __FILE__,"'Vrisk_firewall::trace()' called on model that was Verilated without --trace option");
}
