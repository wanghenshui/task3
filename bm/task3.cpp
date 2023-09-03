#include <iostream>
#include <benchmark/benchmark.h>
#include "task3.h"

#define LEN 10000000
Row global[LEN];

#define BM(f) \
static void BM_##f(benchmark::State& state) {\
    for (auto _ : state) {\
       auto ret = f(global, LEN);\
       benchmark::DoNotOptimize(ret); \
    }\
}\
BENCHMARK(BM_##f)->Iterations(1000);


// warm
static void BM_warm(benchmark::State& state) {
    prepare(global, LEN);
    for (auto _ : state) {
        task0(global, LEN);
    }
}

BENCHMARK(BM_warm)->Iterations(1000);

/*
fixed_thread_pool ths;

static void BM_task2_mt(benchmark::State& state) {
    for (auto _ : state) {
       auto ret = task2_mt(global, LEN, &ths);
       benchmark::DoNotOptimize(ret);
    }

}
BENCHMARK(BM_task2_mt)->Iterations(10000);
*/

BM(task1);
BM(task2);
BM(task3);
BM(task3_stl_sort);

BENCHMARK_MAIN();
