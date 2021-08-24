#include "Point2D.h"

Point2D::Point2D(int x, int y)//constructor
{
    this->x = x;
    this->y = y;
    this->distFrOrigin = setDistFrOrigin();
}
double Point2D::setDistFrOrigin()//algo to get dist from origin
{
    return abs(sqrt((this->x * this->x) + (this->y * this->y)));
}

bool Point2D::operator<(const Point2D &obj) const//overloaded lesser<> opr for asc sort
{
    return (distFrOrigin < obj.getScalarValue());
}
bool Point2D::operator>(const Point2D &obj) const//overloaded greater<> opr for dsc sort
{
    return (distFrOrigin > obj.getScalarValue());
}
bool Point2D::operator==(const Point2D &obj) const//overloaded equal opr for equal function template
{
    return (this->x == obj.getX() && this->y == obj.getY());
}
