add_library(ComputationalMath)

target_sources(ComputationalMath
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Rectangle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra/Matrix.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra/SimdOps.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra/FactorizationLU.cpp

  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Rectangle.h
    ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra/Matrix.h
    ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra/VectorBase.h
    ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra/FactorizationLU.h
    ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra/OpsHelper.h
    ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra/SimdOps.h
)

target_include_directories(ComputationalMath
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )