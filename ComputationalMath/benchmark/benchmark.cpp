#include <memory>
#include <benchmark/benchmark.h>
#include <LinearAlgebra/Matrix.h>

static void BM_MatrixSum(benchmark::State& state)
{
    for (auto stat : state)
    {
        Matrix<float, 5, 5> mat1;
        Matrix<float, 5, 5> mat2;
        Matrix<float, 5, 5> mat3;
        benchmark::DoNotOptimize(mat3 = mat1 + mat2);
        benchmark::ClobberMemory();
    }
}

BENCHMARK(BM_MatrixSum);
BENCHMARK_MAIN();