#include "../src/LinearAlgebra/FactorizationLU.hpp"

#include <LinearAlgebra/Matrix.hpp>
#include <benchmark/benchmark.h>
#include <memory>

static void BM_MatrixSum(benchmark::State& state)
{
    for (auto stat : state)
    {
        state.PauseTiming();
        const size_t size = state.range();
        LinearAlgebra::Matrix<int> mat1(size, size);
        LinearAlgebra::Matrix<int> mat2(size, size);
        mat1.Fill(5);
        mat1.Fill(3);
        state.ResumeTiming();

        benchmark::DoNotOptimize(mat1 + mat2);
        benchmark::ClobberMemory();
    }
}

BENCHMARK(BM_MatrixSum)
    ->RangeMultiplier(2)
    ->Range(1 << 5, 1 << 15);
BENCHMARK_MAIN();