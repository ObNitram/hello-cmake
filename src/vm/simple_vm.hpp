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
    Halt
};

struct Instruction
{
    OpCode op{0};
    int operand{0};

    bool operator==(const Instruction &other) const
    {
        return op == other.op && operand == other.operand;
    }
};

class SimpleVM
{
public:
    explicit SimpleVM() = default;

    // Execute program and return all values produced by Print.
    // The output stream is provided per-run so callers can capture or discard
    // output.
    std::int32_t run(const std::vector<Instruction> &program,
                     std::ostream &output_buf);
};

} // namespace vm
