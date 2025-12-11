#include <gtest/gtest.h>

#include "parcer/parser.hpp"
#include "tockenizer/tokenizer.hpp"

namespace
{
std::unique_ptr<parser::Node> parse_ast(const char *expr)
{
    return parser::parse_tokens(tokenizer::tokenize(expr));
}
} // namespace

TEST(Parser, RespectsPrecedenceAndAssociativity)
{
    auto ast = parse_ast("1 + 2 * 3 - 4 / 2");
    auto *root = dynamic_cast<parser::BinaryNode *>(ast.get());
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->op(), tokenizer::TokenType::Minus);

    auto *left = dynamic_cast<parser::BinaryNode *>(root->left());
    ASSERT_NE(left, nullptr);
    EXPECT_EQ(left->op(), tokenizer::TokenType::Plus);

    auto *right = dynamic_cast<parser::BinaryNode *>(root->right());
    ASSERT_NE(right, nullptr);
    EXPECT_EQ(right->op(), tokenizer::TokenType::Div);
}

TEST(Parser, HandlesParentheses)
{
    auto ast = parse_ast("(2 + 3) * 4");
    auto *root = dynamic_cast<parser::BinaryNode *>(ast.get());
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->op(), tokenizer::TokenType::Mul);

    auto *lhs = dynamic_cast<parser::BinaryNode *>(root->left());
    ASSERT_NE(lhs, nullptr);
    EXPECT_EQ(lhs->op(), tokenizer::TokenType::Plus);

    auto *rhs = dynamic_cast<parser::NumberNode *>(root->right());
    ASSERT_NE(rhs, nullptr);
    EXPECT_DOUBLE_EQ(rhs->value(), 4.0);
}

TEST(Parser, SupportsUnaryMinus)
{
    auto ast = parse_ast("-3.5");
    auto *root = dynamic_cast<parser::BinaryNode *>(ast.get());
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->op(), tokenizer::TokenType::Minus);

    auto *lhs = dynamic_cast<parser::NumberNode *>(root->left());
    ASSERT_NE(lhs, nullptr);
    EXPECT_DOUBLE_EQ(lhs->value(), 0.0);

    auto *rhs = dynamic_cast<parser::NumberNode *>(root->right());
    ASSERT_NE(rhs, nullptr);
    EXPECT_DOUBLE_EQ(rhs->value(), 3.5);
}

TEST(Parser, InvalidSyntaxThrows)
{
    EXPECT_THROW(parse_ast("1 +"), std::runtime_error);
    EXPECT_THROW(parse_ast("(1 + 2"), std::runtime_error);
}
