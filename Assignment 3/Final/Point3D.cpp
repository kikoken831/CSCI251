#include "Point3D.h"

Point3D::Point3D(int x, int y, int z)
{
    //cout << "p3d construct" << endl;
    this->x = x;
    this->y = y;
    this->z = z;
    this->distFrOrigin = setDistFrOrigin();
}

double Point3D::setDistFrOrigin()//set distance algo for point3d
{
    return abs(sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z)));
}

bool Point3D::operator<(const Point3D &obj) const
{
    return (distFrOrigin < obj.getScalarValue());//lesser<> opr overload for sorting
}
bool Point3D::operator>(const Point3D &obj) const//greater<> opr overload for sorting
{
    return (distFrOrigin > obj.getScalarValue());
}
bool Point3D::operator==(const Point3D &obj) const//overloaded equal opr for equals template
{
    return (this->x == obj.getX() && this->y == obj.getY() && this->z == obj.getZ());
}