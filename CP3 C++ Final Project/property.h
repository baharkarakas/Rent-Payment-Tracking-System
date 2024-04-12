// property.h

#ifndef PROPERTY_H
#define PROPERTY_H

#include "real_estate.h"

// Forward declaration
class RentPayment;

// Enumeration for property specialization
enum PropertyType
{
    APARTMENT,
    HOUSE,
    CONDO,
    TOWNHOUSE,
    COMMERCIAL,
    OTHER
};

class Property : public RealEstate
{
private:
    PropertyType propertyType;
    static const int MAX_RENT_PAYMENTS = 10;

    int numberOfRentPayments = 2;

public:
    Property();
    Property(int _id, const std::string &_propertyName, PropertyType _propertyType);

    int getId() const;
    std::string getPropertyName() const;
    PropertyType getPropertyType() const;
    int getNumberOfRentPayments() const;

    void setId(int _id);
    void setPropertyName(const std::string &_propertyName);
    void setPropertyType(PropertyType _propertyType);
    void setNumberOfRentPayments(int _numberOfRentPayments);

    void incrementRentPayments();

    // Operator overloading
    friend bool operator<=(const Property &property, const RentPayment &rentPayment);

    void displayInfo();
};

#endif // PROPERTY_H