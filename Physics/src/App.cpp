#include <iostream>
#include <Geometry/Rectangle.h>


int main()
{
	Rectangle rectangle;
	rectangle.Bottom = 1.0f;
	std::cout << rectangle.Bottom << std::endl;
	return 0;
}