#pragma once

#include <string>

namespace Render::SolidColorShader
{
    const std::string GLSL_SHADER_VERTEX = R"(
        #version 330 core
        layout (location = 0) in vec3 aPosition;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main()
        {
            gl_Position = vec4(aPosition, 1.0) * model * view * projection;
        })";
    const std::string GLSL_SHADER_FRAGMENT = R"(
        #version 330 core

        in float FemValue;
        out vec4 FragColor;
        uniform vec4 drawColor; 

        void main()
        {
            FragColor = drawColor;
        }
    )";
}