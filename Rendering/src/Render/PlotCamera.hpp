#pragma once

#include <glm/glm.hpp>
#include <Render/Core/CameraTransformation.hpp>
#include <Render/Core/Renderer.hpp>

class PlotCamera
{
private:
    glm::vec3 m_up;
    glm::vec3 m_initialEye;
    float m_angle, m_rotationSpeed;
    CameraTransformation m_camera;

private:

public:
    PlotCamera();
    PlotCamera(glm::vec3 initialPosition, glm::vec3 up, float rotationSpeed = 1.0f);

    void Rotate(float delta);
    void Reset();
    void Apply(Renderer& renderer);
};