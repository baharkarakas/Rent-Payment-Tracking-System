// realestate.h

#ifndef REALESTATE_H
#define REALESTATE_H

#include <iostream>
#include <string>

// RealEstate class (superclass)
class RealEstate
{
protected:
    int id;
    std::string name;

public:
    // Constructor for RealEstate
    RealEstate(int id, const std::string &name);

    // Getter methods
    int getId() const;
    std::string getName() const;

    // Setter methods
    void setId(int newId);
    void setName(const std::string &newName);

    // Virtual function to display information
    virtual void displayInfo() const;

    // Virtual destructor to support polymorphism
    virtual ~RealEstate() = default;
};

#endif // REALESTATE_H