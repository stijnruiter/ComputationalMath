#pragma once

#include "Render/Core/Renderer.hpp"
#include "Render/PlotCamera.hpp"

class SceneBase
{
public:
    virtual void Activate(Renderer& render, PlotCamera& camera) { };
    virtual void Update(float deltaTime) { };
    virtual void Draw(Renderer& render) { };
    virtual ~SceneBase() { };
};