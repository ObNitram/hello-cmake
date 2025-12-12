#pragma once

#include <vector>

#include "parcer/parser.hpp"
#include "vm/simple_vm.hpp"

namespace compiler
{

// Emit std::vector<vm::Instruction> for a previously built AST.
std::vector<vm::Instruction> compile(const parser::Node &node);

} // namespace compiler
