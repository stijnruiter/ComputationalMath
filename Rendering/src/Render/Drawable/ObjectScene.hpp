#pragma once

#include "Render/Drawable/DrawableObject.hpp"
#include "Render/Drawable/SceneBase.hpp"
#include <memory>
#include <vector>

class ObjectScene : public SceneBase
{
public:
    ObjectScene(bool is3d);

    void AddObject(std::unique_ptr<DrawableObject> object);
    virtual void Activate(Renderer& render, PlotCamera& camera) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw(Renderer& render) override;

private:
    std::vector<std::unique_ptr<DrawableObject>> m_objects;
    bool m_is3d;
};
