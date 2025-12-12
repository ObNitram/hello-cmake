#include "vm/simple_vm.hpp"

#include <cstdint>
#include <stdexcept>

namespace vm
{

namespace
{
int pop_stack(std::vector<int> &stack)
{
    if (stack.empty()) throw std::runtime_error("Stack underflow");
    int value = stack.back();
    stack.pop_back();
    return value;
}
} // namespace

std::int32_t SimpleVM::run(const std::vector<Instruction> &program,
                           std::ostream &output_buf)
{
    std::vector<int32_t> stack;

    for (std::size_t ip = 0; ip < program.size(); ++ip)
    {
        const Instruction &instr = program[ip];
        switch (instr.op)
        {
        case OpCode::PushConst:
        {
            stack.push_back(instr.operand);
            break;
        }
        case OpCode::Add:
        {
            int rhs = pop_stack(stack);
            int lhs = pop_stack(stack);
            stack.push_back(lhs + rhs);
            break;
        }
        case OpCode::Sub:
        {
            int rhs = pop_stack(stack);
            int lhs = pop_stack(stack);
            stack.push_back(lhs - rhs);
            break;
        }
        case OpCode::Mul:
        {
            int rhs = pop_stack(stack);
            int lhs = pop_stack(stack);
            stack.push_back(lhs * rhs);
            break;
        }
        case OpCode::Div:
        {
            int rhs = pop_stack(stack);
            int lhs = pop_stack(stack);
            if (rhs == 0) throw std::runtime_error("Division by zero");
            stack.push_back(lhs / rhs);
            break;
        }
        case OpCode::Halt:
        {
            if (stack.empty())
                throw std::runtime_error("Stack underflow on halt");
            return stack.back();
        }
        default: throw std::runtime_error("Unknown opcode");
        }
    }

    return 1;
}

} // namespace vm
