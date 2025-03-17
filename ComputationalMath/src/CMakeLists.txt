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
    ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra/SimdOps.cpp

  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Structures/HalfEdge.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Structures/HalfEdgeTriangulation.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Structures/Mesh2D.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Structures/PlanarStraightLineGraph.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Structures/Rectangle.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Structures/SimplexElements.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Structures/Triangle.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Structures/Vertex.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/RectangularMesh.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Delaunay.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/RefinedDelaunay.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra/FactorizationLU.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra/Matrix.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra/VectorBase.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra/SimdOps.hpp
)

target_include_directories(ComputationalMath
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )