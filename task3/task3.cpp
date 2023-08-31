#include <iostream>
#include <benchmark/benchmark.h>
static void BM_SomeFunction(benchmark::State& state) {
     for (auto _ : state) {
  //           SomeFunction();
      }
}

BENCHMARK(BM_SomeFunction);
BENCHMARK_MAIN();
