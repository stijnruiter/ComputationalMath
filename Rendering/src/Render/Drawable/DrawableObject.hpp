#pragma once

#include "Render/Core/Renderer.hpp"

class DrawableObject
{
public:
    virtual void Update(float deltaTime) { }
    virtual void Draw(Renderer& renderer) { }
    virtual ~DrawableObject() { }
};