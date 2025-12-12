#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "tockenizer/tokenizer.hpp"

namespace parser
{

enum class NodeType : std::uint8_t
{
    Number,
    Binary
};

class Node
{
public:
    virtual ~Node() = default;
    virtual NodeType type() const = 0;
};

class NumberNode final : public Node
{
public:
    explicit NumberNode(double value);

    NodeType type() const override;
    double value() const;

private:
    double value_;
};

class BinaryNode final : public Node
{
public:
    BinaryNode(tokenizer::TokenType op, std::unique_ptr<Node> left,
               std::unique_ptr<Node> right);

    NodeType type() const override;

    tokenizer::TokenType op() const;
    const Node *left() const;
    Node *left();
    const Node *right() const;
    Node *right();

    bool operator==(const BinaryNode &other) const;

private:
    tokenizer::TokenType op_;
    std::unique_ptr<Node> left_;
    std::unique_ptr<Node> right_;
};

// Parse a token stream (must end with TokenType::End) into an expression tree.
std::unique_ptr<Node> parse_tokens(const std::vector<tokenizer::Token> &tokens);

} // namespace parser
