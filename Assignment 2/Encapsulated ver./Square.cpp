
#include "Square.h"

Square::Square(string name, bool containsWarpSpace, int id) //square constructor
{
    this->name = name;
    this->containsWarpSpace = containsWarpSpace;
    this->id = id;
    this->set_ords(); //calls the set ords function for unique cordinate prompts and storage.
}
void Square::set_area() //area setter
{
    this->area = computeArea(); //calls the compute area function only unique to this object
}
void Square::set_ords() //ordinates setter
{
    for (int i = 0; i < 4; i++) //loops 4 times to get the 4 points
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
string Square::toString() //to string function that gets all the desired values and returns it as a string
{
    bool isCord = false;
    string stype = (this->containsWarpSpace) ? "WS" : "NS";
    string output;
    output += "Shape [" + to_string(this->id) + "]\n";
    output += "Name  : " + this->name + "\n" + "Special Type : " + stype + "\n";
    output += "Area : " + to_string(this->area) + " units square" + "\n" + "Vectices : \n";

    for (int i = 0; i < 4; i++) //gets the 4 vertex of the squaree
    {
        output += "Point [" + to_string(i) + "] : (" + to_string(x_ord[i]) + ", " + to_string(y_ord[i]) + ")\n";
    }
    int iPoS_count = 0;
    output += "Points on Perimeter : ";
    for (int i = x_min; i <= x_max; i++) //nest for loops to get the maximium surroundings
    {
        for (int j = y_min; j <= y_max; j++)
        {
            for (int k = 0; k < 4; k++) //mini loop to check if point is a coordinate as it does not need to be printed
            {
                if (x_ord[k] == i && y_ord[k] == j)
                    isCord = true;
            }
            if (isPointOnShape(i, j) && !isCord) //if PointOnShape is valid and point is also not a cord append the cordinate to the string
            {
                output += "(" + to_string(i) + ", " + to_string(j) + "), ";
                iPoS_count++; //count of numbers of points printed
            }
            isCord = false; //turn flag off
        }
    }
    if (iPoS_count == 0) //if not cords are printed
    {
        output += "None!"; //print none
    }
    else //else delete the traling comma
    {
        output += "\b\b  ";
    }

    if (this->area < 4) //square that have an area thats lesser than 4 are guarenteed to not have points within shape
        output += "\n\nPoints within shape : None!";
    else
    {
        output += "\n\nPoints within shape : ";
        for (int i = x_min; i <= x_max; i++) //nested loops to find all points within shape
        {
            for (int j = y_min; j <= y_max; j++)
            {
                if (isPointInShape(i, j)) //if PointInShape function is true print coordinates
                {
                    output += "(" + to_string(i) + ", " + to_string(j) + "), ";
                }
            }
        }
        output += "\b\b  ";
    }

    return output;
}
double Square::computeArea() //computes the area of a square using its 4 points
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
bool Square::isPointInShape(int x, int y) //returns true of point is in shape
{
    if (x < this->x_max && x > this->x_min && y < this->y_max && y > this->y_min) //if point is within the min max of x and y, point is in shape
    {
        return true;
    }
    else
        return false;
}
bool Square::isPointOnShape(int x, int y) //returns true if point is on shape
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
double Square::get_area() //area getter for toString
{
    return this->area;
}