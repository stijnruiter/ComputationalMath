#include "ObjectScene.hpp"

namespace Render
{
    ObjectScene::ObjectScene(bool is3d)
        : m_objects(0), m_is3d(is3d)
    {
    }

    void ObjectScene::AddObject(std::unique_ptr<DrawableObject> object)
    {
        m_objects.push_back(std::move(object));
    }

    void ObjectScene::Activate(Renderer& render, PlotCamera& camera)
    {
        if (m_is3d)
        {
            camera.Reset(glm::vec3(2.5, -2.5, 2.5), glm::vec3(0, 0, 1));
            render.EnableDepth();
        }
        else
        {
            camera.Reset(glm::vec3(0, 0, 2.5), glm::vec3(0, 1, 0));
            render.DisableDepth();
        }
    }

    void ObjectScene::Update(float deltaTime)
    {
        for (auto& object : m_objects)
        {
            object->Update(deltaTime);
        }
    }

    void ObjectScene::Draw(Renderer& render)
    {
        for (auto& object : m_objects)
        {
            object->Draw(render);
        }
    }
}