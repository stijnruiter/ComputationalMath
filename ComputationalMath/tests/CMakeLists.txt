include(FetchContent)
FetchContent_Declare(gtest
  QUIET
  URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz
)
# configure build of googletest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

add_executable(
    ComputationalMathTests
    "Geometry/RectangleTests.cpp"
    "LinearAlgebra/ColumnVectorTests.cpp"
     )

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
