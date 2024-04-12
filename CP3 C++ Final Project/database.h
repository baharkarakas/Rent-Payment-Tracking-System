// Database.h

#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "property.h"
#include "tenant.h"
#include "rent_payment.h"

class Database
{
private:
    std::vector<Property> properties;
    std::vector<Tenant> tenants;
    std::vector<RentPayment> rentPayments;
    std::vector<RealEstate *> realEstates;

public:
    // Property Operations
    void addRealEstate();
    void addProperty(const Property &property);
    const std::vector<Property> &getAllProperties() const;
    void saveToFile(const std::string &filename) const;
    void loadFromFile(const std::string &filename);
    void deletePropertyAndRentPayments(int propertyId);
    void updateProperty(int propertyId, const Property &updatedProperty);
    void showAllProperties(const std::string &filename) const;

    // Tenant Operations
    void addTenant(const Tenant &tenant);
    const std::vector<Tenant> &getAllTenants() const;
    void saveTenantsToFile(const std::string &filename) const;
    void loadTenantsFromFile(const std::string &filename);
    void deleteTenantAndRentPayments(int tenantId);
    void updateTenant(int tenantId, const Tenant &updatedTenant);
    void showAllTenantsFromFile(const std::string &filename) const;
    void calculateAndPrintTenantStatistics(const std::vector<Tenant> &tenants);

    // RentPayment Operations
    void addRentPayment(const RentPayment &rentPayment);
    const std::vector<RentPayment> &getAllRentPayments() const;
    void saveRentPaymentsToFile(const std::string &filename) const;
    void loadRentPaymentsFromFile(const std::string &filename);
    void deleteRentPaymentById(int rentPaymentId);
    void updateRentPayment(int rentPaymentId, const RentPayment &updatedRentPayment);
    void showAllRentPaymentsFromFile(const std::string &filename);
};

#endif // DATABASE_H