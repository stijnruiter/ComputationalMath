#pragma once
#include <functional>

struct FrameBufferResizeEvent
{
public:
	const unsigned int Width, Height;
	FrameBufferResizeEvent(unsigned int Width, unsigned int Height) : Width(Width), Height(Height) { }
};
typedef std::function<void(FrameBufferResizeEvent& eventArgs)> FrameBufferResizeEventCallback;

struct KeyEvent
{
public:
	const int Key, Action;
	KeyEvent(int Key, int Action) : Key(Key), Action(Action) { }
};
typedef std::function<void(KeyEvent& eventArgs)> KeyEventCallback;

struct MouseMoveEvent
{
public:
	const double X, Y;
	MouseMoveEvent(double X, double Y) : X(X), Y(Y) { }
};
typedef std::function<void(MouseMoveEvent& eventArgs)> MouseMoveEventCallback;