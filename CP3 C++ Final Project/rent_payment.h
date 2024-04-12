// RentPayment.h

#include "property.h"
#include "tenant.h"

class RentPayment
{
private:
    int id;
    Property property;
    Tenant tenant;
    int hour;
    int day;
    int month;
    int year;

public:
    RentPayment() : id(0), hour(0), day(0), month(0), year(0) {}

    RentPayment(int _id, const Property &_property, const Tenant &_tenant, int _hour, int _day, int _month, int _year)
        : id(_id), property(_property), tenant(_tenant), hour(_hour), day(_day), month(_month), year(_year) {}

    int getId() const { return id; }
    const Property &getProperty() const { return property; }
    const Tenant &getTenant() const { return tenant; }
    int getHour() const { return hour; }
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    void setId(int _id) { id = _id; }
    void setProperty(const Property &_property) { property = _property; }
    void setTenant(const Tenant &_tenant) { tenant = _tenant; }
    void setHour(int _hour) { hour = _hour; }
    void setDay(int _day) { day = _day; }
    void setMonth(int _month) { month = _month; }
    void setYear(int _year) { year = _year; }

    friend bool operator<=(const Property &property, const RentPayment &rentPayment);

    void displayInfo()
    {
        std::cout << "RentPayment ID: " << id << std::endl;
        std::cout << "Property Information:" << std::endl;
        property.displayInfo();
        std::cout << "Tenant Information:" << std::endl;
        tenant.displayInfo();
        std::cout << "Date and Time: " << day << "/" << month << "/" << year << " at " << hour << ":00" << std::endl;
    }
};