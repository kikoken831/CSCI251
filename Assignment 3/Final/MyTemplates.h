#ifndef MYTEMPLATES_H
#define MYTEMPLATES_H
template<typename T, typename N>
double scalar_difference(T lhs , N rhs)//gets the abs value of length or distance
{
    return abs(lhs.getScalarValue() - rhs.getScalarValue());//use getters to get the absolute difference
}

template<typename T, typename N>//test if both objects are equal
bool equals(T lhs , N rhs)
{
    return (lhs == rhs);//all classes overloaded, ready to use
}

#endif