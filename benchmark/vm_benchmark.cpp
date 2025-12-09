#include <benchmark/benchmark.h>

#include "vm/simple_vm.hpp"

namespace
{
std::vector<vm::Instruction> make_linear_sum_program(int count)
{
    std::vector<vm::Instruction> program;
    program.reserve(static_cast<std::size_t>(count) * 2 + 3);

    program.push_back({vm::OpCode::PushConst, 0});
    for (int i = 0; i < count; ++i)
    {
        program.push_back({vm::OpCode::PushConst, i});
        program.push_back({vm::OpCode::Add, 0});
    }
    program.push_back({vm::OpCode::Print, 0});
    program.push_back({vm::OpCode::Halt, 0});
    return program;
}
} // namespace

static void BM_SimpleVM_AddLoop(benchmark::State &state)
{
    vm::SimpleVM vm;
    const auto program = make_linear_sum_program(static_cast<int>(state.range(0)));

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(vm.run(program));
    }
}
BENCHMARK(BM_SimpleVM_AddLoop)->RangeMultiplier(10)->Range(10, 10000);
