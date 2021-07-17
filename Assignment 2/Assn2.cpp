#include <iostream>
#include <string>
using namespace std;
class Shape2D{
protected:
    string name;
    bool containsWarpSpace;
public:
    inline Shape2D(){name = "N/A";containsWarpSpace = false;}
        
        
    Shape2D(string name, bool containsWarpSpace)
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
    string toString()
    {
        return " ";
    }

    double computeArea()
    {
        return 0;
    }
    bool isPointInShape(int x, int y)
    {
        return true;
    }
    bool isPointOnShape(int x, int y)
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


int main(){
    return 0;
}