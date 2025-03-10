
# Include Google Test
include(../cmake/GoogleTest.cmake)

## ComputationalMathTests
add_executable(
    ComputationalMathTests
    "Geometry/RectangleTests.cpp"
    "LinearAlgebra/MatrixTests.cpp" )

target_link_libraries(ComputationalMathTests
  PRIVATE
    ComputationalMath
    gtest_main
  )

# automatic discovery of unit tests
include(GoogleTest)
gtest_discover_tests(ComputationalMathTests
  PROPERTIES
    LABELS "unit"
  DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
    240
  )