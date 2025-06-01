#pragma once

#include "Render/Drawable/DrawableObject.hpp"
#include "Render/Drawable/SceneBase.hpp"
#include <memory>
#include <vector>

namespace Render
{
    class ObjectScene : public SceneBase
    {
    public:
        explicit ObjectScene(bool is3d);

        void AddObject(std::unique_ptr<DrawableObject> object);
        void Activate(Renderer& render, PlotCamera& camera) override;
        void Update(float deltaTime) override;
        void Draw(Renderer& render) override;

    private:
        std::vector<std::unique_ptr<DrawableObject>> m_objects;
        bool m_is3d;
    };
}