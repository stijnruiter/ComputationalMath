add_library(ComputationalMath)

target_sources(ComputationalMath
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Structures/HalfEdgeTriangulation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Structures/Mesh2D.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Structures/PlanarStraightLineGraph.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Structures/Rectangle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Structures/SimplexElements.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Structures/Triangle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Structures/Vertex.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Delaunay.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/RefinedDelaunay.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra/FactorizationLU.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra/Matrix.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra/SimdOps.cpp

  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Structures/HalfEdge.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Structures/HalfEdgeTriangulation.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Structures/Mesh2D.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Structures/PlanarStraightLineGraph.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Structures/Rectangle.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Structures/SimplexElements.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Structures/Triangle.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Structures/Vertex.h

    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Delaunay.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/RefinedDelaunay.h

    ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra/FactorizationLU.h
    ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra/Matrix.h
    ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra/VectorBase.h
    ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra/SimdOps.h
)

target_include_directories(ComputationalMath
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )