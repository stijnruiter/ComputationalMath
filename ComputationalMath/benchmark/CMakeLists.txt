# Include Google Benchmark
include(../cmake/GoogleBenchmark.cmake)

add_executable(ComputationalMathBenchmark)
target_sources(
  ComputationalMathBenchmark
  PRIVATE
    benchmark.cpp
    benchmark.h)

target_link_libraries(
  ComputationalMathBenchmark
  ComputationalMath
  benchmark::benchmark
)