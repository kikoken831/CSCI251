
#include "Circle.h"

Circle::Circle(string name, bool containsWarpSpace, int id) //circle constructor
{
    this->name = name;
    this->containsWarpSpace = containsWarpSpace;
    this->id = id;
    this->set_ords(); //runs the set_ords function to store user input thats unique to circles
}
void Circle::set_area() //area setter that runs the computer area function that unique for circles
{
    this->area = computeArea();
}
void Circle::set_ords() //gets the centre and radius of circle via user input
{

    cout << "Please enter x-ordiante of center : ";
    cin >> this->x_ord;
    cout << "Please enter y-ordiante of center : ";
    cin >> this->y_ord;
    cout << "Please enter radius(units) : ";
    cin >> this->radius;
}
string Circle::toString() //circle tostring that returns a string of key values
{

    string stype = (this->containsWarpSpace) ? "WS" : "NS";
    string output;
    stringstream stream;

    output += "Shape [" + to_string(this->id) + "]\n";
    output += "Name  : " + this->name + "\n" + "Special Type : " + stype + "\n";
    stream << fixed << setprecision(2) << this->area; //rounds area to 2 decimal places
    output += "Area : " + stream.str() + " units square" + "\n" + "Vectices : \n";
    output += "Point [0] : (" + to_string(this->x_ord) + ", " + to_string(this->y_ord) + ")\n";

    output += "Points on Perimeter : ";
    for (int i = x_ord - radius; i <= x_ord + radius; i++) //nested loops for all x and y boundaries
    {
        for (int j = y_ord - radius; j <= y_ord + radius; j++)
        {
            if (isPointOnShape(i, j)) //if point is on shape append point
            {
                output += "(" + to_string(i) + ", " + to_string(j) + "), ";
            }
        }
    }
    output += "\b\b  ";
    if (this->radius == 1) //circle with 1 radius will only have its center hence nothing will need to be printed
        output += "\n\nPoints within shape : None!";
    else
    {
        output += "\n\nPoints within shape : ";
        for (int i = x_ord - radius; i < x_ord + radius; i++) //nested loop for the boundaries
        {
            for (int j = y_ord - radius; j < y_ord + radius; j++)
            {
                if (i == x_ord && j == y_ord) //if point is center ignore
                {
                    continue;
                }
                if (isPointInShape(i, j)) //if point is in shape append cords
                {
                    output += "(" + to_string(i) + ", " + to_string(j) + "), ";
                }
            }
        }
        output += "\b\b  ";
    }

    return output;
}
bool Circle::isPointOnShape(int x, int y) //returns true if point is N S E W  plus the raduis of the centre
{
    if (x == x_ord && y == y_ord + radius) //is point north?
        return true;
    else if (x == x_ord + radius && y == y_ord) //east?
        return true;
    else if (x == x_ord && y == y_ord - radius) //south?
        return true;
    else if (x == x_ord - radius && y == y_ord) //west?
        return true;
    else
        return false;
}
bool Circle::isPointInShape(int x, int y) //returns true if point is in shape
{
    if (pow((x - this->x_ord), 2) + pow((y - this->y_ord), 2) < this->radius * this->radius) //using this formula from geometry, it returns true is point is in shape
        return true;
    else
        return false;
}
double Circle::computeArea() //computes area of circle
{
    return M_PI * (this->radius * this->radius); //Pi R squared
}
double Circle::get_area() //area getter for toString
{
    return this->area;
}