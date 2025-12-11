#include <gtest/gtest.h>

#include "tockenizer/tokenizer.hpp"

using tokenizer::Token;
using tokenizer::TokenType;

TEST(Tokenizer, IntegersAndOperators)
{
    const auto tokens = tokenizer::tokenize("12 + 34");
    ASSERT_GE(tokens.size(), 4u);
    EXPECT_EQ(tokens[0].type, TokenType::Int);
    EXPECT_EQ(tokens[0].number, 12);
    EXPECT_EQ(tokens[1].type, TokenType::Plus);
    EXPECT_EQ(tokens[2].type, TokenType::Int);
    EXPECT_EQ(tokens[2].number, 34);
}

TEST(Tokenizer, FloatsAndParens)
{
    const auto tokens = tokenizer::tokenize("3.14*(2+.5)");
    // 3.14 * ( 2 + 0.5 ) End
    ASSERT_GE(tokens.size(), 7u);
    EXPECT_EQ(tokens[0].type, TokenType::Float);
    EXPECT_NEAR(tokens[0].number, 3.14, 1e-12);
    EXPECT_EQ(tokens[1].type, TokenType::Mul);
    EXPECT_EQ(tokens[2].type, TokenType::LParen);
    EXPECT_EQ(tokens[3].type, TokenType::Int);
    EXPECT_EQ(tokens[4].type, TokenType::Plus);
    EXPECT_EQ(tokens[5].type, TokenType::Float);
    EXPECT_NEAR(tokens[5].number, 0.5, 1e-12);
    EXPECT_EQ(tokens[6].type, TokenType::RParen);
}

TEST(Tokenizer, LeadingDotFloat)
{
    const auto tokens = tokenizer::tokenize(".5+.25");
    ASSERT_GE(tokens.size(), 3u);
    EXPECT_EQ(tokens[0].type, TokenType::Float);
    EXPECT_NEAR(tokens[0].number, 0.5, 1e-12);
    EXPECT_EQ(tokens[1].type, TokenType::Plus);
    EXPECT_EQ(tokens[2].type, TokenType::Float);
    EXPECT_NEAR(tokens[2].number, 0.25, 1e-12);
}

TEST(Tokenizer, InvalidCharacterThrows) { EXPECT_THROW(tokenizer::tokenize("1 & 2"), std::runtime_error); }
