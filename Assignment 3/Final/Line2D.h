#ifndef LINE2D_H
#define LINE2D_H

#include "Point2D.h"
class Line2D
{
protected:
    Point2D pt1;//stores 2  2D points
    Point2D pt2;
    double length;
    virtual double setLength();

public:
    Line2D(int x1 = 0, int x2 = 0, int x3 = 0, int x4 = 0)//constructor with default values of 0
    {
        this->pt1 = Point2D(x1, x2);
        this->pt2 = Point2D(x3, x4);
        this->length = this->setLength();
    }
    Line2D(Point2D p1, Point2D p2)//constructor that takes in 2 point object for template test in bonus files
    {
        this->pt1 = p1;
        this->pt2 = p2;
        this->length = this->setLength();
    }
    //getters and setters
    Point2D getPt1() const { return this->pt1; }
    Point2D getPt2() const { return this->pt2; }
    void setPt1(int x, int y);
    void setPt2(int x, int y);
    double getScalarValue() const { return this->length; }//gets length of linee
    bool operator<(const Line2D &obj) const;//overloaded lesser<> opr for asc sort by length
    bool operator>(const Line2D &obj) const;//overloaded greater<> opr for dsc sort by length
    bool operator==(const Line2D &obj) const;//overloaded equal opr for equals template func
    friend ostream &operator<<(ostream &out, Line2D const &p)//overloaded insertion opr for cout and fstream
    {
        return out << "[" << setw(4) << right << p.getPt1().getX() << ", " << setw(4) << right << p.getPt1().getY() << "]   [" << setw(4) << right << p.getPt2().getX() << ", " << setw(4) << right << p.getPt2().getY() << "]   " << fixed << setprecision(3) << left << p.getScalarValue();
    }
    static bool compare_p1_asc(Line2D l1, Line2D l2)//comparator func for p1 compare in asc order
    {
        return Point2D::compare_X_asc(l1.getPt1(),l2.getPt1());
    }
    static bool compare_p1_dsc(Line2D l1, Line2D l2)//comparator func for p1 compare in dsc order
    {
        return Point2D::compare_X_dsc(l1.getPt1(),l2.getPt1());
    }
    static bool compare_p2_asc(Line2D l1, Line2D l2)//comparator func for p2 compare in asc order
    {
        return Point2D::compare_X_asc(l1.getPt2(),l2.getPt2());
    }
    static bool compare_p2_dsc(Line2D l1, Line2D l2)//comparator func for p2 compare in dsc order
    {
        return Point2D::compare_X_dsc(l1.getPt2(),l2.getPt2());
    }
};

#endif