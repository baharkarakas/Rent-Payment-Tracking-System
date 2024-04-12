

#include <iostream>
#include <algorithm>
#include "database.cpp"
#include "property.cpp"
#include "real_estate.cpp"
#include "tenant.cpp"

int main()
{

    // Create an instance of the Database class
    Database myDatabase;

    myDatabase.addRealEstate();

    int choice;
    int subchoice;
    do
    {

        std::cout << "\n==== Main Menu ====\n";
        std::cout << "1. Property Operations\n";
        std::cout << "2. Tenant Operations\n";
        std::cout << "3. RentPayment Operations\n";
        std::cout << "4. Display All RealEstates\n";
        std::cout << "5. Exit\n";
        std::cin >> choice;

        switch (choice)
        {

        case 1:

            do
            {

                std::cout << "\n==== Property Management ====\n";
                std::cout << "1. Add Property\n";
                std::cout << "2. Delete Property\n";
                std::cout << "3. Update Property\n";
                std::cout << "4. Show All Properties\n";
                std::cout << "5. Exit\n";
                std::cout << "Enter your choice: ";
                std::cin >> subchoice;

                switch (subchoice)
                {
                case 1:
                    // Add a new property
                    {
                        int id;
                        std::string name;
                        int type;

                        std::cout << "Enter Property ID: ";
                        std::cin >> id;

                        std::cout << "Enter Property Name: ";
                        std::cin.ignore();
                        std::getline(std::cin, name);

                        std::cout << "Enter Type (as an integer):\n"
                                  << "0. APARTMENT\n"
                                  << "1. HOUSE\n"
                                  << "2. CONDO\n"
                                  << "3. TOWNHOUSE\n"
                                  << "4. COMMERCIAL\n"
                                  << "5. OTHER\n";
                        std::cin >> type;

                        PropertyType propType = static_cast<PropertyType>(type);

                        Property newProperty(id, name, propType);
                        myDatabase.addProperty(newProperty);
                    }
                    break;

                case 2:
                    // Delete a property
                    {
                        int id;
                        std::cout << "Enter the ID of the property to delete: ";
                        std::cin >> id;
                        myDatabase.deletePropertyAndRentPayments(id);
                    }
                    break;

                case 3:
                    // Update a property
                    {
                        int id;
                        std::cout << "Enter the ID of the property to update: ";
                        std::cin >> id;

                        // Fetch the existing property information
                        auto existingProperties = myDatabase.getAllProperties();
                        auto it = std::find_if(existingProperties.begin(), existingProperties.end(),
                                               [id](const Property &property)
                                               { return property.getId() == id; });

                        if (it != existingProperties.end())
                        {
                            // Input updated information
                            std::string name;
                            int type;

                            std::cout << "Enter Updated Property Name: ";
                            std::cin.ignore(); // Ignore newline in the buffer
                            std::getline(std::cin, name);

                            std::cout << "Enter Type (as an integer):\n"
                                      << "0. APARTMENT\n"
                                      << "1. HOUSE\n"
                                      << "2. CONDO\n"
                                      << "3. TOWNHOUSE\n"
                                      << "4. COMMERCIAL\n"
                                      << "5. OTHER\n";
                            std::cin >> type;

                            PropertyType propType = static_cast<PropertyType>(type);

                            Property updatedProperty(id, name, propType);
                            myDatabase.updateProperty(id, updatedProperty);
                        }
                        else
                        {
                            std::cout << "Property with ID " << id << " not found." << std::endl;
                        }
                    }
                    break;

                case 4:
                    // Show all properties
                    myDatabase.showAllProperties("properties.txt");
                    break;

                case 5:
                    std::cout << "Exiting...\n";
                    break;

                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    break;
                }

            } while (subchoice != 5);
            break;

        case 2:

            int tenantChoice;

            do
            {

                std::cout << "\n==== Tenant Management ====\n";
                std::cout << "1. Add Tenant\n";
                std::cout << "2. Delete Tenant\n";
                std::cout << "3. Update Tenant\n";
                std::cout << "4. Show All Tenants\n";
                std::cout << "5. Back to Main Menu\n";
                std::cout << "Enter your choice: ";
                std::cin >> tenantChoice;

                switch (tenantChoice)
                {
                case 1:
                    // Add a new tenant
                    {
                        int id;
                        std::string name;
                        int salary;

                        std::cout << "Enter Tenant ID: ";
                        std::cin >> id;

                        std::cout << "Enter Tenant Name: ";
                        std::cin.ignore(); // Ignore newline in the buffer
                        std::getline(std::cin, name);

                        std::cout << "Enter Tenant Salary: ";
                        std::cin >> salary;

                        Tenant newTenant(id, name, salary);
                        myDatabase.addTenant(newTenant);
                    }
                    break;

                case 2:
                    // Delete a tenant
                    {
                        int id;
                        std::cout << "Enter the ID of the tenant to delete: ";
                        std::cin >> id;
                        myDatabase.deleteTenantAndRentPayments(id);
                    }
                    break;

                case 3:
                    // Update a tenant
                    {
                        int id;
                        std::cout << "Enter the ID of the tenant to update: ";
                        std::cin >> id;

                        // Fetch the existing tenant information
                        auto existingTenants = myDatabase.getAllTenants();
                        auto it = std::find_if(existingTenants.begin(), existingTenants.end(),
                                               [id](const Tenant &tenant)
                                               { return tenant.getId() == id; });

                        if (it != existingTenants.end())
                        {
                            // Input updated information
                            std::string name;
                            int salary;

                            std::cout << "Enter Updated Tenant Name: ";
                            std::cin.ignore(); // Ignore newline in the buffer
                            std::getline(std::cin, name);

                            std::cout << "Enter Updated Tenant Salary: ";
                            std::cin >> salary;

                            Tenant updatedTenant(id, name, salary);
                            myDatabase.updateTenant(id, updatedTenant);
                        }
                        else
                        {
                            std::cout << "Tenant with ID " << id << " not found." << std::endl;
                        }
                    }
                    break;

                case 4:
                    // Show all tenants
                    myDatabase.showAllTenantsFromFile("tenants.txt");
                    myDatabase.calculateAndPrintTenantStatistics(myDatabase.getAllTenants());
                    break;

                case 5:
                    std::cout << "Returning to Main Menu...\n";
                    break;

                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    break;
                }

            } while (tenantChoice != 5);
            break;

        case 3:

            int rentPaymentChoice;

            do
            {
                // Display rent payment menu
                std::cout << "\n==== RentPayment Management ====\n";
                std::cout << "1. Add RentPayment\n";
                std::cout << "2. Delete RentPayment\n";
                std::cout << "3. Update RentPayment\n";
                std::cout << "4. Show All RentPayments\n";
                std::cout << "5. Back to Main Menu\n";
                std::cout << "Enter your choice: ";
                std::cin >> rentPaymentChoice;

                switch (rentPaymentChoice)
                {
                case 1:
                    // Add a new rent payment
                    {
                        int id;
                        int propertyId;
                        int tenantId;
                        int hour;
                        int day;
                        int month;
                        int year;

                        std::cout << "Enter RentPayment ID: ";
                        std::cin >> id;

                        std::cout << "Enter Property ID: ";
                        std::cin >> propertyId;

                        std::cout << "Enter Tenant ID: ";
                        std::cin >> tenantId;

                        std::cout << "Enter Hour: ";
                        std::cin >> hour;

                        std::cout << "Enter Day: ";
                        std::cin >> day;

                        std::cout << "Enter Month: ";
                        std::cin >> month;

                        std::cout << "Enter Year: ";
                        std::cin >> year;

                        // Fetch the property and tenant objects from their respective vectors
                        auto propertyIt = std::find_if(myDatabase.getAllProperties().begin(), myDatabase.getAllProperties().end(),
                                                       [propertyId](const Property &property)
                                                       { return property.getId() == propertyId; });

                        auto tenantIt = std::find_if(myDatabase.getAllTenants().begin(), myDatabase.getAllTenants().end(),
                                                     [tenantId](const Tenant &tenant)
                                                     { return tenant.getId() == tenantId; });

                        if (propertyIt != myDatabase.getAllProperties().end() && tenantIt != myDatabase.getAllTenants().end())
                        {
                            Property property = *propertyIt;
                            Tenant tenant = *tenantIt;

                            RentPayment newRentPayment(id, property, tenant, hour, day, month, year);

                            if(operator<=(newRentPayment.getProperty(),newRentPayment)){

                              myDatabase.addRentPayment(newRentPayment);

                            }
                            else
                            {
                                std::cout << "Maximum rent payment limit for this property is exceeded\n";
                            }
                            
                        }
                        else
                        {
                            std::cout << "Property or Tenant with ID not found. Please make sure they exist.\n";
                        }
                    }
                    break;

                case 2:
                    // Delete a rent payment
                    {
                        int id;
                        std::cout << "Enter the ID of the rent payment to delete: ";
                        std::cin >> id;
                        myDatabase.deleteRentPaymentById(id);
                    }
                    break;

                case 3:
                    // Update a rent payment
                    {
                        int id;
                        std::cout << "Enter the ID of the rent payment to update: ";
                        std::cin >> id;

                        // Fetch the existing rent payment information
                        auto existingRentPayments = myDatabase.getAllRentPayments();
                        auto it = std::find_if(existingRentPayments.begin(), existingRentPayments.end(),
                                               [id](const RentPayment &rentPayment)
                                               { return rentPayment.getId() == id; });

                        if (it != existingRentPayments.end())
                        {
                            // Input updated information

                            int propertyId;
                            int tenantId;
                            int hour;
                            int day;
                            int month;
                            int year;

                            std::cout << "Enter Updated Property ID: ";
                            std::cin >> propertyId;

                            std::cout << "Enter Updated Tenant ID: ";
                            std::cin >> tenantId;

                            std::cout << "Enter Updated Hour: ";
                            std::cin >> hour;

                            std::cout << "Enter Updated Day: ";
                            std::cin >> day;

                            std::cout << "Enter Updated Month: ";
                            std::cin >> month;

                            std::cout << "Enter Updated Year: ";
                            std::cin >> year;

                            // Fetch the property and tenant objects from their respective vectors
                            auto propertyIt = std::find_if(myDatabase.getAllProperties().begin(), myDatabase.getAllProperties().end(),
                                                           [propertyId](const Property &property)
                                                           { return property.getId() == propertyId; });

                            auto tenantIt = std::find_if(myDatabase.getAllTenants().begin(), myDatabase.getAllTenants().end(),
                                                         [tenantId](const Tenant &tenant)
                                                         { return tenant.getId() == tenantId; });

                            if (propertyIt != myDatabase.getAllProperties().end() && tenantIt != myDatabase.getAllTenants().end())
                            {
                                Property property = *propertyIt;
                                Tenant tenant = *tenantIt;

                                RentPayment updatedRentPayment(id, property, tenant, hour, day, month, year);
                                myDatabase.updateRentPayment(id, updatedRentPayment);
                            }
                            else
                            {
                                std::cout << "Property or Tenant with ID not found. Please make sure they exist.\n";
                            }
                        }
                        else
                        {
                            std::cout << "RentPayment with ID " << id << " not found.\n";
                        }
                    }
                    break;

                case 4:
                    // Show all rent payments
                    myDatabase.showAllRentPaymentsFromFile("rentpayments.txt");
                    break;

                case 5:
                    std::cout << "Returning to Main Menu...\n";
                    break;

                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    break;
                }

            } while (rentPaymentChoice != 5);
            break;

        case 4:
            myDatabase.displayAllRealEstates(myDatabase.getAllRealEstates());

        case 5:

            std::cout << "Exiting...\n";
            break;

        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }

    } while (choice != 5);
}