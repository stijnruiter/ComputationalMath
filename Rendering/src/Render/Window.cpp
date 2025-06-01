#include "Window.hpp"

#include "Debug/Logger.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>

#include "Core/Renderer.hpp"
#include "PlotCamera.hpp"

namespace Render
{
    bool Window::InitializeGLFW()
    {
        int success = glfwInit();
        if (!success)
        {
            Debug::Logger::LogCritical("Unable to load GLFW.");
            return false;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwSetErrorCallback([](int error, const char* description)
                             { Debug::Logger::LogCritical("GLFW ERROR {0}: {1}", error, description); });
        return true;
    }

    bool Window::InitializeGlad()
    {
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            Debug::Logger::LogError("Unable to load GLAD.");
            return false;
        }
        return true;
    }

    Window::Window(int width, int height, std::string title) : m_width(width), m_height(height),
                                                                             m_title(title), m_currentScene(-1),
                                                                             m_scenes(0),
                                                                             m_camera(glm::vec3(0, 0, 2.5),
                                                                                      glm::vec3(0, 1, 0), 30.0)
    {
        if (!InitializeGLFW())
            return;

        m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if (!m_window)
        {
            Debug::Logger::LogCritical("Unable to create GLFW window");
            return;
        }
        glfwMakeContextCurrent(m_window);

        InitializeGlad();

        AttachEventCallbacks();
    }

    Window::~Window()
    {
        m_currentScene = -1;
        glfwDestroyWindow(m_window);
        m_window = nullptr;

        glfwTerminate();
    }

    void Window::AttachEventCallbacks()
    {
        glfwSetWindowUserPointer(m_window, this);

        glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* glfwWindow, int width, int height)
                                       {
            Window &window = *(Window *) glfwGetWindowUserPointer(glfwWindow);
            window.m_width = width;
            window.m_height = height;
            if (window.m_callbackFrameBuffer) {
                FrameBufferResizeEvent frameBufferEvent(width, height);
                window.m_callbackFrameBuffer(frameBufferEvent);
            } });

        glfwSetCursorPosCallback(m_window, [](GLFWwindow* glfwWindow, double x, double y)
                                 {
            Window &window = *(Window *) glfwGetWindowUserPointer(glfwWindow);
            if (window.m_callbackMouseMove) {
                MouseMoveEvent mouseEvent(x, y);
                window.m_callbackMouseMove(mouseEvent);
            } });

        glfwSetKeyCallback(m_window, [](GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
                           {
            Window &window = *(Window *) glfwGetWindowUserPointer(glfwWindow);
            if (window.m_keyEventCallback) {
                KeyEvent keyEvent(key, action);
                window.m_keyEventCallback(keyEvent);
            } });
    }

    void Window::SetMouseCursor(bool enabled)
    {
        if (enabled)
        {
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        else
        {
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }

    bool Window::ShouldClose()
    {
        return glfwWindowShouldClose(m_window);
    }

    void Window::SwapBuffers()
    {
        glfwSwapBuffers(m_window);
    }

    void Window::AddScene(std::unique_ptr<SceneBase> scene)
    {
        m_scenes.push_back(std::move(scene));
        if (m_currentScene < 0)
        {
            m_currentScene = 0;
        }
    }

    void Window::SwitchScene(size_t sceneIndex)
    {
        m_currentScene = sceneIndex;
    }

    void Window::Close()
    {
        glfwSetWindowShouldClose(m_window, true);
    }

    bool Window::IsKeyPressed(int key) const
    {
        return glfwGetKey(m_window, key) == GLFW_PRESS;
    }

    void Window::Run()
    {
        Renderer renderer;

        renderer.SetClearColor(0.2f, 0.3f, 0.3f);
        renderer.UpdateCamera(m_camera.GetTransformation());

        double deltaTime = 0.0;
        double lastFrame = 0.0;

        size_t lastFrameScene = m_currentScene;
        m_scenes[m_currentScene]->Activate(renderer, m_camera);

        while (!ShouldClose())
        {
            double currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            if (IsKeyPressed(GLFW_KEY_ESCAPE))
            {
                Close();
            }
            if (IsKeyPressed(GLFW_KEY_LEFT))
            {
                m_camera.Rotate(-deltaTime);
            }
            if (IsKeyPressed(GLFW_KEY_RIGHT))
            {
                m_camera.Rotate(+deltaTime);
            }

            renderer.UpdateCamera(m_camera.GetTransformation());

            if (lastFrameScene != m_currentScene)
            {
                lastFrameScene = m_currentScene;
                m_scenes[m_currentScene]->Activate(renderer, m_camera);
            }
            renderer.Clear();
            if (m_currentScene >= 0)
            {
                m_scenes[m_currentScene]->Update(deltaTime);
                m_scenes[m_currentScene]->Draw(renderer);
            }
            SwapBuffers();
            glfwPollEvents();
        }
    }
}