/*
* @file Flyweight.cpp
* @brief Implementation of the Flyweight design pattern in C++14.
* @details The Flyweight pattern is a structural design pattern that allows for the efficient sharing of common data among multiple objects. It is particularly useful in scenarios where a large number of similar objects are created, and it helps to reduce memory usage by sharing intrinsic state while keeping extrinsic state separate. In this implementation, we have a `Flyweight` class that represents the shared state (intrinsic state) and a `FlyweightFactory` class that manages the creation and sharing of flyweight objects
* based on their shared state. The `addCarToPoliceDatabase` function demonstrates how to use the flyweight factory to add cars to a police database, utilizing the flyweight pattern to efficiently manage the shared state of car models and companies.
* @author Sergey Petrov
* @date 2026-03-18
*/

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

struct SharedState // Struct representing the shared state of a flyweight, which includes the company and position of a car model
{
    string company; // Intrinsic state that is shared among flyweight objects, representing the company associated with the flyweight
    string position; // Intrinsic state that is shared among flyweight objects, representing the position associated with the flyweight

    SharedState(const string &c, const string &p) : company(c), position(p) {} // Constructor to initialize the shared state with company and position
};

struct UniqueState // Struct representing the unique state of a flyweight, which includes the passport ID and name associated with a specific instance of the flyweight
{
    string passportID; // Extrinsic state that is unique to each flyweight object, representing the passport ID associated with the flyweight
    string name; // Extrinsic state that is unique to each flyweight object, representing the name associated with the flyweight

    UniqueState(const string &pid, const string &n) : passportID(pid), name(n) {} // Constructor to initialize the unique state with passport ID and name
    
};

class Flyweight // Class representing a flyweight object, which contains a shared state and can perform operations using both shared and unique state
{
    SharedState *sharedState; // Pointer to the shared state of the flyweight, which is common among multiple flyweight objects 
public:
    Flyweight(const SharedState *shared) : sharedState(new SharedState(*shared)) {} // Constructor to initialize the flyweight with a shared state, creating a new instance of SharedState based on the provided shared state
    Flyweight(const Flyweight &other) : sharedState(new SharedState(*other.sharedState)) {} // Copy constructor to create a new flyweight by copying the shared state from another flyweight
    ~Flyweight() { delete sharedState; } // Destructor to clean up the dynamically allocated shared state when the flyweight object is destroyed   

    void operation(const UniqueState &uniqueState) const // Method to perform an operation using the flyweight, which takes a unique state as a parameter and combines it with the shared state to perform some action
    {
        cout << "Flyweight: Displaying shared (" << sharedState->company << ", " << sharedState->position << ") and unique (" << uniqueState.passportID << ", " << uniqueState.name << ") state." << endl; // Output the shared and unique state of the flyweight to the console
    }
};

class FlyweightFactory // Class representing a factory for creating and managing flyweight objects, which maintains a collection of flyweights based on their shared state and provides methods to retrieve and list flyweights
{
    unordered_map<string, Flyweight *> flyweights; // Map to store flyweight objects, using a string key to identify each flyweight based on its shared state
    string getKey(const SharedState &ss) const // Method to generate a unique key for the flyweight based on its shared state, which concatenates the company and position to create a unique identifier for the flyweight
    {
        return ss.company + "_" + ss.position; // Generate a unique key by concatenating the company and position from the shared state
    }   
    public:
    FlyweightFactory(initializer_list<SharedState> shareStates) // Constructor to initialize the flyweight factory with a list of shared states, which creates flyweight objects for each shared state and stores them in the flyweights map
    {
        for (const SharedState &ss : shareStates) {
            this->flyweights.insert(make_pair(this->getKey(ss), new Flyweight(&ss))); // Insert a new flyweight object into the flyweights map, using the generated key based on the shared state
        }
    }
    
    Flyweight getFlyweight(const SharedState &sharedState) // Method to retrieve a flyweight object based on a given shared state, which checks if a flyweight with the specified shared state already exists in the flyweights map and returns it, or creates a new flyweight if it does not exist
    {
        string key = this->getKey(sharedState); // Generate a unique key for the flyweight based on the provided shared state
        if (this->flyweights.find(key) == this->flyweights.end()) { // Check if a flyweight with the generated key does not exist in the flyweights map
            cout << "FlyweightFactory: Can't find a flyweight, creating new one." << key << endl; // Output a message indicating that a new flyweight is being created because one with the specified shared state was not found
            this->flyweights.insert(make_pair(key, new Flyweight(&sharedState))); // Insert a new flyweight object into the flyweights map using the generated key and the provided shared state
        } 
        else 
        {
            cout << "FlyweightFactory: Reusing existing flyweight." << key << endl; // Output a message indicating that an existing flyweight is being reused because one with the specified shared state was found in the flyweights map
        }
        return *this->flyweights.at(key); // Return the flyweight object from the flyweights map corresponding to the generated key, dereferencing the pointer to return a reference to the flyweight
    }

    void listFlyweights() const // Method to list all the flyweight objects currently stored in the flyweights map, which outputs the total number of flyweights and their keys to the console
    {
        size_t count = this->flyweights.size(); // Get the total number of flyweight objects in the flyweights map
        cout << "FlyweightFactory: I have " << count << " flyweights:" << endl; // Output the total number of flyweights to the console
        for (auto pair : this->flyweights) { // Iterate through each key-value pair in the flyweights map
            cout << pair.first << endl; // Output the key of each flyweight to the console
        }
    }
};

void addCarToPoliceDatabase(FlyweightFactory &ff, const string &plates, const string &owner, const string &company, const string &model) // Function to add a car to the police database using the flyweight factory, which takes the flyweight factory and the unique and shared state of the car as parameters
{
    cout << "\nClient: Adding a car to database." << endl; // Output a message indicating that a car is being added to the database
    const Flyweight& flyweight = ff.getFlyweight({company, model}); // Retrieve a flyweight object from the flyweight factory based on the shared state of the car (company and model)
    flyweight.operation({plates, owner}); // Perform an operation using the retrieved flyweight object, passing in the unique state of the car (plates and owner) to display the combined state of the flyweight
}


int main() 
{
    FlyweightFactory *ff = new FlyweightFactory({{"Chevrolet", "Camaro2018"}, {"Mercedes Benz", "C300"}, {"Mercedes Benz", "C500"}, {"BMW", "M5"}, {"BMW", "X6"}}); // Create a flyweight factory and initialize it with a list of shared states representing different car models and their associated companies
    ff->listFlyweights(); // List all the flyweight objects currently stored in the flyweight factory

    addCarToPoliceDatabase(*ff, "CL234IR", "James Doe", "BMW", "M5"); // Add a car to the police database using the flyweight factory, providing the unique state (plates and owner) and shared state (company and model) of the car
    addCarToPoliceDatabase(*ff, "CL234IR", "James Doe", "BMW", "X1"); // Add another car to the police database using the flyweight factory, providing a different shared state (company and model) which will result in creating a new flyweight object

    ff->listFlyweights(); // List all the flyweight objects currently stored in the flyweight factory again to see the effect of adding a new car with a different shared state

    delete ff; // Clean up memory by deleting the flyweight factory object
    return 0;
}


