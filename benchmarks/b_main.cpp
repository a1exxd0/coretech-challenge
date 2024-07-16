#include <benchmark/benchmark.h>

static void init_b(benchmark::State& state) {
    for (auto _ : state) {
        int a = 0;
        for (std::size_t i = 0; i < 100; ++i) {
            ++a;
        }
    }
}

BENCHMARK(init_b)
->Name("Initial benchmark setup")
->Iterations(100)
->MeasureProcessCPUTime();

BENCHMARK_MAIN();