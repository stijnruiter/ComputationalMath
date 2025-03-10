#include <memory>
#include <benchmark/benchmark.h>
#include <LinearAlgebra/Matrix.h>

static void BM_MatrixSum(benchmark::State& state)
{
    for (auto stat : state)
    {
        state.PauseTiming();
        size_t size = state.range();
        Matrix<float> mat1(size, size);
        Matrix<float> mat2(size, size);
        Matrix<float> mat3;
        state.ResumeTiming();

        benchmark::DoNotOptimize(mat3 = mat1 + mat2);
        benchmark::ClobberMemory();
    }
}

BENCHMARK(BM_MatrixSum)
->RangeMultiplier(2)
->Range(1 << 5, 1 << 15)
->Complexity();
BENCHMARK_MAIN();