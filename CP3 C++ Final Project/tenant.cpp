// tenant.cpp

#include "tenant.h"
#include <iostream>

// Constructors
Tenant::Tenant() : RealEstate(0, ""), salary(0) {}

Tenant::Tenant(int _id, const std::string &_name, int _salary)
    : RealEstate(_id, _name), salary(_salary) {}

// Getter method for salary
int Tenant::getSalary() const
{
    return salary;
}

// Setter method for salary
void Tenant::setSalary(int _salary)
{
    salary = _salary;
}

// Display information about the tenant
void Tenant::displayInfo()
{
    std::cout << "Tenant ID: " << id << std::endl;
    std::cout << "Tenant Name: " << name << std::endl;
    std::cout << "Tenant Salary: " << salary << "k" << std::endl;
}