#include <iostream>
#include <benchmark/benchmark.h>
#include "task3.h"

#define LEN 1000000
Row global[LEN];

static void BM_task0(benchmark::State& state) {
    prepare(global, LEN);
    for (auto _ : state) {
        task0(global, LEN);
    }
}

static void BM_task1(benchmark::State& state) {
    for (auto _ : state) {
        task1(global, LEN);
    }
}

static void BM_task2(benchmark::State& state) {
    for (auto _ : state) {
        task2(global, LEN);
    }
}


static void BM_task3(benchmark::State& state) {
    for (auto _ : state) {
        task3(global, LEN);
    }
}


BENCHMARK(BM_task0)->Iterations(10000);
BENCHMARK(BM_task3)->Iterations(10000);
BENCHMARK(BM_task2)->Iterations(10000);
BENCHMARK(BM_task1)->Iterations(10000);
BENCHMARK_MAIN();
