
/**
 * @file Singleton.cpp
 * @brief Implementation of the Singleton design pattern in C++.
 *
 * The Singleton pattern ensures that a class has only one instance and provides a global point of access to it. 
 * This implementation uses lazy initialization, where the instance is created only when it is first requested.
 *
 * @details This pattern is particularly useful in scenarios where a single point of control is needed, such as  
 * managing a connection pool, logging, or configuration settings in an embedded system. It ensures that all parts of the system use the same instance, which can help prevent issues related to multiple instances and ensure consistent behavior across the application.
 * @note This implementation is not thread-safe. In a multi-threaded environment, additional synchronization mechanisms would be needed to ensure that only one instance is created.
 * @standard Follows SOLID principles (Single Responsibility Principle).
 * @author Sergey Petrov
 * @date 2026-02-22
 */

#include <iostream>
#include <string>

using namespace std;

// Singleton class
class Singleton {
private:
    static Singleton* instance;
    string data;
    // Private constructor to prevent instantiation
    Singleton() {
        data = "Singleton Data Initialized";
    }
public:
    // Static method to get the single instance of the class
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
    string getData() const {
        return data;
    }
    void setData(const string& newData) {
        data = newData;
    }
}; 

// Initialize the static member
Singleton* Singleton::instance = nullptr;  

int main() {
    // Get the singleton instance and use it
    Singleton* singleton1 = Singleton::getInstance();
    cout << "Singleton1 Data: " << singleton1->getData() << endl;

    // Modify the data through the singleton instance
    singleton1->setData("Updated Singleton Data from singleton1");

    // Get the singleton instance again and check if the data is updated
    Singleton* singleton2 = Singleton::getInstance();
    cout << "Singleton2 Data: " << singleton2->getData() << endl;

    // Modify the data through the singleton2 instance
    singleton2->setData("Updated Singleton Data from singleton2");

    // Get the singleton instance again and check if the data is updated
    Singleton* singleton3 = Singleton::getInstance();
    cout << "Singleton3 Data: " << singleton3->getData() << endl;

    cout << "Singleton2 Data: " << singleton2->getData() << endl; 
    cout << "Singleton1 Data: " << singleton1->getData() << endl;

    return 0;
}
