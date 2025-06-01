#pragma once
#include <functional>

namespace Render
{
    struct FrameBufferResizeEvent
    {
        const unsigned int Width, Height;
        FrameBufferResizeEvent(const unsigned int width, const unsigned int height) : Width(width), Height(height) {}
    };
    typedef std::function<void(FrameBufferResizeEvent& eventArgs)> FrameBufferResizeEventCallback;

    struct KeyEvent
    {
        const int Key, Action;
        KeyEvent(const int key, const int action) : Key(key), Action(action) {}
    };
    typedef std::function<void(KeyEvent& eventArgs)> KeyEventCallback;

    struct MouseMoveEvent
    {
        const double X, Y;
        MouseMoveEvent(const double x, const double y) : X(x), Y(y) {}
    };
    typedef std::function<void(MouseMoveEvent& eventArgs)> MouseMoveEventCallback;
}