#include <iostream>
#include <Geometry/Rectangle.h>
#include <LinearAlgebra/Matrix.h>


int main()
{
	Rectangle rectangle;
	ColumnVector<int, 5> vector;
	std::cout << "Vector Row: " << vector.GetRowCount() << std::endl;
	std::cout << "Vector Column: " << vector.GetColumnCount() << std::endl;
	rectangle.Bottom = 1.0f;
	std::cout << rectangle.Bottom << std::endl;
	return 0;
}