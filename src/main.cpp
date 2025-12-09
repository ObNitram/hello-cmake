#include <iostream>
#include <vector>

#include "helloword/helloword.hpp"
#include "helloword2/helloword.hpp"
#include "vm/simple_vm.hpp"

int main(int argc, char **argv)
{
    std::string name = (argc > 1) ? argv[1] : std::string();
    size_t steps = (argc > 2) ? std::stoul(argv[2]) : 1000000;

    std::cout << hello::get_greeting(name) << "\n";
    std::cout << "Hard compute result: " << hello::hard_compute(steps) << "\n";
    std::cout << hello::get_greeting2(name) << "\n";
    std::cout << "Hard compute2 result: " << hello::hard_compute2(steps) << "\n";

    // Tiny VM program: ((2 + 3) * 4) = 20
    const std::vector<vm::Instruction> program{
        {vm::OpCode::PushConst, 2}, {vm::OpCode::PushConst, 3}, {vm::OpCode::Add, 0}, {vm::OpCode::PushConst, 4},
        {vm::OpCode::Mul, 0},       {vm::OpCode::Print, 0},     {vm::OpCode::Halt, 0}};

    std::cout << "Running tiny VM program:\n";
    vm::SimpleVM vm = vm::SimpleVM();
    vm.run(program);
    return 0;
}
