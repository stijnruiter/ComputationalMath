file(GLOB_RECURSE SRC_FILES src/*.cpp)
# add_executable(Physics WIN32 ${SRC_FILES})
add_executable(Physics ${SRC_FILES})

target_link_libraries(Physics ComputationalMath Rendering)
target_include_directories(Physics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(Physics PUBLIC $<TARGET_PROPERTY:glad,INCLUDE_DIRECTORIES>)

target_compile_definitions(Physics PRIVATE $<$<CONFIG:Debug>:DEBUG>)

if( MSVC )
	set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Physics )
endif()