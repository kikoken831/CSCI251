#ifndef SQUARE_H
#define SQUARE_H

#include "ShapeTwoD.h"
class Square : public ShapeTwoD
{
private:
    //additional attributes only unique to square
    int x_ord[4];
    int y_ord[4];
    int area = 0;
    int x_min = INT_MAX;
    int y_min = INT_MAX;
    int x_max = 0;
    int y_max = 0;

public:
    void set_area();
    Square(string name, bool containsWarpSpace, int id);
    void set_ords();
    string toString();
    double computeArea();
    bool isPointInShape(int x, int y);
    bool isPointOnShape(int x, int y);
    double get_area();
};

#endif