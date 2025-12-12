#include <gtest/gtest.h>
#include <memory>
#include <vector>

#include "compiler/compiler.hpp"
#include "parcer/parser.hpp"
#include "tockenizer/tokenizer.hpp"
#include "utils/dev_null.hpp"
#include "vm/simple_vm.hpp"

TEST(Chain, Program_1)
{
    std::string expression = "1 + 1";
    auto tockens = tokenizer::tokenize(expression);
    EXPECT_EQ(tockens, std::vector<tokenizer::Token>({
                           {tokenizer::TokenType::Int,  "1", 1},
                           {tokenizer::TokenType::Plus, "+", 0},
                           {tokenizer::TokenType::Int,  "1", 1},
                           {tokenizer::TokenType::End,  "",  0}
    }));

    auto ast = parser::parse_tokens(tockens);

    auto program = compiler::compile(*ast);
    EXPECT_EQ(program, std::vector<vm::Instruction>({
                           {vm::OpCode::PushConst, 1},
                           {vm::OpCode::PushConst, 1},
                           {vm::OpCode::Add,       0},
                           {vm::OpCode::Halt,      0}
    }));

    vm::SimpleVM vm{};
    auto result = vm.run(program, utils::devnull);

    EXPECT_EQ(result, 2);
}

TEST(Chain, Program_2)
{
    std::string expression = "(3 + 4) * 5 - 6 / 2"; // 7 * 5 - 3 = 35 - 3 = 32
    auto tockens = tokenizer::tokenize(expression);
    EXPECT_EQ(tockens, std::vector<tokenizer::Token>({
                           {tokenizer::TokenType::LParen, "(", 0},
                           {tokenizer::TokenType::Int,    "3", 3},
                           {tokenizer::TokenType::Plus,   "+", 0},
                           {tokenizer::TokenType::Int,    "4", 4},
                           {tokenizer::TokenType::RParen, ")", 0},
                           {tokenizer::TokenType::Mul,    "*", 0},
                           {tokenizer::TokenType::Int,    "5", 5},
                           {tokenizer::TokenType::Minus,  "-", 0},
                           {tokenizer::TokenType::Int,    "6", 6},
                           {tokenizer::TokenType::Div,    "/", 0},
                           {tokenizer::TokenType::Int,    "2", 2},
                           {tokenizer::TokenType::End,    "",  0}
    }));

    auto ast = parser::parse_tokens(tockens);
    auto program = compiler::compile(*ast);
    EXPECT_EQ(program, std::vector<vm::Instruction>({
                           {vm::OpCode::PushConst, 3},
                           {vm::OpCode::PushConst, 4},
                           {vm::OpCode::Add,       0},
                           {vm::OpCode::PushConst, 5},
                           {vm::OpCode::Mul,       0},
                           {vm::OpCode::PushConst, 6},
                           {vm::OpCode::PushConst, 2},
                           {vm::OpCode::Div,       0},
                           {vm::OpCode::Sub,       0},
                           {vm::OpCode::Halt,      0}
    }));

    vm::SimpleVM vm{};
    auto result = vm.run(program, utils::devnull);
    EXPECT_EQ(result, 32);
}

TEST(Chain, Program_3)
{
    std::string expression = "10 - 2 * 3 + 4 / 2"; // 10 - 6 + 2 = 6
    auto tockens = tokenizer::tokenize(expression);
    EXPECT_EQ(tockens, std::vector<tokenizer::Token>({
                           {tokenizer::TokenType::Int,   "10", 10},
                           {tokenizer::TokenType::Minus, "-",  0 },
                           {tokenizer::TokenType::Int,   "2",  2 },
                           {tokenizer::TokenType::Mul,   "*",  0 },
                           {tokenizer::TokenType::Int,   "3",  3 },
                           {tokenizer::TokenType::Plus,  "+",  0 },
                           {tokenizer::TokenType::Int,   "4",  4 },
                           {tokenizer::TokenType::Div,   "/",  0 },
                           {tokenizer::TokenType::Int,   "2",  2 },
                           {tokenizer::TokenType::End,   "",   0 }
    }));

    auto ast = parser::parse_tokens(tockens);
    auto program = compiler::compile(*ast);
    EXPECT_EQ(program, std::vector<vm::Instruction>({
                           {vm::OpCode::PushConst, 10},
                           {vm::OpCode::PushConst, 2 },
                           {vm::OpCode::PushConst, 3 },
                           {vm::OpCode::Mul,       0 },
                           {vm::OpCode::Sub,       0 },
                           {vm::OpCode::PushConst, 4 },
                           {vm::OpCode::PushConst, 2 },
                           {vm::OpCode::Div,       0 },
                           {vm::OpCode::Add,       0 },
                           {vm::OpCode::Halt,      0 }
    }));

    vm::SimpleVM vm{};
    auto result = vm.run(program, utils::devnull);
    EXPECT_EQ(result, 6);
}