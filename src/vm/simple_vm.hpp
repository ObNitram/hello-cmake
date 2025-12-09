#pragma once

#include <cstdint>
#include <vector>

namespace vm
{

// Minimal instruction set for a tiny stack-based VM.
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
    OpCode op{OpCode::Halt};
    int operand{0};
};

class SimpleVM
{
  public:
    // Execute program and return all values produced by Print.
    std::vector<int> run(const std::vector<Instruction> &program);
};

} // namespace vm
