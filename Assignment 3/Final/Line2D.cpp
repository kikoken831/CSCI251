#include "Line2D.h"

double Line2D::setLength()//set length algo to store length
{
    
    int x_sq =  pow((this->pt1.getX() - this->pt2.getX()),2);
    int y_sq = pow((this->pt1.getY() - this->pt2.getY()),2);
    
    return abs(sqrt(x_sq + y_sq));
}

void Line2D::setPt1(int x, int y)//setter for pt 1
{
    this->pt1.setX(x);
    this->pt1.setY(y);
}
void Line2D::setPt2(int x, int y)//setter for pt2
{
    this->pt2.setX(x);
    this->pt2.setY(y);
}
bool Line2D::operator<(const Line2D &obj) const
{
    return (length < obj.getScalarValue());
}
bool Line2D::operator>(const Line2D &obj) const
{
    return (length > obj.getScalarValue());
}
bool Line2D::operator==(const Line2D &obj) const
{
    return (pt1 == obj.getPt1() && pt2 == obj.getPt2());
}

