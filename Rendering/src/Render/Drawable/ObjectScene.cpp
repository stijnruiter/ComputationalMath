#include "ObjectScene.hpp"

ObjectScene::ObjectScene()
    : m_objects(0)
{
}

void ObjectScene::AddObject(std::unique_ptr<DrawableObject> object)
{
    m_objects.push_back(std::move(object));
}

void ObjectScene::Update(float deltaTime)
{
    for(auto& object : m_objects)
    {
        object->Update(deltaTime);
    }
}

void ObjectScene::Draw(Renderer& render)
{
    for(auto& object : m_objects)
    {
        object->Draw(render);
    }
}
