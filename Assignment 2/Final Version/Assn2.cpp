#include "Shapes.h"
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
    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    //prompt user for type
    cout << "Please enter special type: ";
    cin >> spec_type;
    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
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
    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
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
    cout << "    c)      Sort by special type and area (ascending)\n"<< endl;
    
         
    cout << "Please select sort option ('q' to go main menu): ";

    cin >> choice;
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
        cout << vec[i]->toString() << endl << endl;
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
        cout << vec[i]->toString() << endl << endl;
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
    for(int i = 0; i < vec_NS.size(); i++)
    {
        cout << vec_NS[i]->getName() << endl;
    }
    for(int i = 0; i < vec_WS.size(); i++)
    {
        cout << vec_WS[i]->getName() << endl;
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