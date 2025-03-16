#include "PlotCamera.hpp"

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


PlotCamera::PlotCamera()
    : m_initialEye(2.5, 2.5, 2.5), m_angle(0), m_rotationSpeed(1.0), m_up(0, 1, 0)
{
    Reset();
}

PlotCamera::PlotCamera(glm::vec3 initialPosition, glm::vec3 up, float rotationSpeed)
    : m_initialEye(initialPosition), m_up(up), m_angle(0), m_rotationSpeed(rotationSpeed)
{
    Reset();
}

void PlotCamera::Rotate(float delta)
{
    m_angle += delta * m_rotationSpeed;
    m_camera.Model = glm::rotate(glm::mat4(1.0), glm::radians(-m_angle), glm::vec3(0, 0, 1));
}

void PlotCamera::Reset()
{
    m_camera.Model = glm::mat4(1.0);
    m_camera.View = glm::lookAt(m_initialEye, glm::vec3(0), m_up);
    m_camera.Projection = glm::perspective(glm::radians(45.0f), (float)800 / 600, 0.1f, 100.0f);
}
