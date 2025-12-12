#include <gtest/gtest.h>

#include "utils/dev_null.hpp"
#include "vm/simple_vm.hpp"

namespace
{
std::vector<vm::Instruction> make_add_program(int lhs, int rhs)
{
    return {
        {vm::OpCode::PushConst, lhs},
        {vm::OpCode::PushConst, rhs},
        {vm::OpCode::Add,       0  },
        {vm::OpCode::Halt,      0  }
    };
}
} // namespace

TEST(SimpleVM, AddsAndPrints)
{
    vm::SimpleVM vm;

    auto outputs = vm.run(make_add_program(5, 8), utils::devnull);

    EXPECT_EQ(outputs, 13);
}

TEST(SimpleVM, SubMulDiv)
{
    const std::vector<vm::Instruction> program{
        {vm::OpCode::PushConst, 20},
        {vm::OpCode::PushConst, 5 },
        {vm::OpCode::Div,       0 }, // 20 / 5 = 4
        {vm::OpCode::PushConst, 3 },
        {vm::OpCode::Mul,       0 }, // 4 * 3 = 12
        {vm::OpCode::PushConst, 10},
        {vm::OpCode::Sub,       0 }, // 12 - 10 = 2
        {vm::OpCode::Halt,      0 }
    };

    vm::SimpleVM vm;

    auto outputs = vm.run(program, utils::devnull);

    EXPECT_EQ(outputs, 2);
}

TEST(SimpleVM, DivisionByZeroThrows)
{
    const std::vector<vm::Instruction> program{
        {vm::OpCode::PushConst, 1},
        {vm::OpCode::PushConst, 0},
        {vm::OpCode::Div,       0}
    };

    vm::SimpleVM vm;
    EXPECT_THROW(vm.run(program, utils::devnull), std::runtime_error);
}

TEST(SimpleVM, StackUnderflowThrows)
{
    const std::vector<vm::Instruction> program{
        {vm::OpCode::Add, 0}
    };

    vm::SimpleVM vm;
    EXPECT_THROW(vm.run(program, utils::devnull), std::runtime_error);
}
