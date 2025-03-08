add_library(ComputationalMath)

target_sources(ComputationalMath
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Rectangle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra/ColumnVector.cpp

  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra/ColumnVector.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/Rectangle.h
    
  )

target_include_directories(ComputationalMath
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )