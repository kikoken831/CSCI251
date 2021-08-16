
#include "Rectangle.h"
using namespace std;

Rectangle::Rectangle(string name, bool containsWarpSpace, int id) //rectange constructor
{
    this->name = name;
    this->containsWarpSpace = containsWarpSpace;
    this->id = id;
    this->set_ords(); //runs the set ordinates function to store the unique coordinates of rectangle shape
}
void Rectangle::set_area() //area setter that runs a unique function for calculating rectangle area
{
    this->area = computeArea();
}
void Rectangle::set_ords() //same as square set_ords gets the 4 vertices and gets min max of x and y
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
string Rectangle::toString() //returns string of all values required for rectangle
{

    bool isCord = false;
    string stype = (this->containsWarpSpace) ? "WS" : "NS";
    string output;
    output += "Shape [" + to_string(this->id) + "]\n";
    output += "Name  : " + this->name + "\n" + "Special Type : " + stype + "\n";
    output += "Area : " + to_string(this->area) + " units square" + "\n" + "Vectices : \n";

    for (int i = 0; i < 4; i++) //appennds all shapes vertex
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
            if (isPointOnShape(i, j) && !isCord) //if point is not a cord and point is on shape append the point
            {
                output += "(" + to_string(i) + ", " + to_string(j) + "), ";
                iPoS_count++;
            }
            isCord = false;
        }
    }
    if (iPoS_count == 0)
    {
        output += "None!"; //append none if not points were added
    }
    else
    {
        output += "\b\b  "; //delete trailing comma
    }

    if (this->area <= 4) //rectanges with <= 4 area cant have points with
        output += "\n\nPoints within shape : None!";
    else
    {
        output += "\n\nPoints within shape : ";
        for (int i = x_min; i <= x_max; i++)
        {
            for (int j = y_min; j <= y_max; j++)
            {
                if (isPointInShape(i, j)) //if point is in shape append cords
                {
                    output += "(" + to_string(i) + ", " + to_string(j) + "), ";
                }
            }
        }
        output += "\b\b  "; //remove trailing comma
    }

    return output;
}
bool Rectangle::isPointInShape(int x, int y)
{
    if (x < this->x_max && x > this->x_min && y < this->y_max && y > this->y_min) //if point is within the x y boundaries of rect cords return true
    {
        return true;
    }
    else
        return false;
}
bool Rectangle::isPointOnShape(int x, int y)
{
    if (x == this->x_min && y >= this->y_min && y <= this->y_max) //if point is on the x min axis and within the y min max boundary return true
        return true;
    else if (y == this->y_max && x >= this->x_min && x <= this->x_max) //if point is on the y max axis and within the x min max boundary return true
        return true;
    else if (x == this->x_max && y >= this->y_min && y <= this->y_max) //if point is on the x max axis and within the y min max boundary return tru
        return true;
    else if (y == this->y_min && x >= this->x_min && x <= this->x_max) //if point is on the y min axs and within the x min max boudnary return true
        return true;
    else
        return false;
}
double Rectangle::computeArea()
{
    double ar = 0; // Accumulates area
    int j = 3;

    for (int i = 0; i < 4; i++) // loops through each coordinate
    {
        ar += (x_ord[j] + x_ord[i]) * (y_ord[j] - y_ord[i]); //uses a previous vertex formula in geometry to calculate the area of polygon
        j = i;                                               //j is previous vertex to i
    }
    ar = ar / 2;
    ar = abs(ar); //abs is used as depending on the direction of the cordinates area could be a negative value
    return ar;
}
double Rectangle::get_area() //area getter
{
    return this->area;
}
