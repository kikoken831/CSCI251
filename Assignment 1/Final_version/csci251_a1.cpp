#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <limits>
#include <stdio.h>
using namespace std;
void PressEnterToContinue();
void menu();
void readAFile(string str, int counter);
bool check_number(string str);
void read_config();
void display_city_map();
void display_value_map(int version, int datatype);
void display_cloud_map(int version);
void display_atmos_map(int version);
void summary_report();
void get_cty_names(string filename);
vector<string> tokenizeString(string input, string delimiter);
void print_top();
void print_btm();
double get_mapped_values(int cityID, int type, int *counter);
double get_surroundings(int cityID, int type, int *counter);
void rain_prob(char c, char p);
void rain_prob_map(int mode);
void rain_prob_whole();
vector<string> city_names;
int x;
int y;
int *master_array;
int main() //main function
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
                read_config();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            case 2:
                display_city_map();
                PressEnterToContinue();
                break;
            case 3:
                display_value_map(0, 1);
                PressEnterToContinue();
                break;
            case 4:
                display_value_map(1, 1);
                PressEnterToContinue();
                break;
            case 5:
                display_value_map(0, 2);
                PressEnterToContinue();
                break;
            case 6:
                display_value_map(1, 2);
                PressEnterToContinue();
                break;
            case 7:
                summary_report();
                PressEnterToContinue();
                break;
            case 8:
                rain_prob_map(0);
                PressEnterToContinue();
                break;
            case 9:
                rain_prob_map(1);
                PressEnterToContinue();
                break;
            case 10:
                rain_prob_whole();
                PressEnterToContinue();
                break;
            case 11:
                cout << "Exiting Program" << endl;
                delete[] master_array; //upon exiting the program deallocated memory of the dynamic array
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
//simple menu function displaying all the possible functions of the program
void menu()
{
    cout << left << setw(13) << "Student ID";
    cout << ": 7366814" << endl;
    cout << left << setw(13) << "Student Name";
    cout << ": Kendrick Kee" << endl;
    cout << "-------------------------------------" << endl;
    cout << "Welcome to Weather Information Processing System!" << endl;
    cout << endl;
    cout << "1)       Read in and process a configuration file" << endl;
    cout << "2)       Display city map" << endl;
    cout << "3)       Display cloud coverage map (cloudiness index)" << endl;
    cout << "4)       Display cloud coverage map (LMH symbols)" << endl;
    cout << "5)       Display atmospheric pressure map (pressure index)" << endl;
    cout << "6)       Display atmospheric pressure map (LMH symbols)" << endl;
    cout << "7)       Show weather forecast summary report" << endl;
    cout << "8)       Rain Probability Map (Rain Index)" << endl;
    cout << "9)       Rain Probability Map (LMH Symbols)" << endl;
    cout << "10)      Rain Probability of Entire Map" << endl;
    cout << "11)      Quit" << endl;
    cout << endl;
}
//read file functions that reads all lines in the config. It is also able to detect any file ending with .txt and perform additional reading of the file.
void read_config()
{

    cout << "Please enter input filename : ";

    string inputFilename;

    // when prompted, pls type in 'config.txt'
    cin >> inputFilename;

    fstream inputFile(inputFilename.c_str(), fstream::in);
    string aLine;
    vector<string> temp;
    vector<string> temp2;
    string temps;

    while (getline(inputFile, aLine))
    {
        //seperates the text GridX_IdxRange=0-8 into GridX_IdxRange and 0-8
        temp = tokenizeString(aLine, "=");
        if (temp[0] == "GridX_IdxRange") //only if the first half contains GridX_IdxRange, proceed to store the index length for the map
        {
            temps = temp[1];
            temp2 = tokenizeString(temps, "-");                                       //seperates into 0-8 into 0 and 8
            x = stoi(temp2[1]) + 1;                                                   //store 8 + 1 as index size as 0 to 8 has 9 slots
            cout << "Reading in GridX_IdxRange : " << temp[1] << "... done!" << endl; //cout successful read-in
        }
        if (temp[0] == "GridY_IdxRange") //similar to the previous block but instead for GridY_IdxRange
        {
            temps = temp[1];
            temp2 = tokenizeString(temps, "-");
            y = stoi(temp2[1]) + 1; //stores 8 + 1 as index starts from 0
            cout << "Reading in GridY_IdxRange : " << temp[1] << "... done!" << endl;
        }
    }

    master_array = new int[3 * x * y](); //declare a 3D dynamic array, 3D array is used as the program stores 3 2D maps(city,cloud,pressure) with exactly the same size and coordinates. It also allows for easy cross refering of data sets without the use of classes.
    int counter = 0;
    string bLine;
    fstream inputFile1(inputFilename.c_str(), fstream::in); //second file stream to find all the lines that end in .txt for value mapping
    while (getline(inputFile1, bLine))
    {

        size_t pos = bLine.find(".txt");

        if (pos != string::npos)
        {
            readAFile(bLine, counter); //function that reads the filename from within a file and stores it into our 3D array
            counter++;
        }
    }

    cout << endl;
    cout << "All records successfuly stored. Going back to main menu" << endl
         << endl;
}
//function that reads a file that was called from a previous function. This function reads all strings that ends with .txt
void readAFile(string filename, int counter)
{
    fstream inputFile(filename.c_str(), fstream::in); //opens the .txt file name that was passed through
    int value;
    int get_x;
    int get_y;
    vector<string> temp;
    vector<string> temp2;

    if (counter == 0)
    {
        //sets datatype to 0 for the city "layer" of the map
        get_cty_names(filename); //calls this function to store the unique names and cityID of citylocation file.
    }
    cout << "Storing data from : " << filename;
    string aLine;

    while (getline(inputFile, aLine)) //reads everyline of the .txt file
    {
        if (!aLine.empty())
        {
            temp = tokenizeString(aLine, "-");//splits [1, 1]-3-Big_City into [1, 1]  3  Big_City
            //[12,34] how would you approach this case?
            //split via "," to have [12 and 34] (We can assume no value greater than 99)
            temp2 = tokenizeString(temp[0],",");
            //temp2[0] = "[12" and temp2[1] = "34]"
            temp2[0].erase(0,1);
            temp2[1].erase(temp2[1].size()-1);
            get_x = stoi(temp2[0]);
            get_y = stoi(temp2[1]);
            value = stoi(temp[1]);//gets the value of the cordinates as it will be the second element of the vector
            *(master_array + counter * x * y + get_x * y + get_y) = value; //using pointer arithmatic, select the file-read indexes and assign the value to the array *('array_name' + [first index] * size of second index * size of third index + [second index] * size of third index + [third index])
        }
    }
    cout << "... done!" << endl;
}
//function that gets all the city location names [1, 1]-"3-Big_City" and stores them into a vector, it will then proceed to only store the unique names of the cities, This is for the summary report needed in the later part of the program
void get_cty_names(string filename)
{
    string aLine;
    vector<string> temp;
    vector<string> all_city;
    fstream inputFile(filename.c_str(), fstream::in); //opens citylocation.txt
    //getting all city names and values
    while (getline(inputFile, aLine)) //reads everyline in citylocation.txt
    {
        vector<int>::iterator ip;
        temp = tokenizeString(aLine, "]-"); //splits the string that proceeds "]-" which will normally be "X-City_Name" in the second index [1]
        all_city.push_back(temp[1]);        //stores the "X-City_Name"  string into the local vector
    }
    for (int i = 0; i < all_city.size(); i++) //this loop will then go through the local vector and find the unique values of the vector
    {
        int j;
        for (j = 0; j < i; j++)
        {
            if (all_city[i] == all_city[j])
            {
                break;
            }
        }
        if (i == j)
        {
            city_names.push_back(all_city[i]); //only append the value to the global vector if it is unique so it can be used for the summary report later
        }
    }
    //sort(city_names.begin(), city_names.end()); this line is commented out as linux g++ compiler is unable to use
}
//this function prints the a map of where the city is located on a x by y grid
void display_city_map()
{
    cout << "Displaying City Map" << endl;
    print_top();                     //this functions is able to dynamically print the #'s for the top of the map depending on the size of x and y
    for (int j = y - 1; j >= 0; j--) //nest for loops of traverse the array, outer loop starts from y and decrements to 0 due to the array being transposed for the assignment output
    {
        if (j < 10)
            cout << "  " << j << "  # "; //this line prints the left side of the map with the indexes
        else
            cout << "  " << j << " # "; //for double digit indexes
        for (int k = 0; k < x; k++)
        {

            if (*(master_array + 0 * x * y + k * y + j) != 0) //only print the cityID if it is present in the coordinates else just print a blank space
            {
                cout << " " << *(master_array + 0 * x * y + k * y + j) << " "; //using pointer arithmatic, print out the value stored with the for loop indexes for reference *('array_name' + [first index] * size of second index * size of third index + [second index] * size of third index + [third index])
            }
            else
            {
                cout << "   ";
            }
        }
        cout << " #" << endl; //prints the # before ending the line
    }

    print_btm(); //this functions is able to dynamically print the #'s for the bottom of the map depending on the size of x and y
    cout << "Operation completed. Going back to main menu" << endl
         << endl;
}
//this function displays the cloud map and takes an int called version as a parameter, the int will help us differenciate which type of output it will produce (index or "LMH")
void display_value_map(int version, int datatype)
{
    if (version == 0 && datatype == 1) //function becomes cloudiness index mode
    {
        cout << "Display Cloud coverage map (cloudiness index)" << endl;
    }
    else if (version == 1 && datatype == 1) //function becomes LMH mode
    {
        cout << "Display Cloud coverage map (LMH symbols)" << endl;
    }
    else if (version == 0 && datatype == 2) //function becomes pressure index mode
    {
        cout << "Display Pressure coverage map (cloudiness index)" << endl;
    }
    else if (version == 1 && datatype == 2) //function becomes LMH mode
    {
        cout << "Display Pressure coverage map (LMH symbols)" << endl;
    }

    print_top();                     //this functions is able to dynamically print the #'s for the top of the map depending on the size of x and y
    for (int j = y - 1; j >= 0; j--) //nested for loops of array traversal, note that the outer loop traverses the y cordinates first as the map is transposed to match the assignment output as the top left of the map is [0,8] instead of the traditional [0,0]
    {
        if (j < 10)
            cout << "  " << j << "  # "; //this line prints the left side of the map with the indexes
        else
            cout << "  " << j << " # "; //for double digit indexes
        for (int k = 0; k < x; k++)     //nested loop for the x axis
        {

            if (version == 0) //for cloudiness index mode, just print out the value divided by 10 as the array is an int array no decimal or rounding will occur
            {
                cout << " " << (*(master_array + datatype * x * y + k * y + j) / 10) << " ";
            }
            else //if function is in LMH mode, proceed with condition checking for LOW MEDIUM or HIGH output for the map
            {
                if (*(master_array + datatype * x * y + k * y + j) < 35) //LMH computation
                {
                    cout << " L ";
                }
                else if (*(master_array + datatype * x * y + k * y + j) < 65)
                {
                    cout << " M ";
                }
                else
                {
                    cout << " H ";
                }
            }
        }
        cout << " #" << endl; //prints the # before ending the line
    }
    print_btm(); //dynamically prints the bottom of the map with the indexes
    cout << "Operation completed. Going back to main menu" << endl
         << endl;
}
//function that prints the summary report
void summary_report()
{
    cout << "Weather Forecast Summary Report" << endl;
    cout << "-------------------------------" << endl;
    vector<string> temp;
    int cityId;
    string cityName;
    double cloud_avg;
    double pres_avg;

    char cloud, press;
    for (int i = 0; i < city_names.size(); i++) //loops all the unique city names and ids vector
    {
        int counter = 0;
        double t;
        temp = tokenizeString(city_names[i], "-"); //splits the strings stored in the vector from 3-Big_City to 3 and Big_City
        cityId = stoi(temp[0]);                    //stores cityID as int as it is needed for array traversal later
        cityName = temp[1];                        //store the city name which will be printed in the report
        cout << "City Name : " << cityName << endl;
        cout << "City ID : " << cityId << endl;
        cloud_avg = get_mapped_values(cityId, 1, &counter);            //gets the sum of all the cloud values that match the cityID, counter is being passed by reference and incremented
        cloud_avg = cloud_avg + get_surroundings(cityId, 1, &counter); //gets the sum of all the unique cloud values that surround the city matching the ID, counter is being passed by reference and incremented
        cloud_avg = cloud_avg / counter;                               //gets the true average value by dividing the sum by the total number of squares
        if (cloud_avg >= 0 && cloud_avg < 35)                          //conditional statements that gets the LMH value for rain probability computation
        {
            cloud = 'L';
        }
        else if (cloud_avg < 65)
        {
            cloud = 'M';
        }
        else if (cloud_avg < 100)
        {
            cloud = 'H';
        }
        cout << left << setw(25) << "Ave. Cloud Cover (ACC)" << right << setw(10) << ": " //prints the cloud cover summary
             << fixed << setprecision(2) << cloud_avg
             << "(" << cloud << ")" << endl;

        counter = 0;                                                 //resets the counter as new calculation for pressure is being made, could be ommited as counter would be identical, but cloud and pressure uses the same method therefore counter will be incremented for both occasions
        pres_avg = get_mapped_values(cityId, 2, &counter);           //gets the sum of all the pressure values that match the cityID, counter is being passed by reference and incremented
        pres_avg = pres_avg + get_surroundings(cityId, 2, &counter); //gets the sum of all the unique surrounding pressure values that match the cityID, coutner is being passed by reference and incremented
        pres_avg = pres_avg / counter;                               //divides the sum by counter, counter being the number of blocks to get the pressure average
        if (pres_avg >= 0 && pres_avg < 35)                          //conditional statement that converts the pressure average into LMH, to be used for rain probability computation
        {
            press = 'L';
        }
        else if (pres_avg < 65)
        {
            press = 'M';
        }
        else if (pres_avg < 100)
        {
            press = 'H';
        }

        cout << left << setw(25) << "Ave. Pressure  (AP)" << right << setw(10) << ": " //prints the pressure summary
             << fixed << setprecision(2) << pres_avg
             << "(" << press << ")" << endl;
        rain_prob(cloud, press); //with the LMH of cloud and pressure average, rain probablity can be computed and printed out
        cout << endl;
    }
    cout << "Operation completed. Going back to main menu" << endl
         << endl;
}
//function that travereses the whole map and gets the sum of the values that matched the cityID
double get_mapped_values(int cityID, int type, int *counter)
{
    double sum = 0;
    //find all grids in map
    for (int _x = 0; _x < x; _x++)
    {

        for (int _y = 0; _y < y; _y++)
        {

            if (cityID == *(master_array + 0 * x * y + _x * y + _y)) //if the cityID matches what is being dereferenced at city level, get the value thats being stored in cloud or pressure level depending on the type parameter being passed through
            {
                //sum all grids and increment counter for averaging
                sum += *(master_array + type * x * y + _x * y + _y);
                *counter = *counter + 1; //incremented the counter by reference as this function is already returning a sum, it will be able to return another value.
            }
        }
    }
    return sum; //return the sum to for averaging computation
}
double get_surroundings(int cityID, int type, int *counter)
{
    double sum;

    vector<string> cords;        //stores all the co-ordinates of surrounding values
    vector<string> unique_cords; // stores only the unique cords after end of search as there will be overlaps due depending on city size
    //finds city blocks that == cityID
    //finds the surroundings of city that matches cityID
    //surroundings is determined by not having the same cityID as what is being passed through and not out of bounds _x > x or _y > y
    for (int _x = 0; _x < x; _x++)
    {

        for (int _y = 0; _y < y; _y++)
        {

            if (cityID == *(master_array + 0 * x * y + _x * y + _y))
            {
                //up = y-1, x
                //checks if its already not part of city and within bounds _x > x-1 && -y > y -1 && _x,_y >= 0
                if (*(master_array + 0 * x * y + _x * y + (_y - 1)) != cityID && (_y - 1 >= 0))
                {
                    cords.push_back(to_string(_x) + "-" + to_string(_y - 1));
                }
                //up-right = y-1, x+1
                if (*(master_array + 0 * x * y + (_x + 1) * y + (_y - 1)) != cityID && (_x + 1 < x) && (_y - 1 >= 0))
                {
                    cords.push_back(to_string(_x + 1) + "-" + to_string(_y - 1));
                }
                //right = y, x+1
                if (*(master_array + 0 * x * y + (_x + 1) * y + _y) != cityID && (_x + 1 < x))
                {
                    cords.push_back(to_string(_x + 1) + "-" + to_string(_y));
                }
                //down-right = y+1, x+1
                if (*(master_array + 0 * x * y + (_x + 1) * y + (_y + 1)) != cityID && (_x + 1 < x) && (_y + 1 < y))
                {
                    cords.push_back(to_string(_x + 1) + "-" + to_string(_y + 1));
                }
                //down = y+1, x
                if (*(master_array + 0 * x * y + _x * y + (_y + 1)) != cityID && (_y + 1 < y))
                {
                    cords.push_back(to_string(_x) + "-" + to_string(_y + 1));
                }
                //down-left = y+1, x-1
                if (*(master_array + 0 * x * y + (_x - 1) * y + (_y + 1)) != cityID && (_x - 1 >= 0) && (_y + 1 < y))
                {
                    cords.push_back(to_string(_x - 1) + "-" + to_string(_y + 1));
                }
                //left = y, x-1
                if (*(master_array + 0 * x * y + (_x - 1) * y + _y) != cityID && (_x - 1 >= 0))
                {
                    cords.push_back(to_string(_x - 1) + "-" + to_string(_y));
                }
                //up-left = y-1, x-1

                if (*(master_array + 0 * x * y + (_x - 1) * y + (_y - 1)) != cityID && (_x - 1 >= 0) && (_y - 1 >= 0))
                {
                    cords.push_back(to_string(_x - 1) + "-" + to_string(_y - 1));
                }
            }
        }
    }

    //remove duplicates as there will be overlap if the city area is bigger than 1 block
    for (int i = 0; i < cords.size(); i++)
    {
        int j;
        for (j = 0; j < i; j++)
        {
            if (cords[i] == cords[j])
            {
                break;
            }
        }
        if (i == j)
        {
            unique_cords.push_back(cords[i]);
            //cout<<cords[i] << " ";
        }
    }

    vector<string> temp;
    //derefence the co-ords to get the value and return out the sum
    for (int i = 0; i < unique_cords.size(); i++)
    {
        temp = tokenizeString(unique_cords[i], "-");

        sum += *(master_array + type * x * y + stoi(temp[0]) * y + stoi(temp[1]));
        *counter = *counter + 1; //coutner is incremented by reference and sum is already being returned in this function
    }

    return sum;
}
void rain_prob(char c, char p) //simple rain probability print function based on the table given by the assignment document
{
    float prob;
    //if statements for every possible LMH combination leading to a computation of rain probability
    if (c == 'H' && p == 'L')
    {
        //90%
        prob = 90;
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": "
             << fixed << setprecision(2) << prob
             << endl;
        cout << "~~~~" << endl;
        cout << "~~~~~" << endl;
        cout << "\\\\\\\\\\" << endl;
    }
    else if (c == 'M' && p == 'L')
    {
        //80%
        prob = 80;
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": "
             << fixed << setprecision(2) << prob
             << endl;
        cout << "~~~~" << endl;
        cout << "~~~~~" << endl;
        cout << " \\\\\\\\" << endl;
    }
    else if (c == 'L' && p == 'L')
    {
        //70%
        prob = 70;
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": "
             << fixed << setprecision(2) << prob
             << endl;
        cout << "~~~~" << endl;
        cout << "~~~~~" << endl;
        cout << "  \\\\\\" << endl;
    }
    else if (c == 'H' && p == 'M')
    {
        //60%
        prob = 60;
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": "
             << fixed << setprecision(2) << prob
             << endl;
        cout << "~~~~" << endl;
        cout << "~~~~~" << endl;
        cout << "   \\\\" << endl;
    }
    else if (c == 'M' && p == 'M')
    {
        //50%
        prob = 50;
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": "
             << fixed << setprecision(2) << prob
             << endl;
        cout << "~~~~" << endl;
        cout << "~~~~~" << endl;
        cout << "    \\" << endl;
    }
    else if (c == 'L' && p == 'M')
    {
        //40%
        prob = 40;
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": "
             << fixed << setprecision(2) << prob
             << endl;
        cout << "~~~~" << endl;
        cout << "~~~~~" << endl;
    }
    else if (c == 'H' && p == 'H')
    {
        //30%
        prob = 30;
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": "
             << fixed << setprecision(2) << prob
             << endl;
        cout << "~~~" << endl;
        cout << "~~~~" << endl;
    }
    else if (c == 'M' && p == 'H')
    {
        //20%
        prob = 20;
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": "
             << fixed << setprecision(2) << prob
             << endl;
        cout << "~~" << endl;
        cout << "~~~" << endl;
    }
    else if (c == 'L' && p == 'H')
    {
        //10%
        prob = 10;
        cout << left << setw(25) << "Probability of Rain (%)" << right << setw(10) << ": "
             << fixed << setprecision(2) << prob
             << endl;
        cout << "~" << endl;
        cout << "~~" << endl;
    }
}

bool check_number(string str) //simple checknumber function for input validation for the menu
{
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false;
    return true;
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

void print_top()
{
    //print top of map
    cout << "    ";
    for (int i = 0; i < x + 2; i++)
    {
        cout << " # ";
    }
    cout << endl;
}
void print_btm()
{
    //print bottom of map
    cout << "    ";
    for (int i = 0; i < x + 2; i++)
    {
        cout << " # ";
    }
    cout << endl;
    cout << "       ";
    for (int i = 0; i < x; i++)
    {
        if (i < 10)
            cout << " " << i << " ";
        else
            cout << " " << i;
    }
    cout << endl;
}
//Additional Features
//Rain probability index map
void rain_prob_map(int mode)
{
    char c, p;
    int prob;
    cout << "Displaying Rain Probability Map" << endl;
    print_top();                     //this functions is able to dynamically print the #'s for the top of the map depending on the size of x and y
    for (int j = y - 1; j >= 0; j--) //nest for loops of traverse the array, outer loop starts from y and decrements to 0 due to the array being transposed for the assignment output
    {
        if (j < 10)
            cout << "  " << j << "  # "; //this line prints the left side of the map with the indexes
        else
            cout << "  " << j << " # "; //for double digit indexes
        for (int k = 0; k < x; k++)
        {
            if (*(master_array + 1 * x * y + k * y + j) < 35) //conditional check for LMH for cloud per grid
            {
                c = 'L';
            }
            else if (*(master_array + 1 * x * y + k * y + j) < 65)
            {
                c = 'M';
            }
            else if (*(master_array + 1 * x * y + k * y + j) < 100)
            {
                c = 'H';
            }

            if (*(master_array + 2 * x * y + k * y + j) < 35) //conditional check for LMH for pressure per grid
            {
                p = 'L';
            }
            else if (*(master_array + 2 * x * y + k * y + j) < 65)
            {
                p = 'M';
            }
            else if (*(master_array + 2 * x * y + k * y + j) < 100)
            {
                p = 'H';
            }
            if (c == 'H' && p == 'L') //gets the rain probabily in the Tens digit as all probability ends in a 0
            {
                //90%
                prob = 9;
            }
            else if (c == 'M' && p == 'L')
            {
                //80%
                prob = 8;
            }
            else if (c == 'L' && p == 'L')
            {
                //70%
                prob = 7;
            }
            else if (c == 'H' && p == 'M')
            {
                //60%
                prob = 6;
            }
            else if (c == 'M' && p == 'M')
            {
                //50%
                prob = 5;
            }
            else if (c == 'L' && p == 'M')
            {
                //40%
                prob = 4;
            }
            else if (c == 'H' && p == 'H')
            {
                //30%
                prob = 3;
            }
            else if (c == 'M' && p == 'H')
            {
                //20%
                prob = 2;
            }
            else if (c == 'L' && p == 'H')
            {
                //10%
                prob = 1;
            }
            if (mode == 0)
            {
                cout << " " << prob << " ";
            }
            else
            {
                if (prob < 4) //conditional statement that converts the pressure average into LMH, to be used for rain probability computation
                {
                    cout << " L ";
                }
                else if (prob < 7)
                {
                    cout << " M ";
                }
                else if (prob < 10)
                {
                    cout << " H ";
                }
            }
        }
        cout << " #" << endl; //prints the # before ending the line
    }

    print_btm(); //this functions is able to dynamically print the #'s for the bottom of the map depending on the size of x and y
    cout << "Operation completed. Going back to main menu" << endl
         << endl;
}
//function gets the rain probability of the entire grid by cross referencing cloud and pressure values at each block
void rain_prob_whole()
{
    double sum1, sum2;
    char c, p;
    for (int _x = 0; _x < x; _x++) //array traversal of the entire grid
    {
        for (int _y = 0; _y < y; _y++)
        {
            //sum all grids and increment counter for averaging
            sum1 += *(master_array + 1 * x * y + _x * y + _y);
            sum2 += *(master_array + 2 * x * y + _x * y + _y);
        }
    }
    sum1 = sum1 / (x * y); //get cloud sum and average
    sum2 = sum2 / (x * y); //get pressure sum and average
    if (sum1 < 35)         //LMH for cloud average
    {
        c = 'L';
    }
    else if (sum1 < 65)
    {
        c = 'M';
    }
    else if (sum1 < 100)
    {
        c = 'H';
    }

    if (sum2 < 35) //LMH for pressure average
    {
        p = 'L';
    }
    else if (sum2 < 65)
    {
        p = 'M';
    }
    else if (sum2 < 100)
    {
        p = 'H';
    }
    cout << "Probabilty of rain for the entire grid" << endl;
    rain_prob(c, p); //calls the rain prob function with the respective LMH
}