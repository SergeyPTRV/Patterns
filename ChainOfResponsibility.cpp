
/*
 * @file ChainOfResponsibility.cpp
 * @brief Implementation of the Chain of Responsibility design pattern in C++14.
 * @details The Chain of Responsibility pattern is a behavioral design pattern that allows an object to send a request along a chain of potential handlers until one of them handles the request. In this implementation, we have an `IHandler` interface that defines the methods for handling requests and setting the next handler in the chain, and concrete handler classes that implement this interface to process specific types of requests.
 * @author Sergey Petrov
 * @date 2026-03-23
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class IHandler // Abstract base class representing a handler in the chain of responsibility pattern, which defines the interface for handling requests and setting the next handler in the chain
{
public:
    virtual string handleRequest(string request) = 0; // Pure virtual method to be implemented by concrete handlers, which takes an integer request as input and defines how the handler will process the request
    virtual IHandler *setNext(IHandler *nextHandler) = 0; // Method to set the next handler in the chain, allowing the current handler to delegate requests to the next handler if it cannot process them
};

class AbstractHandler : public IHandler // Abstract class that implements the IHandler interface and provides a default implementation for handling requests, which can be overridden by concrete handlers to provide specific handling logic
{
    IHandler *next; // Pointer to the next handler in the chain, allowing the current handler to delegate requests to the next handler if it cannot process them
public:
    AbstractHandler() : next(nullptr) {}

    IHandler *setNext(IHandler *nextHandler) override // Method to set the next handler in the chain, allowing for method chaining when setting up the chain of responsibility  
    { 
        next = nextHandler; 
        return nextHandler; 
    } 
    
    string handleRequest(string request) override // Override of the handleRequest method to provide a default implementation for handling requests, which checks if the current handler can process the request and either processes it or delegates it to the next handler in the chain
    {
        if (next) {
            return next->handleRequest(request); // Delegate the request to the next handler in the chain if the current handler cannot process it
        }
        return {}; // Return a message indicating that no handler in the chain was able to process the request
    }
};

class Handler1 : public AbstractHandler // Concrete handler class that inherits from AbstractHandler and implements the handleRequest method to process specific requests, which checks if the request matches a certain condition and processes it if it does, or delegates it to the next handler if it does not
{
public:
    string handleRequest(string request) override // Override of the handleRequest method to provide a specific implementation for Handler1, which checks if the request matches a certain condition (e.g., "Request 1") and processes it if it does, or delegates it to the next handler if it does not
    {
        if (request == "Request 1") {
            return "Handler1: Handling " + request; // Return a message indicating that Handler1 is handling the request if the request matches the specified condition
        }
        return AbstractHandler::handleRequest(request); // Delegate the request to the next handler in the chain if the request does not match the specified condition, using the default implementation from AbstractHandler
    }
};

class Handler2 : public AbstractHandler // Concrete handler class that inherits from AbstractHandler and implements the handleRequest method to process specific requests, which checks if the request matches a certain condition and processes it if it does, or delegates it to the next handler if it does not
{
public:
    string handleRequest(string request) override // Override of the handleRequest method to provide a specific implementation for Handler2, which checks if the request matches a certain condition (e.g., "Request 2") and processes it if it does, or delegates it to the next handler if it does not
    {
        if (request == "Request 2") {
            return "Handler2: Handling " + request; // Return a message indicating that Handler2 is handling the request if the request matches the specified condition
        }
        return AbstractHandler::handleRequest(request); // Delegate the request to the next handler in the chain if the request does not match the specified condition, using the default implementation from AbstractHandler
    }
};

class Handler3 : public AbstractHandler // Concrete handler class that inherits from AbstractHandler and implements the handleRequest method to process specific requests, which checks if the request matches a certain condition and processes it if it does, or delegates it to the next handler if it does not
{
public:
    string handleRequest(string request) override // Override of the handleRequest method to provide a specific implementation for Handler3, which checks if the request matches a certain condition (e.g., "Request 3") and processes it if it does, or delegates it to the next handler if it does not
    {
        if (request == "Request 3") {
            return "Handler3: Handling " + request; // Return a message indicating that Handler3 is handling the request if the request matches the specified condition
        }
        return AbstractHandler::handleRequest(request); // Delegate the request to the next handler in the chain if the request does not match the specified condition, using the default implementation from AbstractHandler
    }
}; 

void clientCode(IHandler *handler) // Function representing the client code that interacts with the chain of responsibility, which takes a pointer to the first handler in the chain and makes requests to it, demonstrating how the chain processes the requests
{
    vector<string> requests = {"Request 1", "Request 2", "Request 3", "Unknown Request"}; // Vector of requests to be processed by the chain of responsibility, including some that match specific handlers and one that does not match any handler
    for (const string &request : requests) {
        cout << "Client: Who wants to handle " << request << "?" << endl; // Output a message indicating that the client is making a request and asking which handler will process it
        string result = handler->handleRequest(request); // Make a request to the first handler in the chain and store the result in a string variable
        if (!result.empty()) {
            cout << "  " << result << endl; // Output the result of handling the request if it was processed by any handler in the chain
        } else {
            cout << "  " << request << " was left unhandled." << endl; // Output a message indicating that the request was left unhandled if no handler in the chain was able to process it
        }
    }
}

int main() {
    Handler1 *handler1 = new Handler1(); // Create a new instance of Handler1 and store it in a pointer
    Handler2 *handler2 = new Handler2(); // Create a new instance of Handler2 and store it in a pointer
    Handler3 *handler3 = new Handler3(); // Create a new instance of Handler3 and store it in a pointer

    handler1->setNext(handler2)->setNext(handler3); // Set up the chain of responsibility by linking the handlers together, allowing requests to be passed from handler1 to handler2 and then to handler3 if they cannot be processed by the previous handlers

    clientCode(handler1); // Call the client code function, passing the first handler in the chain (handler1) to demonstrate how the chain processes the requests

    return 0; // Return 0 to indicate successful execution of the program
}
