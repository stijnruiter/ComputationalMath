#pragma once

#include <Render/Core/CameraTransformation.hpp>
#include <glm/glm.hpp>

namespace Render
{
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
        const CameraTransformation& GetTransformation() const { return m_camera; }
        void Rotate(float delta);
        void Reset();
        void Reset(const glm::vec3& initialPosition, const glm::vec3& up);
    };
}