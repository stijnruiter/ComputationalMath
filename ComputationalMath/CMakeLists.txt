project(ComputationalMath VERSION 0.1 LANGUAGES CXX)

add_subdirectory(src)

add_subdirectory(benchmark)
enable_testing()
add_subdirectory(tests)