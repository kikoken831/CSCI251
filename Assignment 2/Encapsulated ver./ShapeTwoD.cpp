#include "ShapeTwoD.h"



using namespace std;

void ShapeTwoD::setName(string name) //name setter
{
    this->name = name;
}

void ShapeTwoD::setContainsWarpSpace(bool containsWarpSpace) //WS setter
{
    this->containsWarpSpace = containsWarpSpace;
}

string ShapeTwoD::getName() //name getter
{
    return name;
}
bool ShapeTwoD::getContainsWarpSpace() //WS getter
{
    return containsWarpSpace;
}