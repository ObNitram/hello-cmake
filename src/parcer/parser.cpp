#include "parcer/parser.hpp"

#include <stdexcept>
#include <utility>

namespace parser
{

NumberNode::NumberNode(double value) : value_(value) {}

NodeType NumberNode::type() const { return NodeType::Number; }
double NumberNode::value() const { return value_; }

BinaryNode::BinaryNode(tokenizer::TokenType op, std::unique_ptr<Node> left,
                       std::unique_ptr<Node> right)
    : op_(op), left_(std::move(left)), right_(std::move(right))
{
}

NodeType BinaryNode::type() const { return NodeType::Binary; }

tokenizer::TokenType BinaryNode::op() const { return op_; }

const Node *BinaryNode::left() const { return left_.get(); }
Node *BinaryNode::left() { return left_.get(); }
const Node *BinaryNode::right() const { return right_.get(); }
Node *BinaryNode::right() { return right_.get(); }

namespace
{
class Parser
{
public:
    explicit Parser(const std::vector<tokenizer::Token> &tokens)
        : tokens_(tokens)
    {
        if (tokens_.empty() || tokens_.back().type != tokenizer::TokenType::End)
        {
            throw std::runtime_error(
                "Token stream must end with TokenType::End");
        }
    }

    std::unique_ptr<Node> parse()
    {
        auto expr = parse_expression();
        expect(tokenizer::TokenType::End, "Unexpected trailing tokens");
        return expr;
    }

private:
    const std::vector<tokenizer::Token> &tokens_;
    std::size_t pos_{0};

    const tokenizer::Token &peek() const
    {
        if (pos_ >= tokens_.size())
            throw std::runtime_error("Unexpected end of input");
        return tokens_[pos_];
    }

    bool match(tokenizer::TokenType type)
    {
        if (peek().type == type)
        {
            ++pos_;
            return true;
        }
        return false;
    }

    void expect(tokenizer::TokenType type, const char *message)
    {
        if (!match(type)) throw std::runtime_error(message);
    }

    std::unique_ptr<Node> parse_expression()
    {
        auto node = parse_term();
        while (true)
        {
            const auto type = peek().type;
            if (type == tokenizer::TokenType::Plus ||
                type == tokenizer::TokenType::Minus)
            {
                ++pos_;
                auto rhs = parse_term();
                node = make_binary(type, std::move(node), std::move(rhs));
            }
            else
            {
                break;
            }
        }
        return node;
    }

    std::unique_ptr<Node> parse_term()
    {
        auto node = parse_factor();
        while (true)
        {
            const auto type = peek().type;
            if (type == tokenizer::TokenType::Mul ||
                type == tokenizer::TokenType::Div)
            {
                ++pos_;
                auto rhs = parse_factor();
                node = make_binary(type, std::move(node), std::move(rhs));
            }
            else
            {
                break;
            }
        }
        return node;
    }

    std::unique_ptr<Node> parse_factor()
    {
        if (match(tokenizer::TokenType::Plus))
        {
            return parse_factor();
        }

        if (match(tokenizer::TokenType::Minus))
        {
            auto rhs = parse_factor();
            return make_binary(tokenizer::TokenType::Minus,
                               make_number_node(0.0), std::move(rhs));
        }

        const auto &tok = peek();
        switch (tok.type)
        {
        case tokenizer::TokenType::Int:
        case tokenizer::TokenType::Float:
        {
            ++pos_;
            return make_number_node(tok.number);
        }
        case tokenizer::TokenType::LParen:
        {
            ++pos_;
            auto node = parse_expression();
            expect(tokenizer::TokenType::RParen, "Expected ')'");
            return node;
        }
        default:
            throw std::runtime_error("Unexpected token while parsing factor");
        }
    }

    static std::unique_ptr<Node> make_number_node(double value)
    {
        return std::make_unique<NumberNode>(value);
    }

    static std::unique_ptr<Node> make_binary(tokenizer::TokenType op,
                                             std::unique_ptr<Node> lhs,
                                             std::unique_ptr<Node> rhs)
    {
        return std::make_unique<BinaryNode>(op, std::move(lhs), std::move(rhs));
    }
};
} // namespace

std::unique_ptr<Node> parse_tokens(const std::vector<tokenizer::Token> &tokens)
{
    Parser parser(tokens);
    return parser.parse();
}

} // namespace parser
