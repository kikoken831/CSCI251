#include <iostream>
#include <string>

using namespace std;

void displayArrayContents (int, string *, string *);
void safelyDeallocateMemory (int, string *, string *);

int main()
{
    string * dynamicNameArrayPtr = nullptr;
    string * dynamicAddrArrayPtr = nullptr;

    int arraySize = 0;

    cout << "Please enter no. of students : ";
    cin >> arraySize;

    cin.ignore (80, '\n');
    cout << endl;

    dynamicNameArrayPtr = new string [arraySize];
    dynamicAddrArrayPtr = new string [arraySize];

    for (int i = 0; i < arraySize; i++){
        cout << "Enter name of student : #" << i+1 << " : ";
        getline(cin,dynamicNameArrayPtr[i]);
        cout << endl; 
    }
    for (int i = 0; i < arraySize; i++){
        cout << "Enter address of student : #" << i+1 << " : ";
        getline(cin,dynamicAddrArrayPtr[i]);
        cout << endl; 
    }
    displayArrayContents (arraySize, dynamicNameArrayPtr,dynamicAddrArrayPtr);
    safelyDeallocateMemory (arraySize, dynamicNameArrayPtr,dynamicAddrArrayPtr);

    cout << endl;
    return 0;
}

void displayArrayContents (int as, string * nA, string * aA)
{
    for( int i = 0; i < as; i++)
    {
        cout << endl;
        cout << "Data of student : #" << i+1 << " : " << endl;

        if (nA != nullptr)
        {
            cout << "Name: " << nA[i] << "     Address: " << aA[i] << endl;
        }
    }
}

void safelyDeallocateMemory (int as, string * nA, string * aA)
{
    delete [] nA;
    delete [] aA;
}