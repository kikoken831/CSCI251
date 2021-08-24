#include "Line3D.h"

double Line3D::setLength()//algo for getting length
{   
    int x_sq =  pow((this->pt1.getX() - this->pt2.getX()),2);
    int y_sq = pow((this->pt1.getY() - this->pt2.getY()),2);
    int z_sq = pow((this->pt1.getZ() - this->pt2.getZ()),2);

    return abs(sqrt(x_sq + y_sq + z_sq));
}
//setters
void Line3D::setPt1(int x, int y, int z)
{
    this->pt1.setX(x);
    this->pt1.setY(y);
    this->pt1.setZ(z);
}
void Line3D::setPt2(int x, int y, int z)
{
    this->pt2.setX(x);
    this->pt2.setY(y);
    this->pt2.setZ(z);
}

bool Line3D::operator<(const Line3D &obj) const//overloaded opr for sorting by length in asc ord
{
    return (length < obj.getScalarValue());
}
bool Line3D::operator>(const Line3D &obj) const//overloaded opr for sorting by length in dsc ord
{
    return (length > obj.getScalarValue());
}