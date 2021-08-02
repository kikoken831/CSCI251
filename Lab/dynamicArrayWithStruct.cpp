#include <iostream>
#include <string>

using namespace std;

struct Student
{
    string name;
    string addr;
};

typedef struct Student StudentType;

void displayArrayContents1(int, StudentType *);
void displayArrayContents2(int, struct Student *);
void safelyDeallocateMemory(int, StudentType *);

int main()
{
    StudentType * dynamicStructArrayPtr = nullptr;
    //struct Student * dynamicStructArrayPtr = nullptr;
    int arraySize = 0;

    cout << "Please enter no. of students : ";
    cin >> arraySize;

    cin.ignore(80, '\n');
    cout << endl;

    dynamicStructArrayPtr = new StudentType[arraySize];

    for (int i = 0; i < arraySize; i++)
    {
        StudentType temp;
        //struct Student temp;
        cout << "Please enter name of student #" << i + 1 << " : ";
        getline(cin, temp.name);
        cout << endl;
        cout << "Please enter address of student #" << i + 1 << " : ";
        getline(cin, temp.addr);
        cout << endl;
        cout << endl;
        dynamicStructArrayPtr[i] = temp;
    }
    
    displayArrayContents1(arraySize, dynamicStructArrayPtr);
    displayArrayContents2(arraySize, dynamicStructArrayPtr);
    safelyDeallocateMemory(arraySize, dynamicStructArrayPtr);
    cout << endl;
    return 0;
}

void displayArrayContents1(int arraySize, StudentType *dynamicStructArrayPtr)
{
    for (int i = 0; i < arraySize; i++)
    {
        cout << "Name: " << dynamicStructArrayPtr[i].name << "  Addr: " << dynamicStructArrayPtr[i].addr << endl;
    }
}
void displayArrayContents2(int arraySize, struct Student *dynamicStructArrayPtr)
{
    displayArrayContents1(arraySize, dynamicStructArrayPtr);
}
void safelyDeallocateMemory(int arraySize, StudentType *dynamicStructArrayPtr)
{
    delete [] dynamicStructArrayPtr;
}
