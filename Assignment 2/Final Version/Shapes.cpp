#include "Shapes.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <cmath>

using namespace std;

void ShapeTwoD::setName(string name)
{
    this->name = name;
}

void ShapeTwoD::setContainsWarpSpace(bool containsWarpSpace)
{
    this->containsWarpSpace = containsWarpSpace;
}

string ShapeTwoD::getName()
{
    return name;
}
bool ShapeTwoD::getContainsWarpSpace()
{
    return containsWarpSpace;
}

Square::Square(string name, bool containsWarpSpace, int id)
{
    this->name = name;
    this->containsWarpSpace = containsWarpSpace;
    this->id = id;
}
void Square::set_area()
{
    this->area = computeArea();
}
void Square::set_ords()
{
    for (int i = 0; i < 4; i++)
    {
        cout << "Please enter x-ordiante of pt." << i + 1 << " : ";
        cin >> this->x_ord[i];
        cout << "Please enter y-ordiante of pt." << i + 1 << " : ";
        cin >> this->y_ord[i];
        if (i == 0)
        {
            this->x_min = this->x_ord[i];
            this->y_min = this->y_ord[i];
        }
        if (this->x_ord[i] < x_min)
            this->x_min = this->x_ord[i];
        if (this->y_ord[i] < y_min)
            this->y_min = this->y_ord[i];
        if (this->x_ord[i] > x_max)
            this->x_max = this->x_ord[i];
        if (this->y_ord[i] > y_max)
            this->y_max = this->y_ord[i];
    }
}
string Square::toString()
{
    bool isCord = false;
    string stype = (this->containsWarpSpace) ? "WS" : "NS";
    ostringstream os;
    os << "Shape [" << this->id << "]\n";
    os << "Name  : " << this->name << endl
       << "Special Type : " << stype << endl
       << "Area : " << this->area << " units square" << endl
       << "Vectices : \n";
    for (int i = 0; i < 4; i++)
    {
        os << "Point [" << i << "] : (" << x_ord[i] << ", " << y_ord[i] << ")\n";
    }
    int iPoS_count = 0;
    os << "Points on Perimeter : ";
    for (int i = x_min; i <= x_max; i++)
    {
        for (int j = y_min; j <= y_max; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                if (x_ord[k] == i && y_ord[k] == j)
                    isCord = true;
            }
            if (isPointOnShape(i, j) && !isCord)
            {
                os << "(" << i << ", " << j << "), ";
                iPoS_count++;
            }
            isCord = false;
        }
    }
    if (iPoS_count == 0)
    {
        os << "None!";
    }
    else
    {
        os << "\b\b"
           << "  ";
    }

    if (this->area < 4)
        os << "\n\nPoints within shape : none!";
    else
    {
        os << "\n\nPoints within shape : ";
        for (int i = x_min; i <= x_max; i++)
        {
            for (int j = y_min; j <= y_max; j++)
            {
                if (isPointInShape(i, j))
                {
                    os << "(" << i << ", " << j << "), ";
                }
            }
        }
        os << "\b\b"
           << "  ";
    }

    return os.str();
}
double Square::computeArea()
{
    double ar = 0; // Accumulates area
    int j = 3;

    for (int i = 0; i < 4; i++)
    {
        ar += (x_ord[j] + x_ord[i]) * (y_ord[j] - y_ord[i]);
        j = i; //j is previous vertex to i
    }
    ar = ar / 2;
    ar = abs(ar);
    return ar;
}
bool Square::isPointInShape(int x, int y)
{
    if (x < this->x_max && x > this->x_min && y < this->y_max && y > this->y_min)
    {
        return true;
    }
    else
        return false;
}
bool Square::isPointOnShape(int x, int y)
{
    if (x == this->x_min && y >= this->y_min && y <= this->y_max)
        return true;
    else if (y == this->y_max && x >= this->x_min && x <= this->x_max)
        return true;
    else if (x == this->x_max && y >= this->y_min && y <= this->y_max)
        return true;
    else if (y == this->y_min && x >= this->x_min && x <= this->x_max)
        return true;
    else
        return false;
}
double Square::get_area()
{
    return this->area;
}

Rectangle::Rectangle(string name, bool containsWarpSpace, int id)
{
    this->name = name;
    this->containsWarpSpace = containsWarpSpace;
    this->id = id;
}
void Rectangle::set_area()
{
    this->area = computeArea();
}
void Rectangle::set_ords()
{
    for (int i = 0; i < 4; i++)
    {
        cout << "Please enter x-ordiante of pt." << i + 1 << " : ";
        cin >> this->x_ord[i];
        cout << "Please enter y-ordiante of pt." << i + 1 << " : ";
        cin >> this->y_ord[i];
        if (i == 0)
        {
            this->x_min = this->x_ord[i];
            this->y_min = this->y_ord[i];
        }
        if (this->x_ord[i] < x_min)
            this->x_min = this->x_ord[i];
        if (this->y_ord[i] < y_min)
            this->y_min = this->y_ord[i];
        if (this->x_ord[i] > x_max)
            this->x_max = this->x_ord[i];
        if (this->y_ord[i] > y_max)
            this->y_max = this->y_ord[i];
    }
}
string Rectangle::toString()
{
    bool isCord = false;
    string stype = (this->containsWarpSpace) ? "WS" : "NS";
    ostringstream os;
    os << "Shape [" << this->id << "]\n";
    os << "Name  : " << this->name << endl
       << "Special Type : " << stype << endl
       << "Area : " << this->area << " units square" << endl
       << "Vectices : \n";
    for (int i = 0; i < 4; i++)
    {
        os << "Point [" << i << "] : (" << x_ord[i] << ", " << y_ord[i] << ")\n";
    }
    int iPoS_count = 0;
    os << "Points on Perimeter : ";
    for (int i = x_min; i <= x_max; i++)
    {
        for (int j = y_min; j <= y_max; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                if (x_ord[k] == i && y_ord[k] == j)
                    isCord = true;
            }
            if (isPointOnShape(i, j) && !isCord)
            {
                os << "(" << i << ", " << j << "), ";
                iPoS_count++;
            }
            isCord = false;
        }
    }
    if (iPoS_count == 0)
    {
        os << "None!";
    }
    else
    {
        os << "\b\b"
           << "  ";
    }
    os << "\b\b"
       << "  ";
    if (x_max - x_min == 1 || y_max - y_min == 1)
        os << "\n\nPoints within shape : none!";
    else
    {
        os << "\n\nPoints within shape : ";
        for (int i = x_min; i <= x_max; i++)
        {
            for (int j = y_min; j <= y_max; j++)
            {
                if (isPointInShape(i, j))
                {
                    os << "(" << i << ", " << j << "), ";
                }
            }
        }
        os << "\b\b"
           << "  ";
    }

    return os.str();
}
bool Rectangle::isPointInShape(int x, int y)
{
    if (x < this->x_max && x > this->x_min && y < this->y_max && y > this->y_min)
    {
        return true;
    }
    else
        return false;
}
bool Rectangle::isPointOnShape(int x, int y)
{
    if (x == this->x_min && y >= this->y_min && y <= this->y_max)
        return true;
    else if (y == this->y_max && x >= this->x_min && x <= this->x_max)
        return true;
    else if (x == this->x_max && y >= this->y_min && y <= this->y_max)
        return true;
    else if (y == this->y_min && x >= this->x_min && x <= this->x_max)
        return true;
    else
        return false;
}
double Rectangle::computeArea()
{
    double ar = 0; // Accumulates area
    int j = 3;

    for (int i = 0; i < 4; i++)
    {
        ar += (x_ord[j] + x_ord[i]) * (y_ord[j] - y_ord[i]);
        j = i; //j is previous vertex to i
    }
    ar = ar / 2;
    ar = abs(ar);
    return ar;
}
double Rectangle::get_area()
{
    return this->area;
}


Circle::Circle(string name, bool containsWarpSpace, int id)
{
    this->name = name;
    this->containsWarpSpace = containsWarpSpace;
    this->id = id;
}
void Circle::set_area()
{
    this->area = computeArea();
}
void Circle::set_ords()
{

    cout << "Please enter x-ordiante of center : ";
    cin >> this->x_ord;
    cout << "Please enter y-ordiante of center : ";
    cin >> this->y_ord;
    cout << "Please enter radius(units) : ";
    cin >> this->radius;
}
string Circle::toString()
{
    string stype = (this->containsWarpSpace) ? "WS" : "NS";
    ostringstream os;
    os << "Shape [" << this->id << "]\n";
    os << "Name  : " << this->name << endl
       << "Special Type : " << stype << endl
       << "Area : " << fixed << setprecision(2) << area << " units square" << endl
       << "Vectices : \n"
       << "Point [0] : (" << this->x_ord << ", " << this->y_ord << ")\n"
       << "Points on Perimeter : ";
    for (int i = x_ord - radius; i <= x_ord + radius; i++)
    {
        for (int j = y_ord - radius; j <= y_ord + radius; j++)
        {
            if (isPointOnShape(i, j))
            {
                os << "(" << i << ", " << j << "), ";
            }
        }
    }
    os << "\b\b"
       << "  ";
    if (this->radius == 1)
        os << "\n\nPoints within shape : none!";
    else
    {
        os << "\n\nPoints within shape : ";
        for (int i = x_ord - radius; i < x_ord + radius; i++)
        {
            for (int j = y_ord - radius; j < y_ord + radius; j++)
            {
                if (i == x_ord && j == y_ord)
                {
                    continue;
                }
                if (isPointInShape(i, j))
                {
                    os << "(" << i << ", " << j << "), ";
                }
            }
        }
        os << "\b\b"
           << "  ";
    }

    return os.str();
}
bool Circle::isPointOnShape(int x, int y)
{
    if (x == x_ord && y == y_ord + radius)
        return true;
    else if (x == x_ord + radius && y == y_ord)
        return true;
    else if (x == x_ord && y == y_ord - radius)
        return true;
    else if (x == x_ord - radius && y == y_ord)
        return true;
    else
        return false;
}
bool Circle::isPointInShape(int x, int y)
{
    if (pow((x - this->x_ord), 2) + pow((y - this->y_ord), 2) < this->radius * this->radius)
        return true;
    else
        return false;
}
double Circle::computeArea()
{
    return M_PI * (this->radius * 2);
}
double Circle::get_area()
{
    return this->area;
}

Cross::Cross(string name, bool containsWarpSpace, int id)
{
    this->name = name;
    this->containsWarpSpace = containsWarpSpace;
    this->id = id;
}
void Cross::set_area()
{
    this->area = computeArea();
}
void Cross::set_ords()
{
    for (int i = 0; i < 12; i++)
    {
        cout << "Please enter x-ordiante of pt." << i + 1 << " : ";
        cin >> this->x_ord[i];
        cout << "Please enter y-ordiante of pt." << i + 1 << " : ";
        cin >> this->y_ord[i];
        if (i == 0)
        {
            this->x_min = this->x_ord[i];
            this->y_min = this->y_ord[i];
        }
        if (this->x_ord[i] < x_min)
            this->x_min = this->x_ord[i];
        if (this->y_ord[i] < y_min)
            this->y_min = this->y_ord[i];
        if (this->x_ord[i] > x_max)
            this->x_max = this->x_ord[i];
        if (this->y_ord[i] > y_max)
            this->y_max = this->y_ord[i];
    }
}
string Cross::toString()
{
    string stype = (this->containsWarpSpace) ? "WS" : "NS";
    ostringstream os;
    os << "Shape [" << this->id << "]\n"
       << "Name  : " << this->name << endl
       << "Special Type : " << stype << endl
       << "Area : " << area << " units square" << endl
       << "Vectices : \n";
    for (int i = 0; i < 12; i++)
    {
        os << "Point [" << i << "] : (" << x_ord[i] << ", " << y_ord[i] << ")\n";
    }
    os << "\n\nPoints on Perimeter : ";
    int iPoS_count = 0;
    for (int i = x_min; i <= x_max; i++)
    {
        for (int j = y_min; j <= y_max; j++)
        {
            if (isPointOnShape(i, j))
            {
                os << "(" << i << ", " << j << "), ";
                iPoS_count++;
            }
        }
    }
    if (iPoS_count == 0)
        os << "None!";
    else
        os << "\b\b"
           << "  ";
    int iPiS_count = 0;
    os << "\n\nPoints within shape : ";
    for (int i = x_min + 1; i < x_max; i++)
    {
        for (int j = y_min + 1; j < y_max; j++)
        {
            if (isPointInShape(i, j) && !isPointOnShape(i, j) && !isPointaVertex(i, j))
            {
                os << "(" << i << ", " << j << "), ";
                iPiS_count++;
            }
        }
    }
    if (iPiS_count == 0)
        os << "None!";
    else
        os << "\b\b"
           << "  ";

    return os.str();
}
double Cross::computeArea()
{
    double ar = 0; // Accumulates area
    int j = 11;

    for (int i = 0; i < 12; i++)
    {
        ar += (x_ord[j] + x_ord[i]) * (y_ord[j] - y_ord[i]);
        j = i; //j is previous vertex to i
    }
    ar = ar / 2;
    ar = abs(ar);
    return ar;
}
bool Cross::isPointOnShape(int x, int y)
{

    for (int i = 0; i < 11; i++)
    {
        //if x is between point x1 and x2 and y == y1 and y == y2
        int ux = max(x_ord[i], x_ord[i + 1]);
        int lx = min(x_ord[i], x_ord[i + 1]);
        int ly = min(y_ord[i], y_ord[i + 1]);
        int uy = max(y_ord[i], y_ord[i + 1]);
        if (ux == lx && x == ux && y > ly && y < uy)
        {
            return true;
        }
        if (uy == ly && y == uy && x > lx && x < ux)
        {
            return true;
        }
    }
    int ux = max(x_ord[11], x_ord[0]);
    int lx = min(x_ord[11], x_ord[0]);
    int ly = min(y_ord[11], y_ord[0]);
    int uy = max(y_ord[11], y_ord[0]);
    if (ux == lx && x == ux && y > ly && y < uy)
    {
        return true;
    }
    if (uy == ly && y == uy && x > lx && x < ux)
    {
        return true;
    }
    return false;
}
bool Cross::isPointInShape(int x, int y)
{
    bool flag;
    flag = pnpoly(12, this->x_ord, this->y_ord, x, y);

    return flag;
}
int Cross::pnpoly(int nvert, int *vertx, int *verty, int testx, int testy)
{
    int i, j, c = 0;
    for (i = 0, j = nvert - 1; i < nvert; j = i++)
    {
        if (((verty[i] > testy) != (verty[j] > testy)) &&
            (testx < (vertx[j] - vertx[i]) * (testy - verty[i]) / (verty[j] - verty[i]) + vertx[i]))
            c = !c;
    }
    return c;
}
bool Cross::isPointaVertex(int x, int y)
{
    for (int i = 0; i < 12; i++)
    {
        if (x == x_ord[i] && y == y_ord[i])
            return true;
    }
    return false;
}
double Cross::get_area()
{
    return this->area;
}



