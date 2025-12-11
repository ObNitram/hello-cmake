#include <gtest/gtest.h>
#include <sstream>

#include "vm/simple_vm.hpp"

namespace
{
std::vector<vm::Instruction> make_add_program(int lhs, int rhs)
{
    return {
        {vm::OpCode::PushConst, lhs},
        {vm::OpCode::PushConst, rhs},
        {vm::OpCode::Add,       0  },
        {vm::OpCode::Print,     0  },
        {vm::OpCode::Halt,      0  }
    };
}
} // namespace

TEST(SimpleVM, AddsAndPrints)
{
    std::ostringstream output_buf;
    vm::SimpleVM vm;

    auto outputs = vm.run(make_add_program(5, 8), output_buf);

    ASSERT_EQ(outputs.size(), 1u);
    EXPECT_EQ(outputs[0], 13);
    EXPECT_EQ(output_buf.str(), "13");
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
        {vm::OpCode::Print,     0 },
        {vm::OpCode::Halt,      0 }
    };

    std::ostringstream output_buf;
    vm::SimpleVM vm;

    auto outputs = vm.run(program, output_buf);

    ASSERT_EQ(outputs.size(), 1u);
    EXPECT_EQ(outputs[0], 2);
    EXPECT_EQ(output_buf.str(), "2");
}

TEST(SimpleVM, DivisionByZeroThrows)
{
    const std::vector<vm::Instruction> program{
        {vm::OpCode::PushConst, 1},
        {vm::OpCode::PushConst, 0},
        {vm::OpCode::Div,       0}
    };

    vm::SimpleVM vm;
    std::ostringstream output_buf;
    EXPECT_THROW(vm.run(program, output_buf), std::runtime_error);
}

TEST(SimpleVM, StackUnderflowThrows)
{
    const std::vector<vm::Instruction> program{
        {vm::OpCode::Add, 0}
    };

    vm::SimpleVM vm;
    std::ostringstream output_buf;
    EXPECT_THROW(vm.run(program, output_buf), std::runtime_error);
}
