#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <cmath>

#define M_PI 3.14159265358979323846
using namespace std;

void menu();
void PressEnterToContinue();
bool check_number(string str);
void read_shape();
void sort_menu();
void asc_sort();
void dsc_sort();
void spec_sort();
class ShapeTwoD
{
protected:
    string name;
    bool containsWarpSpace;

public:
    ShapeTwoD()
    {
        name = "N/A";
        containsWarpSpace = false;
    }
    ShapeTwoD(string name, bool containsWarpSpace)
    {
        this->name = name;
        this->containsWarpSpace = containsWarpSpace;
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
    virtual string toString()
    {
        return "";
    }

    virtual double computeArea()
    {
        return 0;
    }
    virtual bool isPointInShape(int x, int y)
    {
        return true;
    }
    virtual bool isPointOnShape(int x, int y)
    {
        return true;
    }
    virtual void set_ords()
    {
        return;
    }
    virtual void set_area()
    {
        return;
    }
};

class Square : public ShapeTwoD
{
private:
    int x_ord[4];
    int y_ord[4];
    double area;

public:
    void set_area()
    {
        cout << "sq compute area" << endl;
        this->area = computeArea();
    }
    Square(string name, bool containsWarpSpace)
    {
        this->name = name;
        this->containsWarpSpace = containsWarpSpace;
    }
    void set_ords()
    {
        for (int i = 0; i < 4; i++)
        {
            cout << "Please enter x-ordiante of pt." << i + 1 << " : ";
            cin >> this->x_ord[i];
            cout << "Please enter y-ordiante of pt." << i + 1 << " : ";
            cin >> this->y_ord[i];
        }
    }
    string toString()
    {
        string stype = (this->containsWarpSpace) ? "WS" : "NS";
        ostringstream os;
        os << "Name  : " << this->name << endl
           << "Special Type : " << stype << endl
           << "Area : " << this->area << " units square" << endl
           << "Vectices : \n";
        for (int i = 0; i < 4; i++)
        {
            os << "Point [" << i << "] : (" << x_ord[i] << ", " << y_ord[i] << ")\n";
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
};

class Rectangle : public ShapeTwoD
{
private:
    int x_ord[4];
    int y_ord[4];
    double area;

public:
    void set_area()
    {
        this->area = computeArea();
    }
    Rectangle(string name, bool containsWarpSpace)
    {
        this->name = name;
        this->containsWarpSpace = containsWarpSpace;
    }
    void set_ords()
    {
        for (int i = 0; i < 4; i++)
        {
            cout << "Please enter x-ordiante of pt." << i + 1 << " : ";
            cin >> this->x_ord[i];
            cout << "Please enter y-ordiante of pt." << i + 1 << " : ";
            cin >> this->y_ord[i];
        }
    }
    string toString()
    {
        string stype = (this->containsWarpSpace) ? "WS" : "NS";
        ostringstream os;
        os << "Name  : " << this->name << endl
           << "Special Type : " << stype << endl
           << "Area : " << area << " units square" << endl
           << "Vectices : \n";
        for (int i = 0; i < 4; i++)
        {
            os << "Point [" << i << "] : (" << x_ord[i] << ", " << y_ord[i] << ")\n";
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
};
class Circle : public ShapeTwoD
{
    int x_ord;
    int y_ord;
    int radius;
    double area;

public:
    Circle(string name, bool containsWarpSpace)
    {
        this->name = name;
        this->containsWarpSpace = containsWarpSpace;
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
        os << "Name  : " << this->name << endl
           << "Special Type : " << stype << endl
           << "Area : " << area << " units square" << endl
           << "Vectices : \n"
           << "Point [0] : (" << this->x_ord << ", " << this->y_ord << ")\n";

        return os.str();
    }
    double computeArea()
    {

        return M_PI * (this->radius * 2);
    }
};
class Cross : public ShapeTwoD
{
    int x_ord[12];
    int y_ord[12];
    double area;

public:
    Cross(string name, bool containsWarpSpace)
    {
        this->name = name;
        this->containsWarpSpace = containsWarpSpace;
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
        }
    }
    string toString()
    {
        string stype = (this->containsWarpSpace) ? "WS" : "NS";
        ostringstream os;
        os << "Name  : " << this->name << endl
           << "Special Type : " << stype << endl
           << "Area : " << area << " units square" << endl
           << "Vectices : \n";
        for (int i = 0; i < 12; i++)
        {
            os << "Point [" << i << "] : (" << x_ord[i] << ", " << y_ord[i] << ")\n";
        }
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
};
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
        cout << "Please enter your choice :" << endl;
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
                cout<<"Total no. of records available = "<<global_count<<endl;
                for (int i = 0; i < global_count; i++)
                {
                    cout << "Shape [" << i << "]" << endl;
                    cout << shapeArray[i]->toString() << endl;
                }
                PressEnterToContinue();
                break;
            case 4:

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
        shapeArray[global_count] = new Square(shape_name, contain_warp);
        shapeArray[global_count]->set_ords();
        global_count++;
    }
    if (shape_name == "Circle")
    {

        shapeArray[global_count] = new Circle(shape_name, contain_warp);
        shapeArray[global_count]->set_ords();
        global_count++;
    }
    if (shape_name == "Cross")
    {
        shapeArray[global_count] = new Cross(shape_name, contain_warp);
        shapeArray[global_count]->set_ords();
        global_count++;
    }
    if (shape_name == "Rectangle")
    {
        shapeArray[global_count] = new Rectangle(shape_name, contain_warp);
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
    char choice;
    cout <<"    a)      Sort by area (ascending)"<<endl;
    cout <<"    b)      Sort by area (descending)"<<endl;
    cout <<"    c)      Sort by special type and area\n"<<endl;
    cout <<"Please select sort option ('q' to go main menu): ";

    cin>>choice;
    //switch statement for each sort type
    switch (choice)
    {
    case 'a':
        //asc sort
        break;
    case 'b':
        //dsc sort
        break;
    case 'c':
        //special sort
    case 'q':
        cout<<"Going back to main menu.\n\n";
        break;
    }
}
//ascending sort
void asc_sort()
{
    cout<<"Sort by area (smallest to largest)...\n";
    //qsort and print in ascending order
    
}
//descending sort
void dsc_sort()
{
    cout<<"Sort by area (largest to smallest)...\n";
}
//special sort
void spec_sort()
{

}