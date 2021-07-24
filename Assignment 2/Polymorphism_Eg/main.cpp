
// to compile, type:
// -----------------
// g++ Shape.cpp Point.cpp Circle.cpp main.cpp -o poly.exe
//
// to run, type:
// -------------
// ./poly.exe

#include "Shape.h"
#include "Point.h"
#include "Circle.h"

int main()
{
	Shape shape;
	Point point (7, 11);
	Circle circle (3.5, 22, 8);
	
	Shape *arrayOfShapes [3];

	arrayOfShapes [0] = &shape;
	arrayOfShapes [1] = &point;
	arrayOfShapes [2] = &circle;
	
	for (int i=0; i<3; i++)
		arrayOfShapes[i]->draw();


	return 0;
}
