// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vrate_limiter__pch.h"

//============================================================
// Constructors

Vrate_limiter::Vrate_limiter(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vrate_limiter__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , trade_request{vlSymsp->TOP.trade_request}
    , trade_approved{vlSymsp->TOP.trade_approved}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vrate_limiter::Vrate_limiter(const char* _vcname__)
    : Vrate_limiter(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vrate_limiter::~Vrate_limiter() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vrate_limiter___024root___eval_debug_assertions(Vrate_limiter___024root* vlSelf);
#endif  // VL_DEBUG
void Vrate_limiter___024root___eval_static(Vrate_limiter___024root* vlSelf);
void Vrate_limiter___024root___eval_initial(Vrate_limiter___024root* vlSelf);
void Vrate_limiter___024root___eval_settle(Vrate_limiter___024root* vlSelf);
void Vrate_limiter___024root___eval(Vrate_limiter___024root* vlSelf);

void Vrate_limiter::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vrate_limiter::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vrate_limiter___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vrate_limiter___024root___eval_static(&(vlSymsp->TOP));
        Vrate_limiter___024root___eval_initial(&(vlSymsp->TOP));
        Vrate_limiter___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vrate_limiter___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vrate_limiter::eventsPending() { return false; }

uint64_t Vrate_limiter::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vrate_limiter::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vrate_limiter___024root___eval_final(Vrate_limiter___024root* vlSelf);

VL_ATTR_COLD void Vrate_limiter::final() {
    Vrate_limiter___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vrate_limiter::hierName() const { return vlSymsp->name(); }
const char* Vrate_limiter::modelName() const { return "Vrate_limiter"; }
unsigned Vrate_limiter::threads() const { return 1; }
void Vrate_limiter::prepareClone() const { contextp()->prepareClone(); }
void Vrate_limiter::atClone() const {
    contextp()->threadPoolpOnClone();
}

//============================================================
// Trace configuration

VL_ATTR_COLD void Vrate_limiter::trace(VerilatedVcdC* tfp, int levels, int options) {
    vl_fatal(__FILE__, __LINE__, __FILE__,"'Vrate_limiter::trace()' called on model that was Verilated without --trace option");
}
