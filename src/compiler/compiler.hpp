#pragma once

#include <string>
#include <vector>

#include "parcer/parser.hpp"
#include "vm/simple_vm.hpp"

namespace compiler
{

using Bytecode = std::vector<vm::Instruction>;

// Emit bytecode for a previously built AST.
Bytecode compile(const parser::Node &node);

// Convenience helper: tokenize, parse, then compile an expression.
Bytecode compile_expression(const std::string &input);

} // namespace compiler
