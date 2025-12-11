#include "tokenizer.hpp"
#include <cctype>
#include <stdexcept>

namespace tokenizer
{

std::vector<Token> tokenize(const std::string &input)
{
    std::vector<Token> tokens;
    size_t i = 0;
    const size_t n = input.size();

    auto make_token = [&](TokenType type, const std::string &text = std::string(), double number = 0.0)
    {
        Token t;
        t.type = type;
        t.text = text;
        t.number = number;
        tokens.push_back(t);
    };

    while (i < n)
    {
        char c = input[i];
        if (std::isspace(c))
        {
            ++i;
            continue;
        }

        if (std::isdigit(c) || (c == '.' && i + 1 < n && std::isdigit(input[i + 1])))
        {
            // Parse number (int or float)
            size_t start = i;
            bool has_dot = false;
            if (c == '.')
            {
                has_dot = true;
                ++i;
            }
            while (i < n && std::isdigit(static_cast<unsigned char>(input[i]))) ++i;
            if (i < n && input[i] == '.')
            {
                if (has_dot) throw std::runtime_error("Invalid numeric literal: multiple decimal points");
                has_dot = true;
                ++i;
                while (i < n && std::isdigit(static_cast<unsigned char>(input[i]))) ++i;
            }

            std::string lex = input.substr(start, i - start);
            try
            {
                double val = std::stod(lex);
                make_token(has_dot ? TokenType::Float : TokenType::Int, lex, val);
            }
            catch (const std::exception &e)
            {
                throw std::runtime_error(std::string("Failed to parse numeric literal: ") + e.what());
            }

            continue;
        }

        switch (c)
        {
        case '+':
            make_token(TokenType::Plus, "+");
            ++i;
            break;
        case '-':
            make_token(TokenType::Minus, "-");
            ++i;
            break;
        case '*':
            make_token(TokenType::Mul, "*");
            ++i;
            break;
        case '/':
            make_token(TokenType::Div, "/");
            ++i;
            break;
        case '(':
            make_token(TokenType::LParen, "(");
            ++i;
            break;
        case ')':
            make_token(TokenType::RParen, ")");
            ++i;
            break;
        default:
        {
            // Unknown character
            throw std::runtime_error(std::string("Unknown character: ") + c);
        }
        }
    }

    make_token(TokenType::End, "");
    return tokens;
}

} // namespace tokenizer
