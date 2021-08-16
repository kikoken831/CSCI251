#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "ShapeTwoD.h"
using namespace std;

class Rectangle : public ShapeTwoD
{
private: //additional attributes only unique to rectangle
    int x_ord[4];
    int y_ord[4];
    int area = 0;
    int x_min = INT_MAX;
    int y_min = INT_MAX;
    int x_max = 0;
    int y_max = 0;

public:
    void set_area();

    Rectangle(string name, bool containsWarpSpace, int id);

    void set_ords();

    string toString();

    bool isPointInShape(int x, int y);

    bool isPointOnShape(int x, int y);

    double computeArea();

    double get_area();
};

#endif