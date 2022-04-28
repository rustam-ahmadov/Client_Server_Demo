#pragma once
#include <iostream>

class Person
{
private:
    std::string _name;
    int _age;

public:
    // Constructors
    Person() {}
    Person(const std::string name, const int age);

    // Setters
    void Set_Name(const std::string name);
    void Set_Age(int age);

    // Getters
    std::string Get_Name();
    int Get_Age();
};