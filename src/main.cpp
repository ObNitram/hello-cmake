#include <iostream>

#include "helloword/helloword.hpp"
#include "helloword2/helloword.hpp"

int main(int argc, char *argv[])
{
    std::string name = (argc > 1) ? argv[1] : std::string();
    size_t steps = (argc > 2) ? std::stoul(argv[2]) : 1000000;

    std::cout << hello::get_greeting(name) << "\n";
    std::cout << "Hard compute result: " << hello::hard_compute(steps) << "\n";
    std::cout << hello::get_greeting2(name) << "\n";
    std::cout << "Hard compute2 result: " << hello::hard_compute2(steps) << "\n";
    return 0;
}
