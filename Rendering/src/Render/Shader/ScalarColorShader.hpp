#pragma once

#include <string>

namespace ScalarColorShader
{
    const std::string GLSL_SHADER_VERTEX = R"(
        #version 330 core
        layout (location = 0) in vec3 aPosition;
        layout (location = 1) in float gradientValue;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        out float gradient;

        void main()
        {
            gl_Position = vec4(aPosition, 1.0) * model * view * projection;
            gradient = gradientValue;
        })";

    const std::string GLSL_SHADER_FRAGMENT = R"(
        #version 330 core

        in float gradient;

        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(gradient, 0.6f, 0.3f, 1.0f);
        }
    )";
}