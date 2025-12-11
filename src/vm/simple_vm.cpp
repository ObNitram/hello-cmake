#include "vm/simple_vm.hpp"

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

std::vector<int> SimpleVM::run(const std::vector<Instruction> &program, std::ostream &output_buf)
{
    std::vector<int> stack;
    std::vector<int> outputs;

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
        case OpCode::Print:
        {
            int value = pop_stack(stack);
            outputs.push_back(value);

            output_buf << value;
            break;
        }
        case OpCode::Halt: return outputs;
        default: throw std::runtime_error("Unknown opcode");
        }
    }

    return outputs;
}

} // namespace vm
