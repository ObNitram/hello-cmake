#include <benchmark/benchmark.h>

static void BM_MyStuff(benchmark::State &state)
{
    for (auto _ : state)
    {
        auto name = new std::string("Benchmark");

        name->append(" Hello");

        delete name;
    }
}
BENCHMARK(BM_MyStuff);


static void BM_StringCreation(benchmark::State &state)
{
    for (auto _ : state)
    {
        std::string empty_string;
        benchmark::DoNotOptimize(empty_string);
    }
}
BENCHMARK(BM_StringCreation);

static void BM_StringCopy(benchmark::State &state)
{
    std::string x = "Hello World";
    for (auto _ : state)
    {
        std::string copy(x);
        benchmark::DoNotOptimize(copy);
    }
}
BENCHMARK(BM_StringCopy);


