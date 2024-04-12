// Tenant.h

#ifndef TENANT_H
#define TENANT_H

#include <iostream>
#include <string>
#include "real_estate.h"

class Tenant : public RealEstate
{
private:
    int salary;

public:
    Tenant();
    Tenant(int _id, const std::string &_name, int _salary);

    int getSalary() const;

    void setSalary(int _salary);

    void displayInfo();
};

#endif // TENANT_H