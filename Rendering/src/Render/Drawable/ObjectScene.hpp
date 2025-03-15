#pragma once

#include "Render/Drawable/SceneBase.hpp"
#include "Render/Drawable/DrawableObject.hpp"
#include <vector>
#include <memory>

class ObjectScene : public SceneBase
{
public:
    ObjectScene();

    void AddObject(std::unique_ptr<DrawableObject> object);
    virtual void Update(float deltaTime) override;
    virtual void Draw(Renderer& render) override;

private:
    std::vector<std::unique_ptr<DrawableObject>> m_objects;
};
