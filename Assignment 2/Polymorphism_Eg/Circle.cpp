
#include "Circle.h"

Circle::Circle (double r, int x, int y):Point (x,y)
{	
	radius = r;	
}

void Circle::draw() const
{
	cout << "draw circle (" << getx() << ", " << gety() << ", "
		 << radius << ") \n"; 
}




