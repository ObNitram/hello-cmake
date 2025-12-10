#include <iostream>
#include <vector>

#include "vm/simple_vm.hpp"

int main(int argc, char **argv)
{

    // Tiny VM program: ((2 + 3) * 4) = 20
    const std::vector<vm::Instruction> program{
        {.op = vm::OpCode::PushConst, .operand = 2},
        {.op = vm::OpCode::PushConst, .operand = 3},
        {.op = vm::OpCode::Add,       .operand = 0},
        {.op = vm::OpCode::PushConst, .operand = 4},
        {.op = vm::OpCode::Mul,       .operand = 0},
        {.op = vm::OpCode::Print,     .operand = 0},
        {.op = vm::OpCode::Halt,      .operand = 0}
    };

    std::cout << "Running tiny VM program:\n";
    vm::SimpleVM vm = vm::SimpleVM();
    vm.run(program);
    return 0;
}
