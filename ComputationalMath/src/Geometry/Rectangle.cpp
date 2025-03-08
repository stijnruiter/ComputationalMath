#include "Rectangle.h"

Rectangle::Rectangle() : Rectangle(0, 0, 0, 0)
{
}

Rectangle::Rectangle(float left, float right, float bottom, float top)
{
	Left = left;
	Right = right;
	Bottom = bottom;
	Top = top;
}

float Rectangle::GetWidth()
{
	return Right - Left;
}

float Rectangle::GetHeight()
{
	return Top - Bottom;
}
