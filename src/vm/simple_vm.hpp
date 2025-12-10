#pragma once

#include <cstdint>
#include <iostream>
#include <ostream>
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
    OpCode op{0};
    int operand{0};
};

class SimpleVM
{
  private:
    std::ostream &output_buf_;

  public:
    SimpleVM() : output_buf_(std::cerr) {}
    explicit SimpleVM(std::ostream &output_buf) : output_buf_(output_buf) {}

    // Execute program and return all values produced by Print.
    std::vector<int> run(const std::vector<Instruction> &program);
};

} // namespace vm
