#pragma once

struct Rectangle
{
public:
	float Left;
	float Right;
	float Bottom;
	float Top;

	Rectangle();
	Rectangle(float left, float right, float bottom, float top);
	float GetWidth();
	float GetHeight();

};