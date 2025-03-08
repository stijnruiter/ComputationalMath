#include <iostream>
#include <Geometry/Rectangle.h>
#include <LinearAlgebra/ColumnVector.h>


int main()
{
	Rectangle rectangle;
	ColumnVector<int> vector;
	std::cout << "Vector length: " << vector.GetLength() << std::endl;
	rectangle.Bottom = 1.0f;
	std::cout << rectangle.Bottom << std::endl;
	return 0;
}