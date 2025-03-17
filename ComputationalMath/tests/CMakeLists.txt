
# Include Google Test
include(../cmake/GoogleTest.cmake)

## ComputationalMathTests
add_executable(
    ComputationalMathTests
    "Geometry/Structures/RectangleTests.cpp"
    "Geometry/Structures/VertexTests.cpp"
    "Geometry/Structures/SimplexElementTests.cpp"
    "Geometry/DelaunayTests.cpp"
    "Geometry/RefinedDelaunayTests.cpp"
    "LinearAlgebra/MatrixTests.cpp"  
    "LinearAlgebra/VectorBaseTests.cpp"  
    "LinearAlgebra/FactorizationLuTests.cpp"  
    "LinearAlgebra/SimdTests.cpp"
    
    "TestHelper.cpp"
    "TestHelper.hpp")

target_include_directories(ComputationalMathTests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

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