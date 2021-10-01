#include <benchmark/benchmark.h>

#include "stack/Stack.h"
#include "stack/Stack_impl.h"

static const size_t kGrowthCoeffPrec = 10;
static const size_t kStackPushesCnt = 1e5;

static void StackGrowth(benchmark::State& state) {
  for (auto _ : state) {
    Stack<size_t> stack(1 + static_cast<float>(state.range()) / kGrowthCoeffPrec);
    for (size_t i = 0; i < kStackPushesCnt; ++i) {
      stack.push(1);
    }
  }
}

BENCHMARK(StackGrowth)->DenseRange(1, 10);
