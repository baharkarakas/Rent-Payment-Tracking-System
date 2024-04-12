
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "real_estate.h"
#include "property.h"
#include "tenant.h"
#include "rent_payment.h"
#include <algorithm>

class Database
{
private:
    std::vector<Property> properties;
    std::vector<Tenant> tenants;
    std::vector<RentPayment> rentPayments;
    std::vector<RealEstate *> realEstates;

public:
    void addRealEstate()
    {
        // Create 3 properties
        realEstates.push_back(new Property(1, "Serenity Haven", PropertyType::HOUSE));
        realEstates.push_back(new Property(2, "Whispering Pines House", PropertyType::TOWNHOUSE));
        realEstates.push_back(new Property(3, "Cherry Blossom Cottage", PropertyType::CONDO));

        properties.push_back(Property(1, "Serenity Haven", PropertyType::COMMERCIAL));
        properties.push_back(Property(2, "Whispering Pines House", PropertyType::OTHER));
        properties.push_back(Property(3, "Cherry Blossom Cottage", PropertyType::APARTMENT));

        // Create 6 tenants
        realEstates.push_back(new Tenant(1, "Ethan Reynolds", 2));
        realEstates.push_back(new Tenant(2, "Olivia Foster", 5));
        realEstates.push_back(new Tenant(3, "Aaron Patel", 10));
        realEstates.push_back(new Tenant(4, "Ava Baker", 25));
        realEstates.push_back(new Tenant(5, "Gabriel Martinez", 17));
        realEstates.push_back(new Tenant(6, "Sophia Nguyen", 8));

        tenants.push_back(Tenant(1, "Ethan Reynolds", 2));
        tenants.push_back(Tenant(2, "Olivia Foster", 5));
        tenants.push_back(Tenant(3, "Aaron Patel", 10));
        tenants.push_back(Tenant(4, "Ava Baker", 25));
        tenants.push_back(Tenant(5, "Gabriel Martinez", 17));
        tenants.push_back(Tenant(6, "Sophia Nguyen", 8));

        // Create rentpayments with fixed dates
        rentPayments.push_back(RentPayment(1, properties[0], tenants[0], 9, 10, 1, 2023));
        rentPayments.push_back(RentPayment(2, properties[1], tenants[1], 14, 15, 2, 2023));
        rentPayments.push_back(RentPayment(3, properties[2], tenants[2], 11, 20, 3, 2023));
        rentPayments.push_back(RentPayment(4, properties[0], tenants[3], 15, 5, 4, 2023));
        rentPayments.push_back(RentPayment(5, properties[1], tenants[4], 10, 1, 5, 2023));
        rentPayments.push_back(RentPayment(6, properties[2], tenants[5], 13, 8, 6, 2023));
    }

    // Add a property to the database
    void addProperty(const Property &property)
    {
        // Check if the ID is already in use
        if (std::find_if(properties.begin(), properties.end(),
                         [id = property.getId()](const Property &p)
                         { return p.getId() == id; }) != properties.end())
        {
            std::cerr << "Error: Property with ID " << property.getId() << " already exists in the database." << std::endl;
        }
        else
        {
            // Add the property to the vector
            properties.push_back(property);
            realEstates.push_back(new Property(property));

            // Update the file after adding the property
            saveToFile("properties.txt");

            std::cout << "Property with ID " << property.getId() << " added to the database and file." << std::endl;
        }
    }

    // Retrieve all properties from the database
    const std::vector<Property> &getAllProperties() const
    {
        return properties;
    }

    const std::vector<RealEstate *> &getAllRealEstates() const
    {
        return realEstates;
    }

    // Other methods for managing properties can be added here

    void saveToFile(const std::string &filename) const
    {
        std::ofstream outFile(filename);

        if (outFile.is_open())
        {
            for (const auto &property : properties)
            {
                outFile << property.getId() << ","
                        << property.getPropertyName() << ","
                        << static_cast<int>(property.getPropertyType()) << "\n";
            }

            outFile.close();
            std::cout << "Properties saved to file: " << filename << std::endl;
        }
        else
        {
            std::cerr << "Error: Unable to open file for writing: " << filename << std::endl;
        }
    }

    void loadFromFile(const std::string &filename)
    {
        properties.clear(); // Clear existing properties before loading from file

        std::ifstream inFile(filename);

        if (inFile.is_open())
        {
            int id;
            std::string propertyName;
            int propertyType;

            while (inFile >> id >> std::ws && std::getline(inFile, propertyName, ',') && inFile >> propertyType)
            {
                PropertyType spec = static_cast<PropertyType>(propertyType);
                properties.emplace_back(id, propertyName, spec);
            }

            inFile.close();
            std::cout << "Properties loaded from file: " << filename << std::endl;
        }
        else
        {
            std::cerr << "Error: Unable to open file for reading: " << filename << std::endl;
        }
    }

    void deletePropertyAndRentPayments(int propertyId)
    {
        // Remove the property from the vector
        auto propertyIt = std::remove_if(
            properties.begin(), properties.end(),
            [propertyId](const Property &property)
            { return property.getId() == propertyId; });
            
 bool propertyRemoved = (propertyIt != properties.end());

        properties.erase(propertyIt, properties.end());

        // Update the file after removing the property
        saveToFile("properties.txt");

        if (propertyRemoved)
        {
            // Get the deleted property
            Property deletedProperty = *propertyIt;

            // Remove the property's rentpayments from the vector
            rentPayments.erase(
                std::remove_if(
                    rentPayments.begin(), rentPayments.end(),
                    [propertyId](const RentPayment &rentpayment)
                    { return rentpayment.getProperty().getId() == propertyId; }),
                rentPayments.end());

            // Update the file after removing the rentpayments
            saveRentPaymentsToFile("rentpayments.txt");

            std::cout << "Property with ID " << propertyId << " and associated rentpayments deleted from the database and file." << std::endl;
        }
        else
        {
            std::cerr << "Error: Property with ID " << propertyId << " not found in the database." << std::endl;
        }
    }

    void updateProperty(int propertyId, const Property &updatedProperty)
    {
        // Find the property in the vector
        auto it = std::find_if(
            properties.begin(), properties.end(),
            [propertyId](const Property &property)
            { return property.getId() == propertyId; });

        if (it != properties.end())
        {
            // Update the property in the vector
            *it = updatedProperty;

            // Update the file after modifying the property
            saveToFile("properties.txt");

            std::cout << "Property with ID " << propertyId << " updated in the database and file." << std::endl;
        }
        else
        {
            std::cerr << "Error: Property with ID " << propertyId << " not found in the database." << std::endl;
        }
    }

    void showAllProperties(const std::string &filename) const
    {
        std::cout << "All Properties in the Database:" << std::endl;

        for (Property property : properties)
        {
            property.displayInfo();
            std::cout << std::endl;
        }
    }

    void displayAllRealEstates(const std::vector<RealEstate *> &realEstates)
    {
        for (const RealEstate *realEstate : realEstates)
        {
            realEstate->displayInfo();
        }
    }

    // Tenant Operations
    // Save all tenants to a file
    void saveTenantsToFile(const std::string &filename) const
    {
        std::ofstream outFile(filename);

        if (outFile.is_open())
        {
            for (const auto &tenant : tenants)
            {
                outFile << tenant.getId() << ","
                        << tenant.getName() << ","
                        << tenant.getSalary() << "\n";
            }

            outFile.close();
            std::cout << "Tenants saved to file: " << filename << std::endl;
        }
        else
        {
            std::cerr << "Error: Unable to open file for writing: " << filename << std::endl;
        }
    }

    void loadTenantsFromFile(const std::string &filename)
    {
        tenants.clear(); // Clear existing tenants before loading from file

        std::ifstream inFile(filename);

        if (inFile.is_open())
        {
            int id;
            std::string tenantName;
            int salary;

            while (inFile >> id >> std::ws && std::getline(inFile, tenantName, ',') && inFile >> salary)
            {
                tenants.emplace_back(id, tenantName, salary);
            }

            inFile.close();
            std::cout << "Tenants loaded from file: " << filename << std::endl;
        }
        else
        {
            std::cerr << "Error: Unable to open file for reading: " << filename << std::endl;
        }
    }

    void addTenant(const Tenant &tenant)
    {
        // Check if the ID is already in use
        if (std::find_if(tenants.begin(), tenants.end(),
                         [id = tenant.getId()](const Tenant &t)
                         { return t.getId() == id; }) != tenants.end())
        {
            std::cerr << "Error: Tenant with ID " << tenant.getId() << " already exists in the database." << std::endl;
        }
        else
        {
            // Add the tenant to the vector
            tenants.push_back(tenant);
            realEstates.push_back(new Tenant(tenant));

            // Update the file after adding the tenant
            // Assuming you have a saveToFile method similar to the one for properties
            // saveToFile("tenants.txt");
            saveTenantsToFile("tenants.txt");

            std::cout << "Tenant with ID " << tenant.getId() << " added to the database." << std::endl;
        }
    }
    const std::vector<Tenant> &getAllTenants() const
    {
        return tenants;
    }

    void deleteTenantAndRentPayments(int tenantId)
    {
        // Remove the tenant from the vector
        auto tenantIt = std::remove_if(
            tenants.begin(), tenants.end(),
            [tenantId](const Tenant &tenant)
            { return tenant.getId() == tenantId; });
             bool tenantRemoved = (tenantIt != tenants.end());

        tenants.erase(tenantIt, tenants.end());
        // Update the file after removing the tenant
        saveTenantsToFile("tenants.txt");

        if (tenantRemoved)
        {
            // Get the deleted tenant
            Tenant deletedTenant = *tenantIt;

            // Remove the tenant's rentpayments from the vector
            rentPayments.erase(
                std::remove_if(
                    rentPayments.begin(), rentPayments.end(),
                    [tenantId](const RentPayment &rentpayment)
                    { return rentpayment.getTenant().getId() == tenantId; }),
                rentPayments.end());

            // Update the file after removing the rentpayments
            saveRentPaymentsToFile("rentpayments.txt");

            std::cout << "Tenant with ID " << tenantId << " and associated rentpayments deleted from the database and file." << std::endl;
        }
        else
        {
            std::cerr << "Error: Tenant with ID " << tenantId << " not found in the database." << std::endl;
        }
    }

    void updateTenant(int tenantId, const Tenant &updatedTenant)
    {
        // Find the tenant in the vector
        auto it = std::find_if(
            tenants.begin(), tenants.end(),
            [tenantId](const Tenant &tenant)
            { return tenant.getId() == tenantId; });

        if (it != tenants.end())
        {
            // Update the tenant in the vector
            *it = updatedTenant;

            // Update the file after modifying the tenant
            // Assuming you have a saveToFile method similar to the one for properties
            // saveToFile("tenants.txt");
            saveTenantsToFile("tenants.txt");

            std::cout << "Tenant with ID " << tenantId << " updated in the database." << std::endl;
        }
        else
        {
            std::cerr << "Error: Tenant with ID " << tenantId << " not found in the database." << std::endl;
        }
    }

    void showAllTenantsFromFile(const std::string &filename) const
    {
        std::cout << "All Tenants in the Database:" << std::endl;

        for (Tenant tenant : tenants)
        {
            tenant.displayInfo();
            std::cout << std::endl;
        }
    }

    void calculateAndPrintTenantStatistics(const std::vector<Tenant> &tenants)
    {
        if (tenants.empty())
        {
            std::cerr << "Error: Empty vector of tenants." << std::endl;
            return;
        }

        // Allocate memory for an array of Tenant pointers using malloc
        Tenant **tenantArray = static_cast<Tenant **>(malloc(tenants.size() * sizeof(Tenant *)));

        // Populate the array with pointers to Tenant objects
        for (size_t i = 0; i < tenants.size(); ++i)
        {
            tenantArray[i] = new Tenant(tenants[i]);
        }

        // Calculate statistics
        int totalSalary = 0;
        for (size_t i = 0; i < tenants.size(); ++i)
        {
            totalSalary += tenantArray[i]->getSalary();
        }

        double averageSalary = static_cast<double>(totalSalary) / tenants.size();
        int numberOfTenants = tenants.size();

        // Output statistics
        std::cout << "Number of Tenants: " << numberOfTenants << std::endl;
        std::cout << "Average Salary of Tenants: " << averageSalary << "k" << std::endl;

        // Deallocate memory using free
        for (size_t i = 0; i < tenants.size(); ++i)
        {
            delete tenantArray[i];
        }
        free(tenantArray);
    }

    // RentPayments operations

    void addRentPayment(RentPayment &rentPayment)
    {
        // Check if the RentPayment with the same date already exists in the database
        if (std::find_if(rentPayments.begin(), rentPayments.end(),
                         [rentPayment](const RentPayment &rp)
                         {
                             return rp.getHour() == rentPayment.getHour() &&
                                    rp.getDay() == rentPayment.getDay() &&
                                    rp.getMonth() == rentPayment.getMonth() &&
                                    rp.getYear() == rentPayment.getYear();
                         }) != rentPayments.end())
        {
            std::cerr << "Error: RentPayment with the same date already exists in the database." << std::endl;
        }
        // Check if the ID is already in use
        else if (std::find_if(rentPayments.begin(), rentPayments.end(),
                              [id = rentPayment.getId()](const RentPayment &rp)
                              { return rp.getId() == id; }) != rentPayments.end())
        {
            std::cerr << "Error: RentPayment with ID " << rentPayment.getId() << " already exists in the database." << std::endl;
        }
        else
        {
            // Add the RentPayment to the vector
            rentPayments.push_back(rentPayment);

            // Update the file after adding the RentPayment
            saveRentPaymentsToFile("rentPayments.txt");

            std::cout << "RentPayment with ID " << rentPayment.getId() << " added to the database and file." << std::endl;

            Property property = rentPayment.getProperty();
            property.incrementRentPayments();
        }
    }

    const std::vector<RentPayment> &getAllRentPayments() const
    {
        return rentPayments;
    }

    void saveRentPaymentsToFile(const std::string &filename) const
    {
        std::ofstream outFile(filename);

        if (outFile.is_open())
        {
            for (const auto &rentPayment : rentPayments)
            {
                outFile << rentPayment.getId() << ","
                        << rentPayment.getProperty().getId() << ","
                        << rentPayment.getTenant().getId() << ","
                        << rentPayment.getHour() << ","
                        << rentPayment.getDay() << ","
                        << rentPayment.getMonth() << ","
                        << rentPayment.getYear() << "\n";
            }

            outFile.close();
            std::cout << "RentPayments saved to file: " << filename << std::endl;
        }
        else
        {
            std::cerr << "Error: Unable to open file for writing: " << filename << std::endl;
        }
    }

    void loadRentPaymentsFromFile(const std::string &filename)
    {
        rentPayments.clear(); // Clear existing RentPayments before loading from file

        std::ifstream inFile(filename);

        if (inFile.is_open())
        {
            int id;
            int propertyId;
            int tenantId;
            int hour;
            int day;
            int month;
            int year;

            while (inFile >> id >> std::ws && inFile >> propertyId >> std::ws && inFile >> tenantId >> std::ws &&
                   inFile >> hour >> std::ws && inFile >> day >> std::ws && inFile >> month >> std::ws && inFile >> year)
            {
                // Retrieve property and tenant objects from their respective vectors
                auto propertyIt = std::find_if(properties.begin(), properties.end(),
                                               [propertyId](const Property &property)
                                               { return property.getId() == propertyId; });

                auto tenantIt = std::find_if(tenants.begin(), tenants.end(),
                                             [tenantId](const Tenant &tenant)
                                             { return tenant.getId() == tenantId; });

                if (propertyIt != properties.end() && tenantIt != tenants.end())
                {
                    Property property = *propertyIt;
                    Tenant tenant = *tenantIt;

                    rentPayments.emplace_back(id, property, tenant, hour, day, month, year);
                }
            }

            inFile.close();
            std::cout << "RentPayments loaded from file: " << filename << std::endl;
        }
        else
        {
            std::cerr << "Error: Unable to open file for reading: " << filename << std::endl;
        }
    }

    void deleteRentPaymentById(int rentPaymentId)
    {
        // Remove the RentPayment from the vector
        auto rentPaymentIt = std::remove_if(
            rentPayments.begin(), rentPayments.end(),
            [rentPaymentId](const RentPayment &rentPayment)
            { return rentPayment.getId() == rentPaymentId; });

        rentPayments.erase(rentPaymentIt, rentPayments.end());

        // Update the file after removing the RentPayment
        saveRentPaymentsToFile("rentPayments.txt");

        std::cout << "RentPayment with ID " << rentPaymentId << " deleted from the database and file." << std::endl;
    }

    void updateRentPayment(int rentPaymentId, const RentPayment &updatedRentPayment)
    {
        // Find the RentPayment in the vector
        auto it = std::find_if(
            rentPayments.begin(), rentPayments.end(),
            [rentPaymentId](const RentPayment &rentPayment)
            { return rentPayment.getId() == rentPaymentId; });

        if (it != rentPayments.end())
        {
            // Update the RentPayment in the vector
            *it = updatedRentPayment;

            // Update the file after modifying the RentPayment
            saveRentPaymentsToFile("rentPayments.txt");

            std::cout << "RentPayment with ID " << rentPaymentId << " updated in the database and file." << std::endl;
        }
        else
        {
            std::cerr << "Error: RentPayment with ID " << rentPaymentId << " not found in the database." << std::endl;
        }
    }

    void showAllRentPaymentsFromFile(const std::string &filename) const
    {
        std::cout << "All Properties in the Database:" << std::endl;

        for (RentPayment rentPayment : rentPayments)
        {
            rentPayment.displayInfo();
            std::cout << std::endl;
        }
    }
};