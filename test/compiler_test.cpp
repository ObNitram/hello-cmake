// #include <gtest/gtest.h>
// #include <sstream>

// #include "compiler/compiler.hpp"
// #include "parcer/parser.hpp"
// #include "tockenizer/tokenizer.hpp"
// #include "vm/simple_vm.hpp"

// namespace
// {

// std::vector<vm::Instruction> compile_for_test(const char *expr)
// {
//     return compiler::compile_expression(expr);
// }
// } // namespace

// TEST(Compiler, Executesstd::vector<vm::Instruction>)
// {
//     auto ast = parser::parse_tokens(tokenizer::tokenize("2 + 3 * 4"));
//     auto std::vector<vm::Instruction> = compiler::compile(*ast);
//     auto program = make_runnable_program(std::vector<vm::Instruction>);

//     std::ostringstream output_buf;
//     vm::SimpleVM vm;
//     auto outputs = vm.run(program, output_buf);

//     ASSERT_EQ(outputs.size(), 1u);
//     EXPECT_EQ(outputs[0], 14);
//     EXPECT_EQ(output_buf.str(), "14");
// }

// TEST(Compiler, CompileExpressionHelper)
// {
//     auto std::vector<vm::Instruction> = compile_for_test("10 / 2 - 1");
//     auto program = make_runnable_program(std::vector<vm::Instruction>);

//     std::ostringstream output_buf;
//     vm::SimpleVM vm;
//     auto outputs = vm.run(program, output_buf);

//     ASSERT_EQ(outputs.size(), 1u);
//     EXPECT_EQ(outputs[0], 4);
//     EXPECT_EQ(output_buf.str(), "4");
// }

// TEST(Compiler, HandlesUnaryMinus)
// {
//     auto ast = parser::parse_tokens(tokenizer::tokenize("-5 + 3"));
//     auto std::vector<vm::Instruction> = compiler::compile(*ast);

//     // Expect: push 0, push 5, sub, push 3, add
//     const std::vector<vm::OpCode> expected_ops{
//         vm::OpCode::PushConst, vm::OpCode::PushConst, vm::OpCode::Sub,
//         vm::OpCode::PushConst, vm::OpCode::Add};

//     std::vector<vm::OpCode> actual_ops;
//     for (const auto &instr : std::vector<vm::Instruction>)
//     {
//         actual_ops.push_back(instr.op);
//     }

//     EXPECT_EQ(actual_ops, expected_ops);
// }
