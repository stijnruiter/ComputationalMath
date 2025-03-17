# Include Google Benchmark
include(../cmake/GoogleBenchmark.cmake)

add_executable(ComputationalMathBenchmark)
target_sources(
  ComputationalMathBenchmark
  PRIVATE
    # benchmark.cpp
    MatrixTransposed.cpp
    )

target_link_libraries(
  ComputationalMathBenchmark
  ComputationalMath
  benchmark::benchmark
)