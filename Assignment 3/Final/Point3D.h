#ifndef POINT3D_H
#define POINT3D_H
#include "Point2D.h"

class Point3D : public Point2D
{
protected:
    int z;
    double setDistFrOrigin();

public:
    Point3D(int x = 0, int y = 0, int z = 0);//constructor with default value of 0
    int getZ() const{ return this->z; }//get Z
    void setZ(int z){ this->z = z; }//set Z
    bool operator<(const Point3D &obj) const;//lesser<> opr overload for sorting
    bool operator>(const Point3D &obj) const;//greater<> opr overload for sorting
    bool operator==(const Point3D &obj) const;//overloaded equal opr for equals template
    friend ostream& operator<< (ostream &out, Point3D const& p)//overloaded insertion opr
    {
        return out << "[" << setw(4) << right << p.getX() << ", " << setw(4) << right << p.getY()<< ", " << setw(4) << right << p.getZ() << "]   " << fixed << setprecision(3) << left << p.getScalarValue();
    }

    static bool compare_X_asc(Point3D p1, Point3D p2)//static method for comparing X in ASC order
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
            else if(p1.getY() == p2.getY() && p1.getZ() < p2.getZ())
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
    static bool compare_X_dsc(Point3D p1, Point3D p2)//static method for comparing X in DSC order
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
            else if(p1.getY() == p2.getY() && p1.getZ() > p2.getZ())
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
    static bool compare_Y_asc(Point3D p1, Point3D p2)//static method for comparing Y in ASC order
    {
        if(p1.getY() < p2.getY())
        {
            return true;
        }
        else if(p1.getY() == p2.getY())
        {
            if(p1.getZ() < p2.getZ())
            {
                return true;
            }
            else if(p1.getZ() == p2.getZ() && p1.getX() < p2.getX())
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
    static bool compare_Y_dsc(Point3D p1, Point3D p2)//static method for comparing Y in DSC order
    {
        if(p1.getY() > p2.getY())
        {
            return true;
        }
        else if(p1.getY() == p2.getY())
        {
            if(p1.getZ() > p2.getZ())
            {
                return true;
            }
            else if(p1.getZ() == p2.getZ() && p1.getX() > p2.getX())
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
    static bool compare_Z_asc(Point3D p1, Point3D p2)//static method for comparing Z in ASC order
    {
        if(p1.getZ() < p2.getZ())
        {
            return true;
        }
        else if(p1.getZ() == p2.getZ())
        {
            if(p1.getX() < p2.getX())
            {
                return true;
            }
            else if(p1.getX() == p2.getX() && p1.getY() < p2.getY())
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
    static bool compare_Z_dsc(Point3D p1, Point3D p2)//static method for comparing Z in DSC order
    {
        if(p1.getZ() > p2.getZ())
        {
            return true;
        }
        else if(p1.getZ() == p2.getZ())
        {
            if(p1.getX() > p2.getX())
            {
                return true;
            }
            else if(p1.getX() == p2.getX() && p1.getY() > p2.getY())
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