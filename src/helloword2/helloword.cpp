#include <cstddef>
#include <string>

#include "./helloword.hpp"

namespace hello
{

std::string get_greeting2(const std::string &name)
{
    if (name.empty()) return "Hello, World!";
    return std::string("Hello, ") + name + "!";
}

std::string hard_compute2(size_t steps)
{
    volatile double x = 3.14159;
    for (size_t i = 0; i < 10; ++i)
    {
        for (size_t j = 0; j < steps; ++j)
        {

            x = x + 2.71828 / x;
        }
    }
    return std::to_string(x);
}

} // namespace hello
