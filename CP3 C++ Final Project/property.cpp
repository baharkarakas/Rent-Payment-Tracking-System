// property.cpp

#include "property.h"
#include <iostream>

// Constructors
Property::Property() : RealEstate(0, ""), propertyType(PropertyType::OTHER) {}

Property::Property(int _id, const std::string &_propertyName, PropertyType _propertyType)
    : RealEstate(_id, _propertyName), propertyType(_propertyType) {}

// Getter methods
int Property::getId() const
{
    return RealEstate::getId();
}

std::string Property::getPropertyName() const
{
    return RealEstate::getName();
}

PropertyType Property::getPropertyType() const
{
    return propertyType;
}

int Property::getNumberOfRentPayments() const
{
    return numberOfRentPayments;
}

// Setter methods
void Property::setId(int _id)
{
    RealEstate::setId(_id);
}

void Property::setPropertyName(const std::string &_propertyName)
{
    RealEstate::setName(_propertyName);
}

void Property::setPropertyType(PropertyType _propertyType)
{
    propertyType = _propertyType;
}

void Property::setNumberOfRentPayments(int _numberOfRentPayments)
{
    numberOfRentPayments = _numberOfRentPayments;
}

void Property::incrementRentPayments()
{
    numberOfRentPayments++;
}

bool operator<=(const Property &property, const RentPayment &rentPayment)
{
    if (property.numberOfRentPayments < Property::MAX_RENT_PAYMENTS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Display information about the property
void Property::displayInfo()
{
    std::cout << "Property ID: " << getId() << std::endl;
    std::cout << "Property Name: " << getPropertyName() << std::endl;
    std::cout << "Property Type: ";

    switch (propertyType)
    {
    case PropertyType::APARTMENT:
        std::cout << "Apartment";
        break;
    case PropertyType::HOUSE:
        std::cout << "House";
        break;
    case PropertyType::CONDO:
        std::cout << "Condo";
        break;
    case PropertyType::TOWNHOUSE:
        std::cout << "Town House";
        break;
    case PropertyType::COMMERCIAL:
        std::cout << "Commercial";
        break;
    case PropertyType::OTHER:
        std::cout << "Other";
        break;
    }

    std::cout << std::endl;
}
