#include "real_estate.h"
#include <iostream>

// Constructor for RealEstate
RealEstate::RealEstate(int _id, const std::string &_name) : id(_id), name(_name) {}

// Getter methods
int RealEstate::getId() const
{
    return id;
}

std::string RealEstate::getName() const
{
    return name;
}

// Setter methods
void RealEstate::setId(int newId)
{
    id = newId;
}

void RealEstate::setName(const std::string &newName)
{
    name = newName;
}

// Virtual function to display information
void RealEstate::displayInfo() const
{
    std::cout << "ID: " << id << "\nName: " << name << std::endl;
}

