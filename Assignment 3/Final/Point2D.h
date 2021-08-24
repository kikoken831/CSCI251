#ifndef POINT2D_H
#define POINT2D_H
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
using namespace std;
class Point2D
{
protected:
    int x;
    int y;
    double distFrOrigin;
    virtual double setDistFrOrigin();

public:
    Point2D(int x = 0, int y = 0);//constructor with default values for x and y
    double getScalarValue() const { return distFrOrigin; }
    int getX() const { return this->x; }
    int getY() const { return this->y; }
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    bool operator<(const Point2D &obj) const;//overloaded lesser<> opr for asc sort
    bool operator>(const Point2D &obj) const;//overloaded greater<> opr for dsc sort
    bool operator==(const Point2D &obj) const;//overloaded equal opr for equal function template
    friend ostream &operator<<(ostream &out, Point2D const &p)//overloaded insertion operator for cout and fstream out
    {
        return out << "[" << setw(4) << right << p.getX() << ", " << setw(4) << right << p.getY() << "]   " << fixed << setprecision(3) << left << p.getScalarValue();
    }
    static bool compare_X_asc(Point2D p1, Point2D p2)//static method for comparison for X asc to be used for sorting
    {
        if(p1.getX() < p2.getX())
        {
            return true;
        }
        else if(p1.getX() == p2.getX())
        {
            if(p1.getY() < p2.getY())
            {
                return true;
            }
            else
            {
                return false;
            }
            
        }
        else
        {
            return false;
        }

    }
    static bool compare_X_dsc(Point2D p1, Point2D p2)//static method for X dsc to be used for sorting
    {
        if(p1.getX() > p2.getX())
        {
            return true;
        }
        else if(p1.getX() == p2.getX())
        {
            if(p1.getY() > p2.getY())
            {
                return true;
            }
            else
            {
                return false;
            }
            
        }
        else
        {
            return false;
        }

    }
    static bool compare_Y_asc(Point2D p1, Point2D p2)//static method of Y asc to be used for sorting
    {
        if(p1.getY() < p2.getY())
        {
            return true;
        }
        else if(p1.getY() == p2.getY())
        {
            if(p1.getX() < p2.getX())
            {
                return true;
            }
            else
            {
                return false;
            }
            
        }
        else
        {
            return false;
        }

    }
    static bool compare_Y_dsc(Point2D p1, Point2D p2)//static method of Y Dsc to be used for sorting
    {
        if(p1.getY() > p2.getY())
        {
            return true;
        }
        else if(p1.getY() == p2.getY())
        {
            if(p1.getX() > p2.getX())
            {
                return true;
            }
            else
            {
                return false;
            }
            
        }
        else
        {
            return false;
        }

    }
};
#endif