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

void ShapeTwoD::setName(string name)//name setter
{
    this->name = name;
}

void ShapeTwoD::setContainsWarpSpace(bool containsWarpSpace)//WS setter
{
    this->containsWarpSpace = containsWarpSpace;
}

string ShapeTwoD::getName()//name getter
{
    return name;
}
bool ShapeTwoD::getContainsWarpSpace()//WS getter
{
    return containsWarpSpace;
}
//getters are used in toStrings for all child objects

Square::Square(string name, bool containsWarpSpace, int id)//square constructor
{
    this->name = name;
    this->containsWarpSpace = containsWarpSpace;
    this->id = id;
    this->set_ords();//calls the set ords function for unique cordinate prompts and storage.
}
void Square::set_area()//area setter
{
    this->area = computeArea();//calls the compute area function only unique to this object
}
void Square::set_ords()//ordinates setter
{
    for (int i = 0; i < 4; i++)//loops 4 times to get the 4 points
    {
        cout << "Please enter x-ordiante of pt." << i + 1 << " : ";
        cin >> this->x_ord[i];
        cout << "Please enter y-ordiante of pt." << i + 1 << " : ";
        cin >> this->y_ord[i];
        //this block below gets the min max values of x and y to be used for PointIn and PointOn function
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
string Square::toString()//to string function that gets all the desired values and returns it as a string
{
    bool isCord = false;
    string stype = (this->containsWarpSpace) ? "WS" : "NS";
    string output;
    output += "Shape [" + to_string(this->id) + "]\n";
    output += "Name  : " + this->name + "\n" + "Special Type : " + stype + "\n";
    output += "Area : " + to_string(this->area) + " units square" + "\n" + "Vectices : \n";

    for (int i = 0; i < 4; i++)//gets the 4 vertex of the squaree
    {
        output += "Point [" + to_string(i) + "] : (" + to_string(x_ord[i]) + ", " + to_string(y_ord[i]) + ")\n";
    }
    int iPoS_count = 0;
    output += "Points on Perimeter : ";
    for (int i = x_min; i <= x_max; i++)//nest for loops to get the maximium surroundings 
    {
        for (int j = y_min; j <= y_max; j++)
        {
            for (int k = 0; k < 4; k++)//mini loop to check if point is a coordinate as it does not need to be printed
            {
                if (x_ord[k] == i && y_ord[k] == j)
                    isCord = true;
            }
            if (isPointOnShape(i, j) && !isCord)//if PointOnShape is valid and point is also not a cord append the cordinate to the string
            {
                output += "(" + to_string(i) + ", " + to_string(j) + "), ";
                iPoS_count++;//count of numbers of points printed
            }
            isCord = false;//turn flag off
        }
    }
    if (iPoS_count == 0)//if not cords are printed
    {
        output += "None!";//print none
    }
    else//else delete the traling comma
    {
        output += "\b\b  ";
    }

    if (this->area < 4)//square that have an area thats lesser than 4 are guarenteed to not have points within shape
        output += "\n\nPoints within shape : None!";
    else
    {
        output += "\n\nPoints within shape : ";
        for (int i = x_min; i <= x_max; i++)//nested loops to find all points within shape
        {
            for (int j = y_min; j <= y_max; j++)
            {
                if (isPointInShape(i, j))//if PointInShape function is true print coordinates
                {
                    output += "(" + to_string(i) + ", " + to_string(j) + "), ";
                }
            }
        }
        output += "\b\b  ";
    }

    return output;
}
double Square::computeArea()//computes the area of a square using its 4 points
{
    double ar = 0; // Accumulates area
    int j = 3;

    for (int i = 0; i < 4; i++)// loops through each coordinate
    {
        ar += (x_ord[j] + x_ord[i]) * (y_ord[j] - y_ord[i]);//uses a previous vertex formula in geometry to calculate the area of polygon
        j = i; //j is previous vertex to i
    }
    ar = ar / 2;
    ar = abs(ar);//abs is used as depending on the direction of the cordinates area could be a negative value
    return ar;
}
bool Square::isPointInShape(int x, int y)//returns true of point is in shape
{
    if (x < this->x_max && x > this->x_min && y < this->y_max && y > this->y_min)//if point is within the min max of x and y, point is in shape
    {
        return true;
    }
    else
        return false;
}
bool Square::isPointOnShape(int x, int y)//returns true if point is on shape
{
    if (x == this->x_min && y >= this->y_min && y <= this->y_max)//if point is on the x min axis and within the y min max boundary return true
        return true;
    else if (y == this->y_max && x >= this->x_min && x <= this->x_max)//if point is on the y max axis and within the x min max boundary return true
        return true;
    else if (x == this->x_max && y >= this->y_min && y <= this->y_max)//if point is on the x max axis and within the y min max boundary return tru
        return true;
    else if (y == this->y_min && x >= this->x_min && x <= this->x_max)//if point is on the y min axs and within the x min max boudnary return true
        return true;
    else
        return false;
}
double Square::get_area()//area getter for toString
{
    return this->area;
}

Rectangle::Rectangle(string name, bool containsWarpSpace, int id)//rectange constructor
{
    this->name = name;
    this->containsWarpSpace = containsWarpSpace;
    this->id = id;
    this->set_ords();//runs the set ordinates function to store the unique coordinates of rectangle shape

}
void Rectangle::set_area()//area setter that runs a unique function for calculating rectangle area
{
    this->area = computeArea();
}
void Rectangle::set_ords()//same as square set_ords gets the 4 vertices and gets min max of x and y
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
string Rectangle::toString()//returns string of all values required for rectangle
{

    bool isCord = false;
    string stype = (this->containsWarpSpace) ? "WS" : "NS";
    string output;
    output += "Shape [" + to_string(this->id) + "]\n";
    output += "Name  : " + this->name + "\n" + "Special Type : " + stype + "\n";
    output += "Area : " + to_string(this->area) + " units square" + "\n" + "Vectices : \n";

    for (int i = 0; i < 4; i++)//appennds all shapes vertex
    {
        output += "Point [" + to_string(i) + "] : (" + to_string(x_ord[i]) + ", " + to_string(y_ord[i]) + ")\n";
    }
    int iPoS_count = 0;
    output += "Points on Perimeter : ";
    for (int i = x_min; i <= x_max; i++)
    {
        for (int j = y_min; j <= y_max; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                if (x_ord[k] == i && y_ord[k] == j)
                    isCord = true;
            }
            if (isPointOnShape(i, j) && !isCord)//if point is not a cord and point is on shape append the point
            {
                output += "(" + to_string(i) + ", " + to_string(j) + "), ";
                iPoS_count++;
            }
            isCord = false;
        }
    }
    if (iPoS_count == 0)
    {
        output += "None!";//append none if not points were added
    }
    else
    {
        output += "\b\b  ";//delete trailing comma
    }

    if (this->area <= 4)//rectanges with <= 4 area cant have points with
        output += "\n\nPoints within shape : None!";
    else
    {
        output += "\n\nPoints within shape : ";
        for (int i = x_min; i <= x_max; i++)
        {
            for (int j = y_min; j <= y_max; j++)
            {
                if (isPointInShape(i, j))//if point is in shape append cords
                {
                    output += "(" + to_string(i) + ", " + to_string(j) + "), ";
                }
            }
        }
        output += "\b\b  ";//remove trailing comma
    }

    return output;
}
bool Rectangle::isPointInShape(int x, int y)
{
    if (x < this->x_max && x > this->x_min && y < this->y_max && y > this->y_min)//if point is within the x y boundaries of rect cords return true
    {
        return true;
    }
    else
        return false;
}
bool Rectangle::isPointOnShape(int x, int y)
{
    if (x == this->x_min && y >= this->y_min && y <= this->y_max)//if point is on the x min axis and within the y min max boundary return true
        return true;
    else if (y == this->y_max && x >= this->x_min && x <= this->x_max)//if point is on the y max axis and within the x min max boundary return true
        return true;
    else if (x == this->x_max && y >= this->y_min && y <= this->y_max)//if point is on the x max axis and within the y min max boundary return tru
        return true;
    else if (y == this->y_min && x >= this->x_min && x <= this->x_max)//if point is on the y min axs and within the x min max boudnary return true
        return true;
    else
        return false;
}
double Rectangle::computeArea()
{
    double ar = 0; // Accumulates area
    int j = 3;

    for (int i = 0; i < 4; i++)// loops through each coordinate
    {
        ar += (x_ord[j] + x_ord[i]) * (y_ord[j] - y_ord[i]);//uses a previous vertex formula in geometry to calculate the area of polygon
        j = i; //j is previous vertex to i
    }
    ar = ar / 2;
    ar = abs(ar);//abs is used as depending on the direction of the cordinates area could be a negative value
    return ar;
}
double Rectangle::get_area()//area getter
{
    return this->area;
}

Circle::Circle(string name, bool containsWarpSpace, int id)//circle constructor
{
    this->name = name;
    this->containsWarpSpace = containsWarpSpace;
    this->id = id;
    this->set_ords();//runs the set_ords function to store user input thats unique to circles

    
}
void Circle::set_area()//area setter that runs the computer area function that unique for circles
{
    this->area = computeArea();
}
void Circle::set_ords()//gets the centre and radius of circle via user input
{

    cout << "Please enter x-ordiante of center : ";
    cin >> this->x_ord;
    cout << "Please enter y-ordiante of center : ";
    cin >> this->y_ord;
    cout << "Please enter radius(units) : ";
    cin >> this->radius;
}
string Circle::toString()//circle tostring that returns a string of key values
{

    string stype = (this->containsWarpSpace) ? "WS" : "NS";
    string output;
    stringstream stream;
    
    output += "Shape [" + to_string(this->id) + "]\n";
    output += "Name  : " + this->name + "\n" + "Special Type : " + stype + "\n";
    stream << fixed << setprecision(2) << this->area;//rounds area to 2 decimal places
    output += "Area : " + stream.str() + " units square" + "\n" + "Vectices : \n";
    output +=  "Point [0] : (" + to_string(this->x_ord) + ", " + to_string(this->y_ord) + ")\n";
  
    output +=  "Points on Perimeter : ";
    for (int i = x_ord - radius; i <= x_ord + radius; i++)//nested loops for all x and y boundaries
    {
        for (int j = y_ord - radius; j <= y_ord + radius; j++)
        {
            if (isPointOnShape(i, j))//if point is on shape append point
            {
                output += "(" + to_string(i) + ", " + to_string(j) + "), ";
            }
        }
    }
    output += "\b\b  ";
    if (this->radius == 1)//circle with 1 radius will only have its center hence nothing will need to be printed
        output += "\n\nPoints within shape : None!";
    else
    {
        output += "\n\nPoints within shape : ";
        for (int i = x_ord - radius; i < x_ord + radius; i++)//nested loop for the boundaries
        {
            for (int j = y_ord - radius; j < y_ord + radius; j++)
            {
                if (i == x_ord && j == y_ord)//if point is center ignore
                {
                    continue;
                }
                if (isPointInShape(i, j))//if point is in shape append cords
                {
                    output += "(" + to_string(i) + ", " + to_string(j) + "), ";
                }
            }
        }
        output += "\b\b  ";
    }
    
    return output;
}
bool Circle::isPointOnShape(int x, int y)//returns true if point is N S E W  plus the raduis of the centre
{
    if (x == x_ord && y == y_ord + radius)//is point north?
        return true;
    else if (x == x_ord + radius && y == y_ord)//east?
        return true;
    else if (x == x_ord && y == y_ord - radius)//south?
        return true;
    else if (x == x_ord - radius && y == y_ord)//west?
        return true;
    else
        return false;
}
bool Circle::isPointInShape(int x, int y)//returns true if point is in shape
{
    if (pow((x - this->x_ord), 2) + pow((y - this->y_ord), 2) < this->radius * this->radius)//using this formula from geometry, it returns true is point is in shape
        return true;
    else
        return false;
}
double Circle::computeArea()//computes area of circle
{
    return M_PI * (this->radius * this->radius);//Pi R squared
}
double Circle::get_area()//area getter for toString
{
    return this->area;
}

Cross::Cross(string name, bool containsWarpSpace, int id)//Cross constructor
{
    this->name = name;
    this->containsWarpSpace = containsWarpSpace;
    this->id = id;
    this->set_ords();//gets the 12 vertices of the cross and stores in the array of attributes

}
void Cross::set_area()//area setter
{
    this->area = computeArea();//runs a unique area function for cross
}
void Cross::set_ords()//gets the 12 points of the cross and get the min and max of x y
{
    for (int i = 0; i < 12; i++)//12 times loop
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
        output +=  "None!";
    else
        output += "\b\b  ";
    
    int iPiS_count = 0;
    output +=  "\n\nPoints within shape : ";
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
        output +=  "None!";
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
bool Cross::isPointOnShape(int x, int y)//returns true if function is ON shape
{

    for (int i = 0; i < 11; i++)//for each x and y vertices
    {
        
        int ux = max(x_ord[i], x_ord[i + 1]);//find the largest x between adjacent points 
        int lx = min(x_ord[i], x_ord[i + 1]);//find the smallest x between adjacent points 
        int ly = min(y_ord[i], y_ord[i + 1]);//find the largest y between adjacent poitns
        int uy = max(y_ord[i], y_ord[i + 1]);//find the smallest y between adjacent points
        if (ux == lx && x == ux && y > ly && y < uy)//if max x and min x is the same plane as test x and y is within the bounds of adjacent y, return true
        {
            return true;
        }
        if (uy == ly && y == uy && x > lx && x < ux)//if max y and min y is the same plane as test y and x is within the bouds of adjacent x, return true
        {
            return true;
        }
    }
    //this block is for the final edge case of the last point "linking" with the first point
    int ux = max(x_ord[11], x_ord[0]);
    int lx = min(x_ord[11], x_ord[0]);
    int ly = min(y_ord[11], y_ord[0]);
    int uy = max(y_ord[11], y_ord[0]);
    if (ux == lx && x == ux && y > ly && y < uy)//if max x and min x is the same plane as test x and y is within the bounds of adjacent y, return true
    {
        return true;
    }
    if (uy == ly && y == uy && x > lx && x < ux)//if max y and min y is the same plane as test y and x is within the bouds of adjacent x, return true
    {
        return true;
    }
    return false;
}
bool Cross::isPointInShape(int x, int y)//returns true if pnpoly func returns 1 and false for 0
{
    bool flag;
    flag = pnpoly(12, this->x_ord, this->y_ord, x, y);

    return flag;
}
int Cross::pnpoly(int nvert, int *vertx, int *verty, int testx, int testy)//this function will return true if point is in polygon
{
    int i, j, c = 0;
    for (i = 0, j = nvert - 1; i < nvert; j = i++)//this is a ray casting algorithm where it takes an x and y point and extend the x infinitly in a line, if the line cross any of the lines in the shape odd number of time the point is within the shape
    {
        if (((verty[i] > testy) != (verty[j] > testy)) &&
            (testx < (vertx[j] - vertx[i]) * (testy - verty[i]) / (verty[j] - verty[i]) + vertx[i]))
            c = !c;//this flag toggles every time a match is hit
    }
    return c;//c will either be 1 or 0 hence its acceptable for boolean usage
}
bool Cross::isPointaVertex(int x, int y)//function that check if point is a vertex by checking the attribute array
{
    for (int i = 0; i < 12; i++)
    {
        if (x == x_ord[i] && y == y_ord[i])
            return true;
    }
    return false;
}
double Cross::get_area()//area getter for toString
{
    return this->area;
}
