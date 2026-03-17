/*
 * @file Facade.cpp
 * @brief Implementation of the Facade design pattern in C++14.
 * @details This file demonstrates the Facade pattern, which provides a simplified interface to a complex subsystem. The `Facade` class encapsulates a set of interfaces in a single interface, making it easier for clients to use the subsystem.
 * @author Sergey Petrov
 * @date 2026-03-17
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class ProviderComunication // Class representing communication with a provider, which is part of the complex subsystem that the Facade will simplify
{
public:
    void receiveData() // Method to receive data from the provider, which will be called by the Facade
    {
        cout << "Receiving data from provider..." << endl;
    }
    void updateData() // Method to update data for the provider, which will be called by the Facade
    {
        cout << "Updating data for provider..." << endl;
    }
};

class SiteComunication // Class representing communication with a site, which is part of the complex subsystem that the Facade will simplify
{
public:
    void activationData() // Method to activate data for the site, which will be called by the Facade
    {
        cout << "Activating data for site..." << endl;
    }
    void eraseData() // Method to erase data from the site, which will be called by the Facade
    {
        cout << "Erasing data from site..." << endl;
    }
};

class DatabaseComunication // Class representing communication with a database, which is part of the complex subsystem that the Facade will simplify
{
public:
    void storeData() // Method to store data in the database, which will be called by the Facade
    {
        cout << "Storing data in database..." << endl;
    }
    void updateData() // Method to update data in the database, which will be called by the Facade
    {
        cout << "Updating data in database..." << endl;
    }
    void deleteData() // Method to delete data from the database, which will be called by the Facade
    {
        cout << "Deleting data from database..." << endl;
    }
};

class Facade // Facade class that provides a simplified interface to the complex subsystem of ProviderComunication, SiteComunication, and DatabaseComunication
{
    ProviderComunication provider; // Instance of ProviderComunication to be used by the Facade
    SiteComunication site; // Instance of SiteComunication to be used by the Facade
    DatabaseComunication database; // Instance of DatabaseComunication to be used by the Facade
public:
    void performComplexOperation() // Method to perform a complex operation using the Facade, which will call methods on the subsystem classes in a specific sequence
    {
        cout << "Performing complex operation using Facade..." << endl;
        provider.receiveData(); // Call method on ProviderComunication to receive data
        site.activationData(); // Call method on SiteComunication to activate data for the site
        database.storeData(); // Call method on DatabaseComunication to store data in the database
        cout << "Complex operation completed." << endl;
    }
    void performAnotherComplexOperation() // Method to perform another complex operation using the Facade, which will call different methods on the subsystem classes in a specific sequence
    {
        cout << "Performing another complex operation using Facade..." << endl;
        provider.updateData(); // Call method on ProviderComunication to update data for the provider
        site.eraseData(); // Call method on SiteComunication to erase data from the site
        database.deleteData(); // Call method on DatabaseComunication to delete data from the database
        cout << "Another complex operation completed." << endl;
    }
};

int main() 
{
    cout << "Facade Pattern Example" << endl;
    
    Facade facade; // Create an instance of the Facade class
    facade.performComplexOperation(); // Call a method on the Facade to perform a complex operation

    cout << endl; // Output a newline for better readability

    facade.performAnotherComplexOperation(); // Call another method on the Facade to perform a different complex operation
    cout << endl; // Output a newline for better readability

    return 0;
}   
