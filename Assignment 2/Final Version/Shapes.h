#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <cmath>

using namespace std;

class ShapeTwoD // abstract class, only used to hold name, bool and id
{
    protected:
        string name;
        bool containsWarpSpace;
        int id;
        
    public:

        void setName(string name);

        void setContainsWarpSpace(bool containsWarpSpace);

        string getName();

        bool getContainsWarpSpace();
        //virtual polymorphic methods needed
        virtual string toString() = 0;

        virtual double computeArea() = 0;

        virtual bool isPointInShape(int x, int y) = 0;

        virtual bool isPointOnShape(int x, int y) = 0;

        virtual void set_ords() = 0;

        virtual void set_area() = 0;

        virtual double get_area() = 0;

        virtual ~ShapeTwoD() = default;//virtual destructor to prevent mem leaks
};

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

class Rectangle : public ShapeTwoD
{
private://additional attributes only unique to rectangle
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
class Circle : public ShapeTwoD
{
private://additional attributes only unique to circle
    int x_ord;
    int y_ord;
    int radius;
    double area = 0;

public:
    Circle(string name, bool containsWarpSpace, int id);

    void set_area();

    void set_ords();

    string toString();
    
    bool isPointOnShape(int x, int y);

    bool isPointInShape(int x, int y);

    double computeArea();

    double get_area();

   

};
class Cross : public ShapeTwoD
{
private://additional attributes only unique to Cross
    int x_ord[12];
    int y_ord[12];
    int area = 0;
    int x_min = INT_MAX;
    int y_min = INT_MAX;
    int x_max = 0;
    int y_max = 0;

public:
    Cross(string name, bool containsWarpSpace, int id);

    void set_area();

    void set_ords();

    string toString();
    
    double computeArea();

    bool isPointOnShape(int x, int y);

    bool isPointInShape(int x, int y);
    
    int pnpoly(int nvert, int *vertx, int *verty, int testx, int testy);

    bool isPointaVertex(int x, int y);

    double get_area();
 


};

#endif