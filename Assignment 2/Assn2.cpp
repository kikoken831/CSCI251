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
    ShapeTwoD(string name, bool containsWarpSpace, int id)
    {
        this->name = name;
        this->containsWarpSpace = containsWarpSpace;
        this->id = id;
    }

    void setName(string name)
    {
        this->name = name;
    }

    void setContainsWarpSpace(bool containsWarpSpace)
    {
        this->containsWarpSpace = containsWarpSpace;
    }
    string getName()
    {
        return name;
    }
    bool getContainsWarpSpace()
    {
        return containsWarpSpace;
    }

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
    void set_area()
    {
        this->area = computeArea();
    }
    Square(string name, bool containsWarpSpace, int id)
    {
        this->name = name;
        this->containsWarpSpace = containsWarpSpace;
        this->id = id;
    }
    void set_ords()
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
    string toString()
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
    double computeArea()
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
    bool isPointInShape(int x, int y)
    {
        if (x < this->x_max && x > this->x_min && y < this->y_max && y > this->y_min)
        {
            return true;
        }
        else
            return false;
    }
    bool isPointOnShape(int x, int y)
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
    double get_area()
    {
        return this->area;
    }
    bool operator>(const Square &str) const
    {
        return this->area > str.area;
    }
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
    void set_area()
    {
        this->area = computeArea();
    }
    Rectangle(string name, bool containsWarpSpace, int id)
    {
        this->name = name;
        this->containsWarpSpace = containsWarpSpace;
        this->id = id;
    }
    void set_ords()
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
    string toString()
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
    bool isPointInShape(int x, int y)
    {
        if (x < this->x_max && x > this->x_min && y < this->y_max && y > this->y_min)
        {
            return true;
        }
        else
            return false;
    }
    bool isPointOnShape(int x, int y)
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
    double computeArea()
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
    double get_area()
    {
        return this->area;
    }
    bool operator>(const Rectangle &str) const
    {
        return this->area > str.area;
    }
};
class Circle : public ShapeTwoD
{
    int x_ord;
    int y_ord;
    int radius;
    double area;

public:
    Circle(string name, bool containsWarpSpace, int id)
    {
        this->name = name;
        this->containsWarpSpace = containsWarpSpace;
        this->id = id;
    }
    void set_area()
    {
        this->area = computeArea();
    }
    void set_ords()
    {

        cout << "Please enter x-ordiante of center : ";
        cin >> this->x_ord;
        cout << "Please enter y-ordiante of center : ";
        cin >> this->y_ord;
        cout << "Please enter radius(units) : ";
        cin >> this->radius;
    }
    string toString()
    {
        string stype = (this->containsWarpSpace) ? "WS" : "NS";
        ostringstream os;
        os << "Shape [" << this->id << "]\n";
        os << "Name  : " << this->name << endl
           << "Special Type : " << stype << endl
           << "Area : " << setprecision(2) << area << " units square" << endl
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
    bool isPointOnShape(int x, int y)
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
    bool isPointInShape(int x, int y)
    {
        if (pow((x - this->x_ord), 2) + pow((y - this->y_ord), 2) < this->radius * this->radius)
            return true;
        else
            return false;
    }
    double computeArea()
    {
        return M_PI * (this->radius * 2);
    }
    double get_area()
    {
        return this->area;
    }
    bool operator>(const Circle &str) const
    {
        return this->area > str.area;
    }
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
    Cross(string name, bool containsWarpSpace, int id)
    {
        this->name = name;
        this->containsWarpSpace = containsWarpSpace;
        this->id = id;
    }
    void set_area()
    {
        this->area = computeArea();
    }
    void set_ords()
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
    string toString()
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
    double computeArea()
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
    bool isPointOnShape(int x, int y)
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
    bool isPointInShape(int x, int y)
    {
        bool flag;
        flag = pnpoly(12, this->x_ord, this->y_ord, x, y);

        return flag;
    }
    int pnpoly(int nvert, int *vertx, int *verty, int testx, int testy)
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
    bool isPointaVertex(int x, int y)
    {
        for (int i = 0; i < 12; i++)
        {
            if (x == x_ord[i] && y == y_ord[i])
                return true;
        }
        return false;
    }
    double get_area()
    {
        return this->area;
    }
    bool operator>(const Cross &str) const
    {
        return this->area > str.area;
    }
};
void menu();
void PressEnterToContinue();
bool check_number(string str);
void read_shape();
void sort_menu();
void dsc_sort(vector<ShapeTwoD *> vec);
void spec_sort(vector<ShapeTwoD *> vec);
void asc_sort(vector<ShapeTwoD *> vec);
void spec_sort_d(vector<ShapeTwoD *> vec);
ShapeTwoD *shapeArray[100]; //global array for shape objects with a 100 shape limit
int global_count = 0;       //global counter for appending to the last item in array
int main()
{
    string choice;
    bool flag = true;
    int i;
    while (flag)
    {

        menu(); //prints the menu for the user
        cout << "Please enter your choice :";
        cin >> choice;
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        if (check_number(choice))
        {
            int ichoice = stoi(choice);
            switch (ichoice) //switch statement for executing different program functions based on user's choice
            {
            case 1:
                read_shape();
                break;
            case 2:
                double temp;
                for (int i = 0; i < global_count; i++)
                {
                    shapeArray[i]->set_area();
                }
                cout << "Computation completed! (" << global_count << " records were updated )" << endl;
                PressEnterToContinue();
                break;
            case 3:
                cout << "Total no. of records available = " << global_count << endl;
                for (int i = 0; i < global_count; i++)
                {
                    cout << shapeArray[i]->toString() << endl
                         << endl;
                    ;
                }
                PressEnterToContinue();
                break;
            case 4:
                sort_menu();
                PressEnterToContinue();
                break;
            case 5:
                cout << "Exiting Program" << endl;
                flag = false;
                break;

            default:
                cout << "Please key in a valid option" << endl
                     << endl;
                PressEnterToContinue();
            }
        }
        else
        {
            cout << "Please key in a int value" << endl
                 << endl;
            PressEnterToContinue();
        }
    }
    return 0;
}

void menu()
{
    cout << endl;
    cout << left << setw(13) << "Student ID";
    cout << ": 7366814" << endl;
    cout << left << setw(13) << "Student Name";
    cout << ": Kendrick Kee" << endl;
    cout << "-------------------------------------" << endl;
    cout << "Welcome to Assn2 program!" << endl;
    cout << endl;
    cout << "1)       Input sensor data" << endl;
    cout << "2)       Computer area (for all records)" << endl;
    cout << "3)       Print shapes report" << endl;
    cout << "4)       Sort shape data" << endl;
    cout << "5)       Quit" << endl;
    cout << endl;
}
//function that prompts user to key in ENTER to continue
void PressEnterToContinue()
{
    int c;
    printf("Press <enter> to go back to main menu... ");
    fflush(stdout);
    do
        c = getchar();
    while ((c != '\n') && (c != EOF));
}
bool check_number(string str) //simple checknumber function for input validation for the menu
{
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false;
    return true;
}
//function to read in user input and append the shape to the shape array
void read_shape()
{
    string shape_name;
    string spec_type;
    bool contain_warp;
    //prompt user for name of shape
    cout << "Please enter name of shape: ";
    cin >> shape_name;
    //prompt user for type
    cout << "Please enter special type: ";
    cin >> spec_type;
    contain_warp = (spec_type == "WS") ? true : (spec_type == "NS") ? false
                                                                    : false;

    //create new shape based on user input
    if (shape_name == "Square")
    {
        shapeArray[global_count] = new Square(shape_name, contain_warp, global_count);
        shapeArray[global_count]->set_ords();
        global_count++;
    }
    if (shape_name == "Circle")
    {

        shapeArray[global_count] = new Circle(shape_name, contain_warp, global_count);
        shapeArray[global_count]->set_ords();
        global_count++;
    }
    if (shape_name == "Cross")
    {
        shapeArray[global_count] = new Cross(shape_name, contain_warp, global_count);
        shapeArray[global_count]->set_ords();
        global_count++;
    }
    if (shape_name == "Rectangle")
    {
        shapeArray[global_count] = new Rectangle(shape_name, contain_warp, global_count);
        shapeArray[global_count]->set_ords();
        global_count++;
    }
    //run the shape child setter methods for getting the x,y ordinates
    //cout record stored successfully
    cout << "Record successfully stored. Going back to main menu....." << endl;
}
//print the sort menu
void sort_menu()
{
    vector<ShapeTwoD *> vec;
    for (int i = 0; i < global_count; i++)
    {
        vec.push_back(*(shapeArray + i));
    }
    char choice;
    cout << "    a)      Sort by area (ascending)" << endl;
    cout << "    b)      Sort by area (descending)" << endl;
    cout << "    c)      Sort by special type and area (ascending)\n";
    cout << "    d)      Sort by special type and area (descending)\n"
         << endl;
    cout << "Please select sort option ('q' to go main menu): ";

    cin >> choice;
    //switch statement for each sort type
    switch (choice)
    {
    case 'a':
        //asc sort
        asc_sort(vec);
        cout << endl;
        break;
    case 'b':
        dsc_sort(vec);
        cout << endl;
        //dsc sort
        break;
    case 'c':
        spec_sort(vec);
        cout << endl;
        //special sort asc
    case 'd':
        //special sort dsc
        spec_sort_d(vec);
        cout << endl;
    case 'q':
        cout << "Going back to main menu.\n\n";
        break;
    }
}
//ascending sort
void asc_sort(vector<ShapeTwoD *> vec)
{
    sort(vec.begin(), vec.end(), [](ShapeTwoD *lhs, ShapeTwoD *rhs) { //err squiggies
        return lhs->get_area() > rhs->get_area();
    });
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i]->toString() << endl;
    }
}
//descending sort
void dsc_sort(vector<ShapeTwoD *> vec)
{

    sort(vec.begin(), vec.end(), [](ShapeTwoD *lhs, ShapeTwoD *rhs) { //err squiggies
        return lhs->get_area() < rhs->get_area();
    });
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i]->toString() << endl;
    }
}
//special sort
void spec_sort(vector<ShapeTwoD *> vec)
{
    vector<ShapeTwoD *> vec_NS;
    vector<ShapeTwoD *> vec_WS;
    //get all NS type
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i]->getContainsWarpSpace() == false)
        {
            vec_NS.push_back(*(shapeArray + i));
        }
        else
        {
            vec_WS.push_back(*(shapeArray + i));
        }
    }
    asc_sort(vec_WS);
    asc_sort(vec_NS);
}
//special sort
void spec_sort_d(vector<ShapeTwoD *> vec)
{
    vector<ShapeTwoD *> vec_NS;
    vector<ShapeTwoD *> vec_WS;
    //get all NS type
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i]->getContainsWarpSpace() == false)
        {
            vec_NS.push_back(*(shapeArray + i));
        }
        else
        {
            vec_WS.push_back(*(shapeArray + i));
        }
    }
    dsc_sort(vec_WS);
    dsc_sort(vec_NS);
}
