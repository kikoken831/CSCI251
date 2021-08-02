#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string **array2D = nullptr;

void init2DArray(int, int);
void populate2DArray(int, int);
void display2DArray(int, int);
void safelyDeallocateMemory(int, int);

int main()
{
    int row, col = 0;
    cout << "Pls enter no. of cols : ";
    cin >> col;
    cout << "Pls enter no. of rows : ";
    cin >> row;
    
    init2DArray(col, row);
    populate2DArray(col, row);
    display2DArray(col, row);
    safelyDeallocateMemory(col, row);
}

void init2DArray(int col, int row)
{

    array2D = new string *[row];
    for (int i = 0; i < row; i++)
    {
        array2D[i] = new string [col];
    }
}
/*OG 1
void populate2DArray(int col, int row)
{
    

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            ostringstream os;
            os << "r" << i + 1 << "c" << j + 1;
            array2D[i][j] = os.str();
        }
    }
}

void display2DArray(int col, int row)
{

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << array2D[i][j] << ", ";
        }
        cout << endl;
    }
}
*/
void populate2DArray(int col, int row)
{
    

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            ostringstream os;
            os << "x" << j + 1 << "y" << i + 1;
            array2D[i][j] = os.str();
        }
    }
}
//ver 2 for X and Y
void display2DArray(int col, int row)
{

    for (int i = row-1; i >= 0; i--)
    {
        for (int j = 0; j < col; j++)
        {
            cout << array2D[i][j] << ", ";
        }
        cout << endl;
    }
}

void safelyDeallocateMemory(int col, int row)
{

    if (col <= 0)
        return;
    for ( int i = 0; i < row; i++)
    {
        delete [] array2D[i];
    }
    delete [] array2D;
}