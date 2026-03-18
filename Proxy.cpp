/* @file Proxy.cpp
 * @brief Implementation of the Proxy design pattern in C++14.
 * @details The Proxy pattern is a structural design pattern that provides a surrogate or placeholder for another object to control access to it. In this implementation, we have a `Subject` interface that defines the method for making requests, a `RealSubject` class that implements the actual functionality, and a `Proxy` class that controls access to the real subject and can perform additional operations before or after delegating requests.
 * @author Sergey Petrov
 * @date 2026-03-18
*/
    
#include <iostream>
#include <string>
#include <map>

using namespace std;

class Subject // Class representing the subject in the proxy pattern, which defines the interface for the real subject and the proxy to implement
{
public:
    virtual string request(int data) = 0; // Pure virtual method to be implemented by the real subject and the proxy, which takes an integer data as input and returns a string response
    virtual ~Subject() {} // Virtual destructor to ensure proper cleanup of resources when deleting objects through a pointer to the base class
};

class RealSubject : public Subject // Class representing the real subject in the proxy pattern, which implements the actual functionality of the subject and provides a concrete implementation of the request method
{
public:
    string request(int data) override // Override of the request method to provide the actual implementation of the real subject, which takes an integer data as input and returns a string response based on the data
    {
        return "RealSubject: Handling request with data " + to_string(data); // Return a string response indicating that the real subject is handling the request with the provided data, converting the integer data to a string for concatenation
    }
};

class Proxy : public Subject // Class representing the proxy in the proxy pattern, which controls access to the real subject and can perform additional operations before or after delegating requests to the real subject
{
    Subject *realSubject; // Pointer to the real subject that the proxy will control access to, allowing the proxy to delegate requests to the real subject when necessary
    map<int, string> cache; // Map to store cached responses for requests, allowing the proxy to return cached responses for previously handled requests without needing to delegate to the real subject again
public:
    Proxy(Subject *real) : realSubject(real) {} // Constructor to initialize the proxy with a pointer to the real subject, allowing the proxy to control access to the real subject

    string request(int data) override // Override of the request method to provide the implementation of the proxy, which checks if a cached response exists for the given data and returns it if available, or delegates to the real subject and caches the response if not
    {
        if (cache.find(data) != cache.end()) { // Check if a cached response exists for the given data in the cache map
            return "Proxy: Returning cached response for data " + to_string(data) + ": " + cache[data]; // Return a string response indicating that a cached response is being returned for the provided data, including the cached response from the cache map
        }
        string result = realSubject->request(data); // Delegate the request to the real subject and store the result in a string variable
        cache[data] = result; // Cache the result in the cache map using the provided data as the key
        return "Proxy: Delegating request to RealSubject for data " + to_string(data) + ": " + result; // Return a string response indicating that the request is being delegated to the real subject for the provided data, including the result from the real subject
    }

    ~Proxy() { delete realSubject; } // Destructor to clean up resources by deleting the real subject when the proxy object is destroyed
};

int main() {
    Subject *realSubject = new RealSubject(); // Create a new instance of the real subject and store it in a pointer to the base class Subject
    Proxy proxy(realSubject); // Create a new instance of the proxy, passing the pointer to the real subject to control access to it

    cout << proxy.request(10) << endl; // Make a request through the proxy with data 10 and output the response to the console
    cout << proxy.request(20) << endl; // Make a request through the proxy with data 20 and output the response to the console
    cout << proxy.request(10) << endl; // Make another request through the proxy with data 10, which should return a cached response, and output it to the console

    return 0; // Return 0 to indicate successful execution of the program
}   