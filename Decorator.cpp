/*
 * @file Decorator.cpp
 * @brief Implementation of the Decorator design pattern in C++14.
 * @details This file demonstrates the Decorator pattern, which allows behavior to be added to individual objects, 
 * dynamically, without affecting the behavior of other objects from the same class. The `Component` class defines 
 * the interface for objects that can have responsibilities added to them dynamically. The `ConcreteComponent` 
 * class is a simple implementation of the `Component` interface. The `Decorator` class maintains a reference to a `Component` object and defines an interface that conforms to `Component`'s interface. 
 * The `ConcreteDecoratorA` and `ConcreteDecoratorB` classes extend the functionality of the `Component` by adding new behavior before or after delegating to the `Component` object.
 * @author Sergey Petrov
 * @date 2026-03-17
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Processor // Abstract base class for processing data, which will be decorated by concrete decorators
{
public:    
    virtual void process() = 0; // Pure virtual method to be implemented by concrete processors
};

class Transmitter : public Processor // Concrete implementation of Processor that transmits data
{
    string data; // Data to be transmitted, can be set by the client or through decorators
public:    
    Transmitter(string d) : data(d) {} // Constructor to initialize the transmitter with data
    void process() override // Implement the process method for Transmitter
    {
        cout << "Transmitting data..." << data<< endl; // Output a message indicating that data is being transmitted
    }
};

class Shell : public Processor // Base decorator class that wraps a Processor object and delegates processing to it
{
    protected:
    Processor* processor; // Reference to a Processor object that the decorator will enhance
public:    
    Shell(Processor* p) : processor(p) {} // Constructor to initialize the decorator with a Processor object
    void process() override // Implement the process method to delegate to the wrapped Processor object
    {
        processor->process(); // Delegate the processing to the wrapped Processor object
    }
};

class HammingCoder : public Shell // Concrete decorator that adds Hamming coding functionality to a Processor
{
public:    
    HammingCoder(Processor* p) : Shell(p) {} // Constructor to initialize the HammingCoder with a Processor object
    void process() override // Implement the process method to add Hamming coding functionality
    {
        cout << "Adding Hamming code for error correction..." << endl; // Output a message indicating that Hamming coding is being added
        processor->process(); // Delegate the processing to the wrapped Processor object
    }
};

class Encryption : public Shell // Concrete decorator that adds encryption functionality to a Processor
{
public:    
    Encryption(Processor* p) : Shell(p) {} // Constructor to initialize the Encryption with a Processor object
    void process() override // Implement the process method to add encryption functionality
    {
        cout << "Encrypting data..." << endl; // Output a message indicating that encryption is being added
        processor->process(); // Delegate the processing to the wrapped Processor object
    }
};


int main() {
    cout << "Decorator Pattern Example" << endl;
    // Implementation of the Decorator pattern would go here --- IGNORE ---

        Processor* transmitter = new Transmitter("Hello, World!"); // Create a Transmitter object with some data to transmit
        transmitter->process(); // Call the process method to see the basic transmission functionality
        cout << endl; // Output a newline for better readability

        Processor* hammingTransmitter = new HammingCoder(transmitter); // Decorate the Transmitter with Hamming coding functionality
        hammingTransmitter->process(); // Call the process method to see the combined effect of the Transmitter and HammingCoder decorators
        cout << endl; // Output a newline for better readability

        Processor* encryptedHammingTransmitter = new Encryption(hammingTransmitter); // Decorate the HammingCoder with encryption functionality 
        encryptedHammingTransmitter->process(); // Call the process method to see the combined effect of the decorators
        cout << endl; // Output a newline for better readability

     return 0;
}

