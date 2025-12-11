#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace tokenizer
{

enum class TokenType : std::uint8_t
{
    Int,
    Float,
    Plus,
    Minus,
    Mul,
    Div,
    LParen,
    RParen,
    End
};

struct Token
{
    TokenType type{TokenType::End};
    std::string text;
    double number{0.0};
};

// Tokenize an input string into tokens. Throws std::runtime_error on invalid
// characters.
std::vector<Token> tokenize(const std::string &input);

} // namespace tokenizer
