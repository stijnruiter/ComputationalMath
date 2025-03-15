#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <string>
#include "Event.hpp"

class Window
{
private:
	GLFWwindow* m_window;

	int m_width;
	int m_height;
	std::string m_title;

private:
	bool InitializeGLFW();
	bool InitializeGlad();

	void AttachEventCallbacks();

	FrameBufferResizeEventCallback m_callbackFrameBuffer;
	MouseMoveEventCallback m_callbackMouseMove;
	KeyEventCallback m_keyEventCallback;

public:
	Window(int width, int height, std::string title);
	~Window();

	void SetMouseCursor(bool enabled);
	bool ShouldClose();
	void SwapBuffers();

	void Close();

	void SetCallbackOnFrameBufferResize(const FrameBufferResizeEventCallback& callback) { m_callbackFrameBuffer = callback; }
	void SetCallbackOnMouseMove(const MouseMoveEventCallback& callback) { m_callbackMouseMove = callback; }
	void SetCallbackOnKey(const KeyEventCallback& callback) { m_keyEventCallback = callback; }

	bool IsKeyPressed(int key) const;

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

	float GetAspectRatio() const { return m_height == 0 ? 1.0f : (float)m_width / m_height; } // Window is probably hidden, stop rendering;

};