add_library(Rendering)

target_sources(Rendering
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Render/Core/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Render/Core/ShaderProgram.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Render/Core/VertexArrayObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Render/Core/VertexBuffer.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Render/Debug/gl_debug.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Render/Debug/Logger.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Render/Drawable/ObjectScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Render/PlotCamera.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Render/Window.cpp

  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Render/Core/CameraTransformation.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Render/Core/IndexBuffer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Render/Core/Renderer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Render/Core/ShaderProgram.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Render/Core/VertexArrayObject.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Render/Core/VertexBuffer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Render/Core/CameraTransformation.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Render/Debug/gl_debug.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Render/Debug/Logger.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Render/Shader/SolidColorShader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Render/Shader/VertexColorShader.hpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/Render/Drawable/SceneBase.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Render/Drawable/ObjectScene.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Render/Drawable/DrawableObject.hpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/Render/PlotCamera.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Render/Event.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Render/Window.hpp
)

target_include_directories(Rendering
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(Rendering ${OPENGL_LIBRARIES} glfw glad glm)