#pragma once

#include <cstddef>
#include <string>

namespace hello
{

std::string get_greeting(const std::string &name = std::string());

std::string hard_compute(size_t steps);

} // namespace hello
