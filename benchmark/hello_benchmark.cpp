#include "helloword/helloword.hpp"
# include <benchmark/benchmark.h>

static void BM_get_greeting(benchmark::State &state)
{
    std::string name = "Benchmark";
    for (auto _ : state)
    {
        auto greeting = hello::get_greeting(name);
        benchmark::DoNotOptimize(greeting);
    }
}

BENCHMARK(BM_get_greeting);

static void BM_hard_compute(benchmark::State &state)
{
    size_t steps = state.range(0);
    for (auto _ : state)
    {
        auto result = hello::hard_compute(steps);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_hard_compute)->Ranges({{2, 10000000}});