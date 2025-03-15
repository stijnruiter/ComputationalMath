#include "Window.hpp"

#include "glad\glad.h"
#include <GLFW\glfw3.h>
#include <string>
#include "Debug/Logger.hpp"

bool Window::InitializeGLFW()
{
    int success = glfwInit();
    if (!success)
    {
        Engine::Logger::LogCritical("Unable to load GLFW.");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback([](int error, const char* description)
    {
        Engine::Logger::LogCritical("GLFW ERROR {0}: {1}", error, description);
    });
    return true;
}
bool Window::InitializeGlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Engine::Logger::LogError("Unable to load GLAD.");
        return false;
    }
    return true;
}

Window::Window(int width, int height, std::string title) : 
    m_width(width), m_height(height), m_title(title)
{
    if (!InitializeGLFW())
        return;

    m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!m_window)
    {
        Engine::Logger::LogCritical("Unable to create GLFW window");
        return;
    }
    glfwMakeContextCurrent(m_window);
    
    InitializeGlad();

    AttachEventCallbacks();
}

Window::~Window() 
{
    glfwDestroyWindow(m_window);
    m_window = nullptr;

    glfwTerminate();
}

void Window::AttachEventCallbacks()
{
    glfwSetWindowUserPointer(m_window, this);

    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* glfwWindow, int width, int height)
    {
        Window& window = *(Window*)glfwGetWindowUserPointer(glfwWindow);
        window.m_width = width;
        window.m_height = height;
        if (window.m_callbackFrameBuffer)
        {
            FrameBufferResizeEvent frameBufferEvent(width, height);
            window.m_callbackFrameBuffer(frameBufferEvent);
        }
    });

    glfwSetCursorPosCallback(m_window, [](GLFWwindow* glfwWindow, double x, double y)
    {
        Window& window = *(Window*)glfwGetWindowUserPointer(glfwWindow);
        if (window.m_callbackMouseMove)
        {
            MouseMoveEvent mouseEvent(x, y);
            window.m_callbackMouseMove(mouseEvent);
        }
    });

    glfwSetKeyCallback(m_window, [](GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
    {
        Window& window = *(Window*)glfwGetWindowUserPointer(glfwWindow);
        if (window.m_keyEventCallback)
        {
            KeyEvent keyEvent(key, action);
            window.m_keyEventCallback(keyEvent);
        }
    });
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

void Window::Close()
{
    glfwSetWindowShouldClose(m_window, true);
}

bool Window::IsKeyPressed(int key) const
{
    return glfwGetKey(m_window, key) == GLFW_PRESS;
}