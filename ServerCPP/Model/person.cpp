#include "person.h"

Person::Person(const std::string name, const int age)
{
    _name = name;
    _age = age;
}
void Person::Set_Name(const std::string name)
{
    _name = name;
}
std::string Person::Get_Name()
{
    return _name;
}
void Person::Set_Age(int age)
{
    _age = age;
}
int Person::Get_Age()
{
    return _age;
}