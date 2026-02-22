/*
 * @file Adapter.cpp
 * @brief Implementation of the Adapter design pattern.
 * @details The Adapter pattern allows incompatible interfaces to work together by converting the interface of one class into another interface that clients expect. 
 * This is particularly useful in embedded systems where you may need to integrate legacy code or third-party libraries with a new system architecture. 
 * The `main` function demonstrates how to use the adapter pattern to allow a client to use an incompatible interface through an adapter.
 * @author Sergey Petrov
 * @date 2026-02-02
 */

#include    <iostream>
#include    <string>    

using namespace std;

// LengthAdapter interface expected by the client
class LengthAdapter {
public:
    virtual float* getLength() = 0; // Pure virtual method to get length, which will be implemented by concrete adapters
    virtual ~LengthAdapter() {} // Virtual destructor for proper cleanup
};

// Adaptee class with an incompatible interface
class EuroLength : public LengthAdapter {
    float* lengthInMeters;  // Length in meters, which is the expected format for EuroLength
public:
    EuroLength(float* meters) : lengthInMeters(meters) {}   // Constructor to initialize length in meters
    float* getLength() override {   // Return length in meters, which is the expected format for EuroLength
        return lengthInMeters;  // Return length in meters, which is the expected format for EuroLength
    }
    ~EuroLength() { // Clean up length in meters
        delete lengthInMeters;  // Clean up length in meters
    }
};

// Adaptee class with an incompatible interface
class USLength{
    float* curentLength;    // Length in meters, will be converted to feet by adapter
public:
    USLength(float* meters) : curentLength(meters) {}   // Constructor to initialize length in meters
    float* getLength(){ // Return length in meters, will be converted by adapter
        return curentLength;  // Return length in meters, will be converted by adapter
    }
    ~USLength() {
        delete curentLength;    // Clean up length in meters
    }
};

// Adapter class that converts EuroLength to USLength
class LengthAdapterUS : public LengthAdapter {
    USLength* usLength;     // Adaptee
    float* lengthInFeet;    // Converted length in feet
public:
    LengthAdapterUS(USLength* usLength) : usLength(usLength), lengthInFeet(nullptr) {

    }
    float* getLength() override {   // Convert length from meters to feet
        lengthInFeet = usLength->getLength();   // Get length in meters from USLength
        *lengthInFeet = (*lengthInFeet) * 3.28084; // Convert meters to feet
        return lengthInFeet;    // Return length in feet
    }
    ~LengthAdapterUS() {
        delete usLength;    // Clean up USLength
        delete lengthInFeet; // Clean up converted length in feet
    }
};

int main() 
{
    float lengthInMeters = 3.0; // 1 meter

    LengthAdapter* euroLength = new EuroLength(&lengthInMeters);    // Create an instance of EuroLength with length in meters
    LengthAdapter* usLength = new LengthAdapterUS(new USLength(&lengthInMeters));   // Create an instance of LengthAdapterUS with a new USLength that has length in meters

    cout << "Length in meters: " << *euroLength->getLength() << " m" << endl;
    cout << "Length in feet: " << *usLength->getLength() << " ft" << endl; 

    return 0;
}