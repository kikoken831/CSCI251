#include "Point2D.h"
#include "Point3D.h"
#include "Line2D.h"
#include "Line3D.h"
#include "MyTemplates.h"
#include <fstream>
#include <cstdlib>
#include <stdio.h> 
#include <stdlib.h>
using namespace std;

void menu();
void changeFilter();
void changeSorting();
void changeOrder();
bool check_number(string str);
void readFile();
void PressEnterToContinue();
void viewData();
void pre_Processing();
void storeData();
vector<string> tokenizeString(string input, string delimiter);
//used for storing all records and finding uniques
vector<string> all_Records;
vector<string> unique_Records;

//4 containers for each class
vector<Point2D> p2d_vec;
vector<Point3D> p3d_vec;
vector<Line2D> l2d_vec;
vector<Line3D> l3d_vec;

//mode names for 3 different sorting types
string filter_mode[] = {"Point2D", "Point3D", "Line2D", "Line3D"};
string sort_mode[] = {"x-ordinate", "y-ordinate", "z-ordinate", "Dist.Fr Origin", "Pt.1", "Pt.2", "Length"};
string order_mode[] = {"ASC", "DSC"};
int f_mode, s_mode, o_mode = 0; //all set to default

int main() //main
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
                readFile();
                pre_Processing();
                break;
            case 2:
                changeFilter();
                PressEnterToContinue();
                break;
            case 3:
                changeSorting();
                PressEnterToContinue();
                break;
            case 4:
                changeOrder();
                PressEnterToContinue();
                break;
            case 5:
                viewData();
                PressEnterToContinue();
                break;
            case 6:
                storeData();
                break;
            case 7:
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
}

void menu() //simple menu
{
    cout << endl;
    cout << left << setw(13) << "Student ID";
    cout << ": 7366814" << endl;
    cout << left << setw(13) << "Student Name";
    cout << ": Kendrick Kee" << endl;
    cout << "-------------------------------------" << endl;
    cout << "Welcome to Assn2 program!" << endl;
    cout << endl;
    cout << "1)       Read in data" << endl;
    cout << "2)       Specify filtering criteria (current : " << filter_mode[f_mode] << ")" << endl;
    cout << "3)       Specify sorting criteria   (current : " << sort_mode[s_mode] << ")" << endl;
    cout << "4)       Specify sorting order      (current : " << order_mode[o_mode] << ")" << endl;
    cout << "5)       View data" << endl;
    cout << "6)       Store data" << endl;
    cout << "7)       Exit" << endl;
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

    cout << "Going back to main menu..." << endl;
}
bool check_number(string str) //simple checknumber function for input validation for the menu
{
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false;
    return true;
}

//read file functions that reads all lines in the config. It is also able to detect any file ending with .txt and perform additional reading of the file.
void readFile()
{
    string inputFilename;
    string aLine;
    cout << "Please enter filename : ";
    // when prompted, pls type in 'messy.txt'
    cin >> inputFilename;

    fstream inputFile(inputFilename.c_str(), fstream::in);

    while (getline(inputFile, aLine))
    {
        aLine.erase(remove(aLine.begin(), aLine.end(), '['), aLine.end());
        aLine.erase(remove(aLine.begin(), aLine.end(), ']'), aLine.end());
        all_Records.push_back(aLine);
    }
    for (int i = 0; i < all_Records.size(); i++) //this loop will then go through the local vector and find the unique values of the vector
    {
        int j;
        for (j = 0; j < i; j++)
        {
            if (all_Records[i] == all_Records[j])
            {
                break;
            }
        }
        if (i == j)
        {
            unique_Records.push_back(all_Records[i]); //only append the value to the global vector if it is unique so it can be used for the summary report later
        }
    }
    cout << endl;
    cout << all_Records.size() << " records read in successfully! " << endl
         << all_Records.size() - unique_Records.size() << " of duplicates found. " << unique_Records.size() << " unique values stored!"
         << endl
         << "Going back to main menu" << endl
         << endl;
}

void pre_Processing()
{
    //tokenize the string
    vector<string> temp;
    vector<string> temp2;
    for (string x : unique_Records) //goes through each unique record
    {
        temp = tokenizeString(x, ", ");

        if (temp[0] == "Point2D") //creates a Point2D object if head of string matches
        {
            int i1, i2;
            i1 = stoi(temp[1]);
            i2 = stoi(temp[2]);
            p2d_vec.push_back(Point2D(i1, i2));
        }
        else if (temp[0] == "Point3D") //creates a Point3D object if head of string matches
        {
            int i1, i2, i3;
            i1 = stoi(temp[1]);
            i2 = stoi(temp[2]);
            i3 = stoi(temp[3]);
            p3d_vec.push_back(Point3D(i1, i2, i3));
        }
        else if (temp[0] == "Line2D") //creates a Line2D object if head of string matches
        {

            int i1, i2, i3, i4;
            i1 = stoi(temp[1]);
            i2 = stoi(temp[2]);
            i3 = stoi(temp[3]);
            i4 = stoi(temp[4]);
            l2d_vec.push_back(Line2D(i1, i2, i3, i4));
        }
        else if (temp[0] == "Line3D") //creates a Line3D object if head of string matches
        {
            int i1, i2, i3, i4, i5, i6;
            i1 = stoi(temp[1]);
            i2 = stoi(temp[2]);
            i3 = stoi(temp[3]);
            i4 = stoi(temp[4]);
            i5 = stoi(temp[5]);
            i6 = stoi(temp[6]);
            l3d_vec.push_back(Line3D(i1, i2, i3, i4, i5, i6));
        }
    }
}

void changeFilter() //changing filter mode
{
    cout << "[Specifying filtering criteria (current : " << filter_mode[f_mode] << ")]" << endl
         << endl;
    cout << "   a)      Point2D records" << endl;
    cout << "   b)      Point3D records" << endl;
    cout << "   c)      Line2D records" << endl;
    cout << "   d)      Line3D records" << endl;
    char choice;
    cout << endl
         << "Please enter your criteria (a - d) : ";
    cin >> choice;
    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    //setting the default sorting and order mode based on type of filter
    switch (choice)
    {
    case 'a':
        f_mode = 0;
        s_mode = 0;

        break;
    case 'b':
        f_mode = 1;
        s_mode = 0;
        break;
    case 'c':
        f_mode = 2;
        s_mode = 4;
        break;
    case 'd':
        f_mode = 3;
        s_mode = 4;
        break;
    }
    o_mode = 0;
    cout << "Filer criteria successfully set to '" << filter_mode[f_mode] << "'!" << endl
         << endl;
}

void changeSorting() //change sorting type func
{
    cout << "[Specifying sorting criteria (current : " << sort_mode[s_mode] << ")]" << endl
         << endl;

    char choice;
    if (f_mode == 0)
    {
        cout << "   a)      " << sort_mode[0] << " values" << endl;
        cout << "   b)      " << sort_mode[1] << " values" << endl;
        cout << "   c)      " << sort_mode[3] << " value" << endl;
        cout << endl
             << "Please enter your criteria (a - c) : ";
        cin >> choice;
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    }
    else if (f_mode == 1)
    {
        cout << "   a)      " << sort_mode[0] << " values" << endl;
        cout << "   b)      " << sort_mode[1] << " values" << endl;
        cout << "   c)      " << sort_mode[2] << " values" << endl;
        cout << "   d)      " << sort_mode[3] << " value" << endl;
        cout << endl
             << "Please enter your criteria (a - d) : ";
        cin >> choice;
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    }
    else
    {
        cout << "   a)      " << sort_mode[4] << "'s (x, y) values" << endl;
        cout << "   b)      " << sort_mode[5] << "'s (x, y) values" << endl;
        cout << "   c)      " << sort_mode[6] << "' value" << endl;
        cout << endl
             << "Please enter your criteria (a - c) : ";
        cin >> choice;
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    }
    //setting the correct sorting mode based on filter.
    switch (choice)
    {
    case 'a':
        s_mode = (f_mode < 2) ? 0 : 4;
        break;
    case 'b':
        s_mode = (f_mode < 2) ? 1 : 5;
        break;
    case 'c':
        s_mode = (f_mode == 1) ? 2 : (f_mode >= 2) ? 6
                                                   : 3;
        break;
    case 'd':
        s_mode = 3;
        break;
    }
    o_mode = 0; //changes order to ASC by default
    cout << "Sorting criteria successfully set to '" << sort_mode[s_mode] << "'!" << endl
         << endl;
}

void changeOrder() //change order func
{
    cout << "[Specifying sorting order (current : " << order_mode[o_mode] << ")]" << endl
         << endl;
    cout << "   a)      ASC (Ascending order)" << endl;
    cout << "   b)      DSC (Descending order)" << endl;
    char choice;
    cout << endl
         << "Please enter your criteria (a - b) : ";
    cin >> choice;
    switch (choice)
    {
    case 'a':
        o_mode = 0;
        break;
    case 'b':
        o_mode = 1;
        break;
    }
    cout << "Sorting order successfully set to '" << order_mode[o_mode] << "'!" << endl
         << endl;
}

void viewData() //displays all records based on filters
{
    cout << "\n[View data ...]" << endl;
    cout << "filering criteria : " << filter_mode[f_mode] << endl;
    cout << "sorting criteria : " << sort_mode[s_mode] << endl;
    cout << "sorting order : " << order_mode[o_mode] << endl
         << endl;
    switch (f_mode) //switch for each possible filter modes
    {
    case 0:
        switch (s_mode) //switch for each possible sorting modes for Point2D
        {
        case 0:
            if (o_mode == 0) //checks for ASC or DSC
            {
                //do Asc
                sort(p2d_vec.begin(), p2d_vec.end(), Point2D::compare_X_asc);
                cout << setw(5) << right << "X" << setw(6) << right << "Y"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point2D &x : p2d_vec)
                {
                    cout << x << endl;
                }
            }
            else
            {
                //do dsc
                sort(p2d_vec.begin(), p2d_vec.end(), Point2D::compare_X_dsc);
                cout << setw(5) << right << "X" << setw(6) << right << "Y"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point2D &x : p2d_vec)
                {
                    cout << x << endl;
                }
            }
            break;
        case 1:
            if (o_mode == 0) //checks for ASC or DSC
            {
                //do Asc
                sort(p2d_vec.begin(), p2d_vec.end(), Point2D::compare_Y_asc);
                cout << setw(5) << right << "X" << setw(6) << right << "Y"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point2D &x : p2d_vec)
                {
                    cout << x << endl;
                }
            }
            else
            {
                //do dsc
                sort(p2d_vec.begin(), p2d_vec.end(), Point2D::compare_Y_dsc);
                cout << setw(5) << right << "X" << setw(6) << right << "Y"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point2D &x : p2d_vec)
                {
                    cout << x << endl;
                }
            }
            break;
        case 3:
            if (o_mode == 0) //checks for ASC or DSC
            {
                //do Asc
                sort(p2d_vec.begin(), p2d_vec.end()); //asc
                cout << setw(5) << right << "X" << setw(6) << right << "Y"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point2D &x : p2d_vec)
                {
                    cout << x << endl;
                }
            }
            else
            {
                //do dsc
                sort(p2d_vec.begin(), p2d_vec.end(), greater<Point2D>()); //dsc
                cout << setw(5) << right << "X" << setw(6) << right << "Y"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point2D &x : p2d_vec)
                {
                    cout << x << endl;
                }
            }
            break;
        }
        break;
    case 1:
        switch (s_mode) //switch for each possible sorting modes for Point3D
        {
        case 0:
            if (o_mode == 0)
            {
                //do Asc
                sort(p3d_vec.begin(), p3d_vec.end(), Point3D::compare_X_asc);
                cout << setw(5) << right << "X" << setw(6) << right << "Y" << setw(6) << right << "Z"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point3D &x : p3d_vec)
                {
                    cout << x << endl;
                }
            }
            else
            {
                //do dsc
                sort(p3d_vec.begin(), p3d_vec.end(), Point3D::compare_X_dsc);
                cout << setw(5) << right << "X" << setw(6) << right << "Y" << setw(6) << right << "Z"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point3D &x : p3d_vec)
                {
                    cout << x << endl;
                }
            }
            break;
        case 1:
            if (o_mode == 0)
            {
                //do Asc
                sort(p3d_vec.begin(), p3d_vec.end(), Point3D::compare_Y_asc);
                cout << setw(5) << right << "X" << setw(6) << right << "Y" << setw(6) << right << "Z"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point3D &x : p3d_vec)
                {
                    cout << x << endl;
                }
            }
            else
            {
                //do dsc
                sort(p3d_vec.begin(), p3d_vec.end(), Point3D::compare_Y_dsc);
                cout << setw(5) << right << "X" << setw(6) << right << "Y" << setw(6) << right << "Z"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point3D &x : p3d_vec)
                {
                    cout << x << endl;
                }
            }
            break;
        case 2:
            if (o_mode == 0)
            {
                //do Asc
                sort(p3d_vec.begin(), p3d_vec.end(), Point3D::compare_Z_asc);
                cout << setw(5) << right << "X" << setw(6) << right << "Y" << setw(6) << right << "Z"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point3D &x : p3d_vec)
                {
                    cout << x << endl;
                }
            }
            else
            {
                //do dsc
                sort(p3d_vec.begin(), p3d_vec.end(), Point3D::compare_Z_dsc);
                cout << setw(5) << right << "X" << setw(6) << right << "Y" << setw(6) << right << "Z"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point3D &x : p3d_vec)
                {
                    cout << x << endl;
                }
            }
            break;
        case 3:
            if (o_mode == 0)
            {
                //do Asc
                sort(p3d_vec.begin(), p3d_vec.end());
                cout << setw(5) << right << "X" << setw(6) << right << "Y" << setw(6) << right << "Z"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point3D &x : p3d_vec)
                {
                    cout << x << endl;
                }
            }
            else
            {
                //do dsc
                sort(p3d_vec.begin(), p3d_vec.end(), greater<Point3D>());
                cout << setw(5) << right << "X" << setw(6) << right << "Y" << setw(6) << right << "Z"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point3D &x : p3d_vec)
                {
                    cout << x << endl;
                }
            }
            break;
        }
        break;
    case 2:
        switch (s_mode) //switch for all possible sorting modes for Line2D
        {
        case 4:
            if (o_mode == 0)
            {
                sort(l2d_vec.begin(), l2d_vec.end(), Line2D::compare_p1_asc);
                cout << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y"
                     << "    Length" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;
                for (Line2D &x : l2d_vec)
                {
                    cout << x << endl;
                }
            }
            else
            {
                sort(l2d_vec.begin(), l2d_vec.end(), Line2D::compare_p1_dsc);
                cout << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y"
                     << "    Length" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;
                for (Line2D &x : l2d_vec)
                {
                    cout << x << endl;
                }
            }
            break;
        case 5:
            if (o_mode == 0)
            {
                sort(l2d_vec.begin(), l2d_vec.end(), Line2D::compare_p2_asc);
                cout << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y"
                     << "    Length" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;
                for (Line2D &x : l2d_vec)
                {
                    cout << x << endl;
                }
            }
            else
            {
                sort(l2d_vec.begin(), l2d_vec.end(), Line2D::compare_p2_dsc);
                cout << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y"
                     << "    Length" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;
                for (Line2D &x : l2d_vec)
                {
                    cout << x << endl;
                }
            }
            break;
        case 6:
            if (o_mode == 0)
            {
                sort(l2d_vec.begin(), l2d_vec.end());
                cout << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y"
                     << "    Length" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;
                for (Line2D &x : l2d_vec)
                {
                    cout << x << endl;
                }
            }
            else
            {
                sort(l2d_vec.begin(), l2d_vec.end(), greater<Line2D>());
                cout << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y"
                     << "    Length" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;
                for (Line2D &x : l2d_vec)
                {
                    cout << x << endl;
                }
            }
            break;
        }
        break;
    case 3:
        switch (s_mode) //switch for all possible sorting modes for Line3D
        {
        case 4:
            if (o_mode == 0)
            {
                sort(l3d_vec.begin(), l3d_vec.end(), Line3D::compare_p1_asc);
                cout << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(6) << right << "P1-Z" << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y" << setw(6) << right << "P2-Z"
                     << "    Length" << endl
                     << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
                for (Line3D &x : l3d_vec)
                {
                    cout << x << endl;
                }
            }
            else
            {
                sort(l3d_vec.begin(), l3d_vec.end(), Line3D::compare_p1_dsc);
                cout << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(6) << right << "P1-Z" << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y" << setw(6) << right << "P2-Z"
                     << "    Length" << endl
                     << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
                for (Line3D &x : l3d_vec)
                {
                    cout << x << endl;
                }
            }
            break;
        case 5:
            if (o_mode == 0)
            {
                sort(l3d_vec.begin(), l3d_vec.end(), Line3D::compare_p2_asc);
                cout << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(6) << right << "P1-Z" << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y" << setw(6) << right << "P2-Z"
                     << "    Length" << endl
                     << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
                for (Line3D &x : l3d_vec)
                {
                    cout << x << endl;
                }
            }
            else
            {
                sort(l3d_vec.begin(), l3d_vec.end(), Line3D::compare_p2_dsc);
                cout << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(6) << right << "P1-Z" << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y" << setw(6) << right << "P2-Z"
                     << "    Length" << endl
                     << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
                for (Line3D &x : l3d_vec)
                {
                    cout << x << endl;
                }
            }
            break;
        case 6:
            if (o_mode == 0)
            {
                sort(l3d_vec.begin(), l3d_vec.end());
                cout << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(6) << right << "P1-Z" << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y" << setw(6) << right << "P2-Z"
                     << "    Length" << endl
                     << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
                for (Line3D &x : l3d_vec)
                {
                    cout << x << endl;
                }
            }
            else
            {
                sort(l3d_vec.begin(), l3d_vec.end(), greater<Line3D>());
                cout << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(6) << right << "P1-Z" << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y" << setw(6) << right << "P2-Z"
                     << "    Length" << endl
                     << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
                for (Line3D &x : l3d_vec)
                {
                    cout << x << endl;
                }
            }
            break;
        }
        break;
    }
}

void storeData() //stores output into a file
{
    string filename = "";
    cout << "Please enter filename : ";
    cin >> filename;
    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    ofstream outfile;
    outfile.open(filename);


    switch (f_mode) //switch for each possible filter modes
    {
    case 0:
        switch (s_mode) //switch for each possible sorting modes for Point2D
        {
        case 0:
            if (o_mode == 0) //checks for ASC or DSC
            {
                //do Asc
                sort(p2d_vec.begin(), p2d_vec.end(), Point2D::compare_X_asc);
                outfile << setw(5) << right << "X" << setw(6) << right << "Y"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point2D &x : p2d_vec)
                {
                    outfile << x << endl;
                }
                cout << p2d_vec.size() << " records output successfully!" << endl;
            }
            else
            {
                //do dsc
                sort(p2d_vec.begin(), p2d_vec.end(), Point2D::compare_X_dsc);
                outfile << setw(5) << right << "X" << setw(6) << right << "Y"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point2D &x : p2d_vec)
                {
                    outfile << x << endl;
                }
                cout << p2d_vec.size() << " records output successfully!" << endl;
            }
            break;
        case 1:
            if (o_mode == 0) //checks for ASC or DSC
            {
                //do Asc
                sort(p2d_vec.begin(), p2d_vec.end(), Point2D::compare_Y_asc);
                outfile << setw(5) << right << "X" << setw(6) << right << "Y"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point2D &x : p2d_vec)
                {
                    outfile << x << endl;
                }
                cout << p2d_vec.size() << " records output successfully!" << endl;
            }
            else
            {
                //do dsc
                sort(p2d_vec.begin(), p2d_vec.end(), Point2D::compare_Y_dsc);
                outfile << setw(5) << right << "X" << setw(6) << right << "Y"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point2D &x : p2d_vec)
                {
                    outfile << x << endl;
                }
                cout << p2d_vec.size() << " records output successfully!" << endl;
            }
            break;
        case 3:
            if (o_mode == 0) //checks for ASC or DSC
            {
                //do Asc
                sort(p2d_vec.begin(), p2d_vec.end()); //asc
                outfile << setw(5) << right << "X" << setw(6) << right << "Y"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point2D &x : p2d_vec)
                {
                    outfile << x << endl;
                }
                cout << p2d_vec.size() << " records output successfully!" << endl;
            }
            else
            {
                //do dsc
                sort(p2d_vec.begin(), p2d_vec.end(), greater<Point2D>()); //dsc
                outfile << setw(5) << right << "X" << setw(6) << right << "Y"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point2D &x : p2d_vec)
                {
                    outfile << x << endl;
                }
                cout << p2d_vec.size() << " records output successfully!" << endl;
            }
            break;
        }
        break;
    case 1:
        switch (s_mode) //switch for each possible sorting modes for Point3D
        {
        case 0:
            if (o_mode == 0)
            {
                //do Asc
                sort(p3d_vec.begin(), p3d_vec.end(), Point3D::compare_X_asc);
                outfile << setw(5) << right << "X" << setw(6) << right << "Y" << setw(6) << right << "Z"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point3D &x : p3d_vec)
                {
                    outfile << x << endl;
                }
                cout << p3d_vec.size() << " records output successfully!" << endl;
            }
            else
            {
                //do dsc
                sort(p3d_vec.begin(), p3d_vec.end(), Point3D::compare_X_dsc);
                outfile << setw(5) << right << "X" << setw(6) << right << "Y" << setw(6) << right << "Z"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point3D &x : p3d_vec)
                {
                    outfile << x << endl;
                }
                cout << p3d_vec.size() << " records output successfully!" << endl;
            }
            break;
        case 1:
            if (o_mode == 0)
            {
                //do Asc
                sort(p3d_vec.begin(), p3d_vec.end(), Point3D::compare_Y_asc);
                outfile << setw(5) << right << "X" << setw(6) << right << "Y" << setw(6) << right << "Z"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point3D &x : p3d_vec)
                {
                    outfile << x << endl;
                }
                cout << p3d_vec.size() << " records output successfully!" << endl;
            }
            else
            {
                //do dsc
                sort(p3d_vec.begin(), p3d_vec.end(), Point3D::compare_Y_dsc);
                outfile << setw(5) << right << "X" << setw(6) << right << "Y" << setw(6) << right << "Z"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point3D &x : p3d_vec)
                {
                    outfile << x << endl;
                }
                cout << p3d_vec.size() << " records output successfully!" << endl;
            }
            break;
        case 2:
            if (o_mode == 0)
            {
                //do Asc
                sort(p3d_vec.begin(), p3d_vec.end(), Point3D::compare_Z_asc);
                outfile << setw(5) << right << "X" << setw(6) << right << "Y" << setw(6) << right << "Z"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point3D &x : p3d_vec)
                {
                    outfile << x << endl;
                }
                cout << p3d_vec.size() << " records output successfully!" << endl;
            }
            else
            {
                //do dsc
                sort(p3d_vec.begin(), p3d_vec.end(), Point3D::compare_Z_dsc);
                outfile << setw(5) << right << "X" << setw(6) << right << "Y" << setw(6) << right << "Z"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point3D &x : p3d_vec)
                {
                    outfile << x << endl;
                }
                cout << p3d_vec.size() << " records output successfully!" << endl;
            }
            break;
        case 3:
            if (o_mode == 0)
            {
                //do Asc
                sort(p3d_vec.begin(), p3d_vec.end());
                outfile << setw(5) << right << "X" << setw(6) << right << "Y" << setw(6) << right << "Z"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point3D &x : p3d_vec)
                {
                    outfile << x << endl;
                }
                cout << p3d_vec.size() << " records output successfully!" << endl;
            }
            else
            {
                //do dsc
                sort(p3d_vec.begin(), p3d_vec.end(), greater<Point3D>());
                outfile << setw(5) << right << "X" << setw(6) << right << "Y" << setw(6) << right << "Z"
                     << "    Dist. Fr Origin" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;

                for (Point3D &x : p3d_vec)
                {
                    outfile << x << endl;
                }
                cout << p3d_vec.size() << " records output successfully!" << endl;
            }
            break;
        }
        break;
    case 2:
        switch (s_mode) //switch for all possible sorting modes for Line2D
        {
        case 4:
            if (o_mode == 0)
            {
                sort(l2d_vec.begin(), l2d_vec.end(), Line2D::compare_p1_asc);
                outfile << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y"
                     << "    Length" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;
                for (Line2D &x : l2d_vec)
                {
                    outfile << x << endl;
                }
                cout << l2d_vec.size() << " records output successfully!" << endl;
            }
            else
            {
                sort(l2d_vec.begin(), l2d_vec.end(), Line2D::compare_p1_dsc);
                outfile << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y"
                     << "    Length" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;
                for (Line2D &x : l2d_vec)
                {
                    outfile << x << endl;
                }
                cout << l2d_vec.size() << " records output successfully!" << endl;
            }
            break;
        case 5:
            if (o_mode == 0)
            {
                sort(l2d_vec.begin(), l2d_vec.end(), Line2D::compare_p2_asc);
                outfile << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y"
                     << "    Length" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;
                for (Line2D &x : l2d_vec)
                {
                    outfile << x << endl;
                }
                cout << l2d_vec.size() << " records output successfully!" << endl;
            }
            else
            {
                sort(l2d_vec.begin(), l2d_vec.end(), Line2D::compare_p2_dsc);
                outfile << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y"
                     << "    Length" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;
                for (Line2D &x : l2d_vec)
                {
                    outfile << x << endl;
                }
                cout << l2d_vec.size() << " records output successfully!" << endl;
            }
            break;
        case 6:
            if (o_mode == 0)
            {
                sort(l2d_vec.begin(), l2d_vec.end());
                outfile << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y"
                     << "    Length" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;
                for (Line2D &x : l2d_vec)
                {
                    outfile << x << endl;
                }
                cout << l2d_vec.size() << " records output successfully!" << endl;
            }
            else
            {
                sort(l2d_vec.begin(), l2d_vec.end(), greater<Line2D>());
                outfile << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y"
                     << "    Length" << endl
                     << "- - - - - - - - - - - - - - - - - - -" << endl;
                for (Line2D &x : l2d_vec)
                {
                    outfile << x << endl;
                }
                cout << l2d_vec.size() << " records output successfully!" << endl;
            }
            break;
        }
        break;
    case 3:
        switch (s_mode) //switch for all possible sorting modes for Line3D
        {
        case 4:
            if (o_mode == 0)
            {
                sort(l3d_vec.begin(), l3d_vec.end(), Line3D::compare_p1_asc);
                outfile << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(6) << right << "P1-Z" << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y" << setw(6) << right << "P2-Z"
                     << "    Length" << endl
                     << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
                for (Line3D &x : l3d_vec)
                {
                    outfile << x << endl;
                }
                cout << l3d_vec.size() << " records output successfully!" << endl;
            }
            else
            {
                sort(l3d_vec.begin(), l3d_vec.end(), Line3D::compare_p1_dsc);
                outfile << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(6) << right << "P1-Z" << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y" << setw(6) << right << "P2-Z"
                     << "    Length" << endl
                     << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
                for (Line3D &x : l3d_vec)
                {
                    outfile << x << endl;
                }
                cout << l3d_vec.size() << " records output successfully!" << endl;
            }
            break;
        case 5:
            if (o_mode == 0)
            {
                sort(l3d_vec.begin(), l3d_vec.end(), Line3D::compare_p2_asc);
                outfile << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(6) << right << "P1-Z" << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y" << setw(6) << right << "P2-Z"
                     << "    Length" << endl
                     << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
                for (Line3D &x : l3d_vec)
                {
                    outfile << x << endl;
                }
                cout << l3d_vec.size() << " records output successfully!" << endl;
            }
            else
            {
                sort(l3d_vec.begin(), l3d_vec.end(), Line3D::compare_p2_dsc);
                outfile << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(6) << right << "P1-Z" << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y" << setw(6) << right << "P2-Z"
                     << "    Length" << endl
                     << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
                for (Line3D &x : l3d_vec)
                {
                    outfile << x << endl;
                }
                cout << l3d_vec.size() << " records output successfully!" << endl;
            }
            break;
        case 6:
            if (o_mode == 0)
            {
                sort(l3d_vec.begin(), l3d_vec.end());
                outfile << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(6) << right << "P1-Z" << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y" << setw(6) << right << "P2-Z"
                     << "    Length" << endl
                     << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
                for (Line3D &x : l3d_vec)
                {
                    outfile << x << endl;
                }
                cout << l3d_vec.size() << " records output successfully!" << endl;
            }
            else
            {
                sort(l3d_vec.begin(), l3d_vec.end(), greater<Line3D>());
                outfile << setw(5) << right << "P1-X" << setw(6) << right << "P1-Y" << setw(6) << right << "P1-Z" << setw(9) << right << "P2-X" << setw(6) << right << "P2-Y" << setw(6) << right << "P2-Z"
                     << "    Length" << endl
                     << "- - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
                for (Line3D &x : l3d_vec)
                {
                    outfile << x << endl;
                }
                cout << l3d_vec.size() << " records output successfully!" << endl;
            }
            break;
        }
        break;
    }
    outfile.close();
}
vector<string> tokenizeString(string input, string delimiter) //function provided by tutor to split strings based on delimiter
{
    size_t pos = 0;
    string token;
    vector<string> result;

    while ((pos = input.find(delimiter)) != string::npos)
    {
        token = input.substr(0, pos);
        result.push_back(token);
        input.erase(0, pos + delimiter.length());
    }

    result.push_back(input);

    return (result);
}