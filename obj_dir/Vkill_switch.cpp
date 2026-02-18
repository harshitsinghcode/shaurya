// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vkill_switch__pch.h"

//============================================================
// Constructors

Vkill_switch::Vkill_switch(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vkill_switch__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , reset{vlSymsp->TOP.reset}
    , software_panic{vlSymsp->TOP.software_panic}
    , system_halted{vlSymsp->TOP.system_halted}
    , latency_us{vlSymsp->TOP.latency_us}
    , max_latency{vlSymsp->TOP.max_latency}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vkill_switch::Vkill_switch(const char* _vcname__)
    : Vkill_switch(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vkill_switch::~Vkill_switch() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vkill_switch___024root___eval_debug_assertions(Vkill_switch___024root* vlSelf);
#endif  // VL_DEBUG
void Vkill_switch___024root___eval_static(Vkill_switch___024root* vlSelf);
void Vkill_switch___024root___eval_initial(Vkill_switch___024root* vlSelf);
void Vkill_switch___024root___eval_settle(Vkill_switch___024root* vlSelf);
void Vkill_switch___024root___eval(Vkill_switch___024root* vlSelf);

void Vkill_switch::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vkill_switch::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vkill_switch___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vkill_switch___024root___eval_static(&(vlSymsp->TOP));
        Vkill_switch___024root___eval_initial(&(vlSymsp->TOP));
        Vkill_switch___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vkill_switch___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vkill_switch::eventsPending() { return false; }

uint64_t Vkill_switch::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vkill_switch::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vkill_switch___024root___eval_final(Vkill_switch___024root* vlSelf);

VL_ATTR_COLD void Vkill_switch::final() {
    Vkill_switch___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vkill_switch::hierName() const { return vlSymsp->name(); }
const char* Vkill_switch::modelName() const { return "Vkill_switch"; }
unsigned Vkill_switch::threads() const { return 1; }
void Vkill_switch::prepareClone() const { contextp()->prepareClone(); }
void Vkill_switch::atClone() const {
    contextp()->threadPoolpOnClone();
}

//============================================================
// Trace configuration

VL_ATTR_COLD void Vkill_switch::trace(VerilatedVcdC* tfp, int levels, int options) {
    vl_fatal(__FILE__, __LINE__, __FILE__,"'Vkill_switch::trace()' called on model that was Verilated without --trace option");
}
