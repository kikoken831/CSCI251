
// to compile, type:
// -----------------
// g++ Shape.cpp Point.cpp Circle.cpp mainWithVector.cpp -o polyVec.exe
//
// to run, type:
// -------------
// ./polyVec.exe


#include "Shape.h"
#include "Point.h"
#include "Circle.h"

#include <vector>

int main()
{
	Shape shape;
	Point point (7, 11);
	Circle circle (3.5, 22, 8);
	
	vector<Shape *> shapeVector;

	shapeVector.push_back (&shape);
	shapeVector.push_back (&point);
	shapeVector.push_back (&circle);
	
	for (int i=0; i<shapeVector.size(); i++)
	{
		Shape * aShape = (Shape *) shapeVector [i];
		aShape->draw();
	}

	return 0;
}
