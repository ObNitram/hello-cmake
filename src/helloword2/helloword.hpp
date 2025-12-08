#pragma once

#include <cstddef>
#include <string>

namespace hello
{

std::string get_greeting2(const std::string &name = std::string());

std::string hard_compute2(size_t steps);

} // namespace hello
