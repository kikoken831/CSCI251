#ifndef LINE3D_H
#define LINE3D_H
#include "Line2D.h"
#include "Point3D.h"
class Line3D : public Line2D
{
protected:
    Point3D pt1;//consists of 2 3D points
    Point3D pt2;
    double setLength();

public:
    Line3D(){};
    Line3D(int x1, int x2, int x3, int x4, int x5, int x6)//constructor for main function
    {
        this->pt1 = Point3D(x1, x2, x3);
        this->pt2 = Point3D(x4, x5, x6);
        this->length = this->setLength();
    }
    Line3D(Point3D p1, Point3D p2)//constructor for bonus main.cpp to take in 2 objects instead of int vals
    {
        this->pt1 = p1;
        this->pt2 = p2;
        this->length = this->setLength();
    }
    Point3D getPt1() const { return this->pt1; }
    Point3D getPt2() const { return this->pt2; }
    void setPt1(int x, int y, int z);
    void setPt2(int x, int y, int z);
    bool operator<(const Line3D &obj) const;//overloaded opr for sorting by length in asc ord
    bool operator>(const Line3D &obj) const;//overloaded opr for sorting by length in dsc ord
    friend ostream &operator<<(ostream &out, Line3D const &p)//overloaded insertion opr for cout and fstream
    {
        return out << "[" << setw(4) << right << p.getPt1().getX() << ", " << setw(4) << right << p.getPt1().getY() << ", " << setw(4) << right << p.getPt1().getZ() << "]   [" << setw(4) << right << p.getPt2().getX() << ", " << setw(4) << right << p.getPt2().getY() << ", " << setw(4) << right << p.getPt2().getZ() << "]   " << fixed << setprecision(3) << left << p.getScalarValue();
    }
    bool operator==(const Line3D &obj) const//overloaded equals operator for equals template
    {
        return (pt1 == obj.getPt1() && pt2 == obj.getPt2());
    }
    static bool compare_p1_asc(Line3D l1, Line3D l2)//static comparator function for sorting Line3D reusing the comparator func of Point3D for asc order
    {
        return Point3D::compare_X_asc(l1.getPt1(),l2.getPt1());
    }
    static bool compare_p1_dsc(Line3D l1, Line3D l2)//static comparator function for sorting Line3D reusing the comparator func of Point3D for dsc order
    {
        return Point3D::compare_X_dsc(l1.getPt1(),l2.getPt1());
    }
    static bool compare_p2_asc(Line3D l1, Line3D l2)//static comparator function for sorting Line3D reusing the comparator func of Point3D for asc order (point2)
    {
        return Point3D::compare_X_asc(l1.getPt2(),l2.getPt2());
    }
    static bool compare_p2_dsc(Line3D l1, Line3D l2)//static comparator function for sorting Line3D reusing the comparator func of Point3D for dsc order (point2)
    {
        return Point3D::compare_X_dsc(l1.getPt2(),l2.getPt2());
    }
};
#endif