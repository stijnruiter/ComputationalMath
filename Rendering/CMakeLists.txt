## CMAKE file for all OpenGL dependencies
# Currently using glad and GLFW
project(Rendering)

find_package( OpenGL REQUIRED )
include_directories( ${OPENGL_INCLUDE_DIRS} )

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )

add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)

include_directories(lib/glad/include)
add_library(glad STATIC lib/glad/src/glad.c)

add_subdirectory(src)