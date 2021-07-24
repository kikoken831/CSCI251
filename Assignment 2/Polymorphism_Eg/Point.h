
#ifndef POINT_H
#define POINT_H

#include <iostream>

#include "Shape.h"

using namespace std;

class Point : public Shape
{
	public:
		Point (int a=0, int b=0);
		int getx() const;
		int gety() const;
		
//		void draw() const
		virtual void draw() const;
		
	private:
		int x, y;

};

#endif
