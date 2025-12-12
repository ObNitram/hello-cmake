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

std::vector<vm::Instruction> compile_node(const parser::Node &node)
{
    switch (node.type())
    {
    case parser::NodeType::Number:
    {
        auto *num = dynamic_cast<const parser::NumberNode *>(&node);
        if (!num) throw std::runtime_error("Number node expected");
        return std::vector<vm::Instruction>{
            {vm::OpCode::PushConst, number_to_operand(num->value())}
        };
    }
    case parser::NodeType::Binary:
    {
        auto *binary = dynamic_cast<const parser::BinaryNode *>(&node);
        if (!binary) throw std::runtime_error("Binary node expected");

        std::vector<vm::Instruction> instructions =
            compile_node(*binary->left());
        std::vector<vm::Instruction> rhs = compile_node(*binary->right());
        instructions.insert(instructions.end(), rhs.begin(), rhs.end());
        instructions.push_back({token_to_opcode(binary->op()), 0});
        return instructions;
    }
    default: throw std::runtime_error("Unknown node type during compilation");
    }
}
} // namespace

std::vector<vm::Instruction> compile(const parser::Node &node)
{
    std::vector<vm::Instruction> code = compile_node(node);
    code.push_back({vm::OpCode::Halt, 0});
    return code;
}

} // namespace compiler
