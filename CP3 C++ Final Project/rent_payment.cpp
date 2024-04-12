// rentpayment.cpp

#include "rent_payment.h"
#include <iostream>

// Constructors
RentPayment::RentPayment() : id(0), hour(0), day(0), month(0), year(0) {}

RentPayment::RentPayment(int _id, const Property &_property, const Tenant &_tenant, int _hour, int _day, int _month, int _year)
    : id(_id), property(_property), tenant(_tenant), hour(_hour), day(_day), month(_month), year(_year) {}

// Getter methods
int RentPayment::getId() const
{
    return id;
}

const Property &RentPayment::getProperty() const
{
    return property;
}

const Tenant &RentPayment::getTenant() const
{
    return tenant;
}

int RentPayment::getHour() const
{
    return hour;
}

int RentPayment::getDay() const
{
    return day;
}

int RentPayment::getMonth() const
{
    return month;
}

int RentPayment::getYear() const
{
    return year;
}

// Setter methods
void RentPayment::setId(int _id)
{
    id = _id;
}

void RentPayment::setProperty(const Property &_property)
{
    property = _property;
}

void RentPayment::setTenant(const Tenant &_tenant)
{
    tenant = _tenant;
}

void RentPayment::setHour(int _hour)
{
    hour = _hour;
}

void RentPayment::setDay(int _day)
{
    day = _day;
}

void RentPayment::setMonth(int _month)
{
    month = _month;
}

void RentPayment::setYear(int _year)
{
    year = _year;
}

// Display information about the rent payment
void RentPayment::displayInfo()
{
    std::cout << "RentPayment ID: " << id << std::endl;
    std::cout << "Property Information:" << std::endl;
    property.displayInfo();
    std::cout << "Tenant Information:" << std::endl;
    tenant.displayInfo();
    std::cout << "Date and Time: " << day << "/" << month << "/" << year << " at " << hour << ":00" << std::endl;
}