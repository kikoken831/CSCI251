
#include "Point.h"

Point::Point (int a, int b)
{ 
	x = a;	
	y = b;
}
		
int Point::getx() const
{	
	return (x);	
}

int Point::gety() const
{	
	return (y);	
}
		
void Point::draw() const
{	
	cout << "draw point (" << x << ", " << y << ") \n";
}





