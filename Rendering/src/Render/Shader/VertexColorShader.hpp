#pragma once

#include <string>

namespace Render::VertexColorShader
{
    const std::string GLSL_SHADER_VERTEX = R"(
        #version 330 core
        layout (location = 0) in vec3 vertPosition;
        layout (location = 1) in vec3 vertColor;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        out vec4 color;

        void main()
        {
            gl_Position = vec4(vertPosition, 1.0) * model * view * projection;
            color = vec4(vertColor, 1.0);
        })";
    const std::string GLSL_SHADER_FRAGMENT = R"(
        #version 330 core

        in vec4 color;
        out vec4 FragColor;

        void main()
        {
            FragColor = color;
        }
    )";
}