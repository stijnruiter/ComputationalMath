#pragma once

#include "Render/Core/Renderer.hpp"

class SceneBase
{
public:
    virtual void Update(float deltaTime) { };
    virtual void Draw(Renderer& render) { };
    virtual ~SceneBase() { };
};