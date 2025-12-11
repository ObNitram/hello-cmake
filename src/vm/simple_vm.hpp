#pragma once

#include <cstdint>
#include <iostream>
#include <ostream>
#include <vector>

namespace vm
{

enum class OpCode : std::uint8_t
{
    PushConst,
    Add,
    Sub,
    Mul,
    Div,
    Print,
    Halt
};

struct Instruction
{
    OpCode op{0};
    int operand{0};
};

class SimpleVM
{
public:
    SimpleVM() = default;

    // Execute program and return all values produced by Print.
    // The output stream is provided per-run so callers can capture or discard
    // output.
    std::vector<int> run(const std::vector<Instruction> &program,
                         std::ostream &output_buf);
};

} // namespace vm
