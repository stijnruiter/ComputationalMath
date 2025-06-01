#pragma once

#include <glm/glm.hpp>

namespace Render
{
    struct CameraTransformation
    {
        glm::mat4 Model, View, Projection;
    };
}