// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vfeature_engine__pch.h"

//============================================================
// Constructors

Vfeature_engine::Vfeature_engine(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vfeature_engine__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , new_price{vlSymsp->TOP.new_price}
    , price_delta{vlSymsp->TOP.price_delta}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vfeature_engine::Vfeature_engine(const char* _vcname__)
    : Vfeature_engine(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vfeature_engine::~Vfeature_engine() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vfeature_engine___024root___eval_debug_assertions(Vfeature_engine___024root* vlSelf);
#endif  // VL_DEBUG
void Vfeature_engine___024root___eval_static(Vfeature_engine___024root* vlSelf);
void Vfeature_engine___024root___eval_initial(Vfeature_engine___024root* vlSelf);
void Vfeature_engine___024root___eval_settle(Vfeature_engine___024root* vlSelf);
void Vfeature_engine___024root___eval(Vfeature_engine___024root* vlSelf);

void Vfeature_engine::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vfeature_engine::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vfeature_engine___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vfeature_engine___024root___eval_static(&(vlSymsp->TOP));
        Vfeature_engine___024root___eval_initial(&(vlSymsp->TOP));
        Vfeature_engine___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vfeature_engine___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vfeature_engine::eventsPending() { return false; }

uint64_t Vfeature_engine::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vfeature_engine::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vfeature_engine___024root___eval_final(Vfeature_engine___024root* vlSelf);

VL_ATTR_COLD void Vfeature_engine::final() {
    Vfeature_engine___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vfeature_engine::hierName() const { return vlSymsp->name(); }
const char* Vfeature_engine::modelName() const { return "Vfeature_engine"; }
unsigned Vfeature_engine::threads() const { return 1; }
void Vfeature_engine::prepareClone() const { contextp()->prepareClone(); }
void Vfeature_engine::atClone() const {
    contextp()->threadPoolpOnClone();
}

//============================================================
// Trace configuration

VL_ATTR_COLD void Vfeature_engine::trace(VerilatedVcdC* tfp, int levels, int options) {
    vl_fatal(__FILE__, __LINE__, __FILE__,"'Vfeature_engine::trace()' called on model that was Verilated without --trace option");
}
