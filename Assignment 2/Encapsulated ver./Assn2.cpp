#include "ShapeTwoD.h"
#include "Circle.h"
#include "Square.h"
#include "Rectangle.h"
#include "Cross.h"
#include <iostream>
#include <string>

void menu();
void PressEnterToContinue();
bool check_number(string str);
void read_shape();
void sort_menu();
void dsc_sort(vector<ShapeTwoD *> vec);
void spec_sort(vector<ShapeTwoD *> vec);
void asc_sort(vector<ShapeTwoD *> vec);
void spec_sort_d(vector<ShapeTwoD *> vec);
using namespace std;
ShapeTwoD *shape_Ar[100];
//global array for shape objects with a 100 shape limit
int global_count = 0;
//global counter for appending to the last item in array
int main()
{
    string choice;
    bool flag = true;
    while (flag)
    {
        menu(); //prints the menu for the user
        cout << "Please enter your choice : ";
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

                for (int i = 0; i < global_count; i++) //iterates the shape array to dynamicaly comptue the array
                {
                    shape_Ar[i]->set_area(); //function runs a set method that computes the area depending on child
                }
                cout << "Computation completed! (" << global_count << " records were updated )" << endl;

                PressEnterToContinue();
                break;
            case 3:

                cout << "Total no. of records available = " << global_count << endl;
                for (int i = 0; i < global_count; i++) //iterates the shape array to dynamically call the toString function as it vaires from child to child
                {
                    cout << shape_Ar[i]->toString() << endl
                         << endl;
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
    for (auto v : shape_Ar)
    {
        delete v;
    }
    return 0;
}
//simple menu for program
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
    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    cout << "Please enter special type: ";
    cin >> spec_type;
    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    contain_warp = (spec_type == "WS") ? true : (spec_type == "NS") ? false
                                                                    : false;
    //create new shape based on user input
    if (shape_name == "Square")
    {
        //using global count as pointer arithmetic and ID
        shape_Ar[global_count] = new Square(shape_name, contain_warp, global_count); //allocated to the heap
        global_count++;
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        cout << "Record successfully stored. Going back to main menu....." << endl;
    }
    else if (shape_name == "Circle") //same application as Square
    {
        shape_Ar[global_count] = new Circle(shape_name, contain_warp, global_count);
        global_count++;
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        cout << "Record successfully stored. Going back to main menu....." << endl;
    }
    else if (shape_name == "Cross") //same application as Square
    {
        shape_Ar[global_count] = new Cross(shape_name, contain_warp, global_count);
        global_count++;
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        cout << "Record successfully stored. Going back to main menu....." << endl;
    }
    else if (shape_name == "Rectangle") //same application as Square
    {
        shape_Ar[global_count] = new Rectangle(shape_name, contain_warp, global_count);
        global_count++;
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        cout << "Record successfully stored. Going back to main menu....." << endl;
    }
    else
    {
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        cout << "Invaild shape name, exiting to menu" << endl
             << endl;
    }
}
//print the sort menu
void sort_menu()
{
    //get the array stored into a local vector to preserve the original shape order by id
    vector<ShapeTwoD *> vec;
    for (int i = 0; i < global_count; i++)
    {
        vec.push_back(shape_Ar[i]);
    }
    char choice;
    cout << "    a)      Sort by area (ascending)" << endl;
    cout << "    b)      Sort by area (descending)" << endl;
    cout << "    c)      Sort by special type and area (ascending)\n";
    cout << "    d)      Sort by special type and area (ascending)" << endl;

    cout << "Please select sort option ('q' to go main menu): ";

    cin >> choice;
    cout << endl;
    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
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
        break;
    case 'd':
        spec_sort_d(vec);
        cout << endl;
        break;
    case 'q':
        cout << "Going back to main menu.\n\n";
        break;
    }
    vec.clear();
}
//ascending sort
void asc_sort(vector<ShapeTwoD *> vec)
{
    //lambda function to get ascending order
    sort(vec.begin(), vec.end(), [](ShapeTwoD *lhs, ShapeTwoD *rhs) { //err squiggies
        return lhs->get_area() > rhs->get_area();
    });
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i]->toString() << endl
             << endl;
    }
}
//descending sort
void dsc_sort(vector<ShapeTwoD *> vec)
{
    //lambda function to get descending order
    sort(vec.begin(), vec.end(), [](ShapeTwoD *lhs, ShapeTwoD *rhs) { //err squiggies
        return lhs->get_area() < rhs->get_area();
    });
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i]->toString() << endl
             << endl;
    }
}
//special sort with precedence given to WS and largest area
void spec_sort(vector<ShapeTwoD *> vec)
{
    vector<ShapeTwoD *> vec_NS; //vector to store shapes with NS type
    vector<ShapeTwoD *> vec_WS; //vector to store shapes with WS type
    //get all NS type
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i]->getContainsWarpSpace() == false) //if object is NS append to NS vector else WS vector
        {
            vec_NS.push_back(vec[i]);
        }
        else
        {
            vec_WS.push_back(vec[i]);
        }
    }
    asc_sort(vec_WS);
    asc_sort(vec_NS);
    vec_NS.clear();
    vec_WS.clear();
}

//special sort with precedence given to WS and largest area
void spec_sort_d(vector<ShapeTwoD *> vec)
{
    vector<ShapeTwoD *> vec_NS; //vector to store shapes with NS type
    vector<ShapeTwoD *> vec_WS; //vector to store shapes with WS type
    //get all NS type
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i]->getContainsWarpSpace() == false) //if object is NS append to NS vector else WS vector
        {
            vec_NS.push_back(vec[i]);
        }
        else
        {
            vec_WS.push_back(vec[i]);
        }
    }
    dsc_sort(vec_WS);
    dsc_sort(vec_NS);
    vec_NS.clear();
    vec_WS.clear();
}
