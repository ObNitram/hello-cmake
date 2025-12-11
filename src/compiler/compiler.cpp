#include "compiler/compiler.hpp"

#include <stdexcept>

namespace compiler
{

namespace
{
int number_to_operand(double value) { return static_cast<int>(value); }

vm::OpCode token_to_opcode(tokenizer::TokenType op)
{
    switch (op)
    {
    case tokenizer::TokenType::Plus: return vm::OpCode::Add;
    case tokenizer::TokenType::Minus: return vm::OpCode::Sub;
    case tokenizer::TokenType::Mul: return vm::OpCode::Mul;
    case tokenizer::TokenType::Div: return vm::OpCode::Div;
    default: throw std::runtime_error("Unsupported operator in compiler");
    }
}

Bytecode compile_node(const parser::Node &node)
{
    switch (node.type())
    {
    case parser::NodeType::Number:
    {
        auto *num = dynamic_cast<const parser::NumberNode *>(&node);
        if (!num) throw std::runtime_error("Number node expected");
        return Bytecode{
            {vm::OpCode::PushConst, number_to_operand(num->value())}
        };
    }
    case parser::NodeType::Binary:
    {
        auto *binary = dynamic_cast<const parser::BinaryNode *>(&node);
        if (!binary) throw std::runtime_error("Binary node expected");

        Bytecode instructions = compile_node(*binary->left());
        Bytecode rhs = compile_node(*binary->right());
        instructions.insert(instructions.end(), rhs.begin(), rhs.end());
        instructions.push_back({token_to_opcode(binary->op()), 0});
        return instructions;
    }
    default: throw std::runtime_error("Unknown node type during compilation");
    }
}
} // namespace

Bytecode compile(const parser::Node &node)
{
    Bytecode code = compile_node(node);
    return code;
}

Bytecode compile_expression(const std::string &input)
{
    auto tokens = tokenizer::tokenize(input);
    auto ast = parser::parse_tokens(tokens);
    return compile(*ast);
}

} // namespace compiler
