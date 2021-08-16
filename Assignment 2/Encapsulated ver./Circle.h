#ifndef CIRCLE_H
#define CIRCLE_H


#include "ShapeTwoD.h"
using namespace std;

class Circle : public ShapeTwoD
{
private: //additional attributes only unique to circle
    int x_ord;
    int y_ord;
    int radius;
    double area = 0;

public:
    Circle(string name, bool containsWarpSpace, int id);

    void set_area();

    void set_ords();

    string toString();

    bool isPointOnShape(int x, int y);

    bool isPointInShape(int x, int y);

    double computeArea();

    double get_area();
};


#endif