
#include "Cross.h"

using namespace std;

Cross::Cross(string name, bool containsWarpSpace, int id) //Cross constructor
{
    this->name = name;
    this->containsWarpSpace = containsWarpSpace;
    this->id = id;
    this->set_ords(); //gets the 12 vertices of the cross and stores in the array of attributes
}
void Cross::set_area() //area setter
{
    this->area = computeArea(); //runs a unique area function for cross
}
void Cross::set_ords() //gets the 12 points of the cross and get the min and max of x y
{
    for (int i = 0; i < 12; i++) //12 times loop
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

    bool isCord = false;
    string stype = (this->containsWarpSpace) ? "WS" : "NS";
    string output;
    output += "Shape [" + to_string(this->id) + "]\n";
    output += "Name  : " + this->name + "\n" + "Special Type : " + stype + "\n";
    output += "Area : " + to_string(this->area) + " units square" + "\n" + "Vectices : \n";
    for (int i = 0; i < 12; i++)
    {
        output += "Point [" + to_string(i) + "] : (" + to_string(x_ord[i]) + ", " + to_string(y_ord[i]) + ")\n";
    }
    output += "\n\nPoints on Perimeter : ";
    int iPoS_count = 0;
    for (int i = x_min; i <= x_max; i++)
    {
        for (int j = y_min; j <= y_max; j++)
        {
            if (isPointOnShape(i, j))
            {
                output += "(" + to_string(i) + ", " + to_string(j) + "), ";
                iPoS_count++;
            }
        }
    }
    if (iPoS_count == 0)
        output += "None!";
    else
        output += "\b\b  ";

    int iPiS_count = 0;
    output += "\n\nPoints within shape : ";
    for (int i = x_min + 1; i < x_max; i++)
    {
        for (int j = y_min + 1; j < y_max; j++)
        {
            if (isPointInShape(i, j) && !isPointOnShape(i, j) && !isPointaVertex(i, j))
            {
                output += "(" + to_string(i) + ", " + to_string(j) + "), ";
                iPiS_count++;
            }
        }
    }
    if (iPiS_count == 0)
        output += "None!";
    else
        output += "\b\b  ";

    return output;
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
bool Cross::isPointOnShape(int x, int y) //returns true if function is ON shape
{

    for (int i = 0; i < 11; i++) //for each x and y vertices
    {

        int ux = max(x_ord[i], x_ord[i + 1]);        //find the largest x between adjacent points
        int lx = min(x_ord[i], x_ord[i + 1]);        //find the smallest x between adjacent points
        int ly = min(y_ord[i], y_ord[i + 1]);        //find the largest y between adjacent poitns
        int uy = max(y_ord[i], y_ord[i + 1]);        //find the smallest y between adjacent points
        if (ux == lx && x == ux && y > ly && y < uy) //if max x and min x is the same plane as test x and y is within the bounds of adjacent y, return true
        {
            return true;
        }
        if (uy == ly && y == uy && x > lx && x < ux) //if max y and min y is the same plane as test y and x is within the bouds of adjacent x, return true
        {
            return true;
        }
    }
    //this block is for the final edge case of the last point "linking" with the first point
    int ux = max(x_ord[11], x_ord[0]);
    int lx = min(x_ord[11], x_ord[0]);
    int ly = min(y_ord[11], y_ord[0]);
    int uy = max(y_ord[11], y_ord[0]);
    if (ux == lx && x == ux && y > ly && y < uy) //if max x and min x is the same plane as test x and y is within the bounds of adjacent y, return true
    {
        return true;
    }
    if (uy == ly && y == uy && x > lx && x < ux) //if max y and min y is the same plane as test y and x is within the bouds of adjacent x, return true
    {
        return true;
    }
    return false;
}
bool Cross::isPointInShape(int x, int y) //returns true if pnpoly func returns 1 and false for 0
{
    bool flag;
    flag = pnpoly(12, this->x_ord, this->y_ord, x, y);

    return flag;
}
int Cross::pnpoly(int nvert, int *vertx, int *verty, int testx, int testy) //this function will return true if point is in polygon
{
    int i, j, c = 0;
    for (i = 0, j = nvert - 1; i < nvert; j = i++) //this is a ray casting algorithm where it takes an x and y point and extend the x infinitly in a line, if the line cross any of the lines in the shape odd number of time the point is within the shape
    {
        if (((verty[i] > testy) != (verty[j] > testy)) &&
            (testx < (vertx[j] - vertx[i]) * (testy - verty[i]) / (verty[j] - verty[i]) + vertx[i]))
            c = !c; //this flag toggles every time a match is hit
    }
    return c; //c will either be 1 or 0 hence its acceptable for boolean usage
}
bool Cross::isPointaVertex(int x, int y) //function that check if point is a vertex by checking the attribute array
{
    for (int i = 0; i < 12; i++)
    {
        if (x == x_ord[i] && y == y_ord[i])
            return true;
    }
    return false;
}
double Cross::get_area() //area getter for toString
{
    return this->area;
}
