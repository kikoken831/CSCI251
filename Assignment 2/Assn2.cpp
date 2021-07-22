#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

void menu();
void PressEnterToContinue();
bool check_number(string str);
void read_shape();
class ShapeTwoD
{
protected:
    string name;
    bool containsWarpSpace;

public:
    inline ShapeTwoD()
    {
        name = "N/A";
        containsWarpSpace = false;
    }

    ShapeTwoD(string name, bool containsWarpSpace)
    {
        this->name = name;
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

    void setName(string name)
    {
        this->name = name;
    }

    void setContainsWarpSpace(bool containsWarpSpace)
    {
        this->containsWarpSpace = containsWarpSpace;
    }
};

class Square : public ShapeTwoD
{
public:
    Square(string name, bool containsWarpSpace)
    {
        this->name = name;
        this->containsWarpSpace = containsWarpSpace;
    }
};

class Rectangle : public ShapeTwoD
{
public:
    Rectangle(string name, bool containsWarpSpace)
    {
        this->name = name;
        this->containsWarpSpace = containsWarpSpace;
    }
};
class Circle : public ShapeTwoD
{
public:
    Circle(string name, bool containsWarpSpace)
    {
        this->name = name;
        this->containsWarpSpace = containsWarpSpace;
    }
};
class Cross : public ShapeTwoD
{
public:
    Cross(string name, bool containsWarpSpace)
    {
        this->name = name;
        this->containsWarpSpace = containsWarpSpace;
    }
};
ShapeTwoD *shapeArray[100]; //global array for shape objects with a 100 shape limit
int global_count = 0; //global counter for appending to the last item in array
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
                PressEnterToContinue();
                break;
            case 2:

                PressEnterToContinue();
                break;
            case 3:

                PressEnterToContinue();
                break;
            case 4:
                for (int i = 0; i < global_count; i++)
                {
                    cout << (shapeArray[i])->getName()<<"  "<<boolalpha<< (shapeArray[i])->getContainsWarpSpace()<< endl;
                    
                }
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
    //prompt user for name of shape
    cout << "Please enter name of shape: ";
    cin >> shape_name;
    //prompt user for type
    cout << "Please enter special type: ";
    cin >> spec_type;
    //create new shape based on user input
    //if shape_name == "Square"
    if (shape_name == "Square")
    {
        if (spec_type == "WS"){
            //Square sq(shape_name, true);
            shapeArray[global_count] = new Square(shape_name,true);
            global_count++;
        }    
        else{
            shapeArray[global_count] = new Square(shape_name,false);
            global_count++;
        }
            
    }
    if (shape_name == "Circle")
    {
        if (spec_type == "WS")
            Circle cr(shape_name, true);
        else
            Circle cr(shape_name, false);
    }
    if (shape_name == "Cross")
    {
        if (spec_type == "WS")
            Cross cs(shape_name, true);
        else
            Cross cs(shape_name, false);
    }
    if (shape_name == "Rectangle")
    {
        if (spec_type == "WS")
            Rectangle rt(shape_name, true);
        else
            Rectangle rt(shape_name, false);
    }
    //run the shape child setter methods for getting the x,y ordinates
    //cout record stored successfully
}