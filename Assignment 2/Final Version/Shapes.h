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

class ShapeTwoD
{
protected:
    string name;
    bool containsWarpSpace;
    int id;

public:
    ShapeTwoD()
    {
        name = "N/A";
        containsWarpSpace = false;
    }
    ShapeTwoD(string name , bool containsWarpSpace , int id)
    {
        this->name = name;
        this->containsWarpSpace = containsWarpSpace;
        this->id = id;
    }

    void setName(string name);

    void setContainsWarpSpace(bool containsWarpSpace);

    string getName();

    bool getContainsWarpSpace();

    virtual string toString() = 0;

    virtual double computeArea() = 0;

    virtual bool isPointInShape(int x, int y) = 0;

    virtual bool isPointOnShape(int x, int y) = 0;

    virtual void set_ords() = 0;

    virtual void set_area() = 0;

    virtual double get_area() = 0;
};

class Square : public ShapeTwoD
{
private:
    int x_ord[4];
    int y_ord[4];
    double area;
    int x_min;
    int y_min;
    int x_max;
    int y_max;

public:
    void set_area();
    Square(string name, bool containsWarpSpace, int id);
    void set_ords();
    string toString();
    double computeArea();
    bool isPointInShape(int x, int y);
    bool isPointOnShape(int x, int y);
    double get_area();
    bool operator>(const Square &str) const;
};

class Rectangle : public ShapeTwoD
{
private:
    int x_ord[4];
    int y_ord[4];
    double area;
    int x_min;
    int y_min;
    int x_max;
    int y_max;

public:
    void set_area();

    Rectangle(string name, bool containsWarpSpace, int id);

    void set_ords();

    string toString();

    bool isPointInShape(int x, int y);

    bool isPointOnShape(int x, int y);

    double computeArea();

    double get_area();

    bool operator>(const Rectangle &str) const;
};
class Circle : public ShapeTwoD
{
    int x_ord;
    int y_ord;
    int radius;
    double area;

public:
    Circle(string name, bool containsWarpSpace, int id);

    void set_area();

    void set_ords();

    string toString();
    
    bool isPointOnShape(int x, int y);

    bool isPointInShape(int x, int y);

    double computeArea();

    double get_area();

    bool operator>(const Circle &str) const;

};
class Cross : public ShapeTwoD
{

    int x_ord[12];
    int y_ord[12];
    double area;
    int x_min;
    int y_min;
    int x_max;
    int y_max;

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
 
    bool operator>(const Cross &str) const;

};

#endif