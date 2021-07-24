
#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>

#include "Point.h"

using namespace std;

class Circle : public Point
{
	public:
		Circle (double r=0.0, int x=0, int y=0);
//		void draw() const;
		virtual void draw() const;

	private:
		double radius;
};

#endif
