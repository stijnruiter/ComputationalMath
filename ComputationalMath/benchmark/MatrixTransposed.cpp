#include <memory>
#include <benchmark/benchmark.h>
#include <LinearAlgebra/Matrix.hpp>

// 2025-03-17T23:34:53+01:00
// Run on (8 X 3294 MHz CPU s)
// CPU Caches:
//   L1 Data 32 KiB (x4)
//   L1 Instruction 32 KiB (x4)
//   L2 Unified 512 KiB (x4)
//   L3 Unified 8192 KiB (x1)

// BM_MatrixTranspose1/32           762 ns          371 ns      3584000
// BM_MatrixTranspose2/32           728 ns          345 ns      1947826
// BM_MatrixTranspose3/32           773 ns          365 ns      1967687

// BM_MatrixTranspose1/64          1703 ns          963 ns      1120000
// BM_MatrixTranspose2/64          1780 ns          732 ns       746667
// BM_MatrixTranspose3/64          2000 ns          991 ns      1120000

// BM_MatrixTranspose1/128        29937 ns         9844 ns       100000
// BM_MatrixTranspose2/128        29799 ns        13672 ns        64000
// BM_MatrixTranspose3/128         6550 ns         2849 ns       235789

// BM_MatrixTranspose1/256       131267 ns        48652 ns        14452
// BM_MatrixTranspose2/256       136070 ns        53125 ns        10000
// BM_MatrixTranspose3/256        27857 ns        13951 ns        89600

// BM_MatrixTranspose1/512       974664 ns       353671 ns         1723
// BM_MatrixTranspose2/512       967467 ns       495257 ns         2240
// BM_MatrixTranspose3/512       578560 ns       229492 ns         3200

// BM_MatrixTranspose1/1024     6093484 ns      3019068 ns          295
// BM_MatrixTranspose2/1024     6118161 ns      2399554 ns          280
// BM_MatrixTranspose3/1024     2984164 ns      1342773 ns          640

// BM_MatrixTranspose1/2048    29380195 ns     11160714 ns           56
// BM_MatrixTranspose2/2048    29357515 ns     13750000 ns           75
// BM_MatrixTranspose3/2048    15507547 ns      6517380 ns          187

// BM_MatrixTranspose1/4096   133194478 ns     62500000 ns            9
// BM_MatrixTranspose2/4096   135795040 ns     57812500 ns           10
// BM_MatrixTranspose3/4096    63557525 ns     31901042 ns           24

// BM_MatrixTranspose1/8192   640277533 ns    312500000 ns            3
// BM_MatrixTranspose2/8192   635720700 ns    257812500 ns            2
// BM_MatrixTranspose3/8192   260836755 ns     83806818 ns           11

// BM_MatrixTranspose1/16384 5905913000 ns   2343750000 ns            1
// BM_MatrixTranspose2/16384 5955950100 ns   3109375000 ns            1
// BM_MatrixTranspose3/16384 1167336150 ns    492187500 ns            2

template<typename T>
static void Transpose1(const LinearAlgebra::Matrix<T>& mat, LinearAlgebra::Matrix<T>& output)
{
    for (size_t i = 0; i < mat.GetRowCount(); i++)
    {
        for (size_t j = 0; j < output.GetColumnCount(); j++)
        {
            output(j, i) = mat(i, j);
        }
    }
}

template<typename T>
static void Transpose2(const LinearAlgebra::Matrix<T>& mat, LinearAlgebra::Matrix<T>& output)
{
    const T* src = mat.Data();
    T* dst = output.Data();

    size_t rowCount = mat.GetRowCount();
    size_t columnCount = mat.GetColumnCount();

    for (size_t i = 0; i < rowCount; i++)
    {
        for (size_t j = 0; j < columnCount; j++)
        {
            dst[j * rowCount + i] = src[i * columnCount + j];
        }
    }
}

template<typename T>
static void Transpose3(const LinearAlgebra::Matrix<T>& mat, LinearAlgebra::Matrix<T>& output)
{
    const T* src = mat.Data();
    T* dst = output.Data();

    size_t rowCount = mat.GetRowCount();
    size_t columnCount = mat.GetColumnCount();
    size_t block = 32;
    for (size_t i = 0; i < rowCount; i += block)
    {
        for (size_t j = 0; j < columnCount; ++j)
        {
            for (size_t k = 0; k < block && i + k < rowCount; ++k)
            {
                dst[j * rowCount + i + k] = src[(i + k) * columnCount + j];
            }
        }
    }
}

#define TransposeBenchmark(x)                               \
static void BM_MatrixTranspose##x(benchmark::State& state)  \
{                                                           \
    for (auto stat : state)                                 \
    {                                                       \
        state.PauseTiming();                                \
        size_t size = state.range();                        \
        LinearAlgebra::Matrix<int> mat1(size, size + 1);    \
        LinearAlgebra::Matrix<int> mat2(size + 1, size);    \
        mat1.Fill(5);                                       \
        state.ResumeTiming();                               \
        Transpose##x(mat1, mat2);                           \
        benchmark::ClobberMemory();                         \
    }                                                       \
}                                                           \
BENCHMARK(BM_MatrixTranspose##x)                            \
    ->RangeMultiplier(2)                                    \
    ->Range(1 << 5, 1 << 14);                               

TransposeBenchmark(1)
TransposeBenchmark(2)
TransposeBenchmark(3)

// BENCHMARK(BM_MatrixTranspose2)
//     ->RangeMultiplier(2)
//     ->Range(1 << 5, 1 << 14);
// BENCHMARK(BM_MatrixTranspose3)
//     ->RangeMultiplier(2)
//     ->Range(1 << 5, 1 << 14);
BENCHMARK_MAIN();