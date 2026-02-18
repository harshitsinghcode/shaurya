#ifndef VERILATED_H
#define VERILATED_H
// Mocking Verilator for LLVM Build
class Verilated {
public:
    static void commandArgs(int, char**) {}
};
#endif