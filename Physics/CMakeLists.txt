# file(GLOB_RECURSE SRC_FILES src/*.cpp)
# add_executable(Physics WIN32 ${SRC_FILES})
add_executable(Physics)

target_sources(Physics
	PRIVATE
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp

	  ${CMAKE_CURRENT_SOURCE_DIR}/src/Drawables/Axis.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/Drawables/DrawableMesh.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/Drawables/DrawableGraph.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/Drawables/DrawableTimeDependentFemMesh.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/Fem/HelmholtzEquationWithSource.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/Fem/HeatEquationWithoutSource.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/Fem/LaplaceFem.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/Fem/FemAssembler.cpp
	
	PUBLIC
    	${CMAKE_CURRENT_SOURCE_DIR}/src/Drawables/Axis.hpp
    	${CMAKE_CURRENT_SOURCE_DIR}/src/Drawables/DrawableMesh.hpp
    	${CMAKE_CURRENT_SOURCE_DIR}/src/Drawables/DrawableGraph.hpp
	  	${CMAKE_CURRENT_SOURCE_DIR}/src/Drawables/DrawableTimeDependentFemMesh.hpp
    	
		${CMAKE_CURRENT_SOURCE_DIR}/src/Fem/HeatEquationWithoutSource.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/Fem/LaplaceFem.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/Fem/FemAssembler.hpp


)

target_include_directories(Physics
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(Physics ComputationalMath Rendering)
target_include_directories(Physics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(Physics PUBLIC $<TARGET_PROPERTY:glad,INCLUDE_DIRECTORIES>)

target_compile_definitions(Physics PRIVATE $<$<CONFIG:Debug>:DEBUG>)

if( MSVC )
	set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Physics )
endif()