/**
 * @file Prototype.cpp
 * @brief Implementation of the Prototype design pattern in C++.
 *
 * The Prototype pattern allows for the creation of new objects by copying existing ones, 
 * which can be more efficient than creating new instances from scratch. This is particularly 
 * useful when object creation is costly or complex. The pattern involves a prototype interface 
 * that defines a cloning method, and concrete prototypes that implement this interface.
 *
 * In this implementation, we have a base class `Prototype` with a pure virtual `clone` method, 
 * and two concrete classes `ConcretePrototypeA` and `ConcretePrototypeB` that implement the cloning 
 * functionality. The `main` function demonstrates how to use the prototype pattern to create clones 
 * of the concrete prototypes and display their data.
 * @details This pattern is especially beneficial in embedded systems where memory and processing 
 * resources are limited, and creating new instances can be expensive in terms of time and memory.
 * @standard Follows SOLID principles (Single Responsibility Principle).
 * @author Sergey Petrov
 * @date 2026-02-02
 */

#include <iostream>
#include <string>
using namespace std;

// Prototype interface
class Prototype {
public:
    virtual Prototype* clone() const = 0;
    virtual void showData() const = 0;
    virtual ~Prototype() {}
};  
// Concrete Prototype A
class ConcretePrototypeA : public Prototype {
    string data;
public:
    ConcretePrototypeA(string d) : data(d) {}
    Prototype* clone() const override {
        return new ConcretePrototypeA(*this);
    }
    void showData() const override {
        cout << "ConcretePrototypeA Data: " << data << endl;
    }
};
// Concrete Prototype B
class ConcretePrototypeB : public Prototype {
    string data;
public:
    ConcretePrototypeB(string d) : data(d) {}
    Prototype* clone() const override {
        return new ConcretePrototypeB(*this);
    }
    void showData() const override {
        cout << "ConcretePrototypeB Data: " << data << endl;
    }
}; 

int main() {
    ConcretePrototypeA prototypeA("Prototype A Data");
    Prototype* cloneA = prototypeA.clone();
    cloneA->showData();

    ConcretePrototypeB prototypeB("Prototype B Data");
    Prototype* cloneB = prototypeB.clone();
    cloneB->showData();

    delete cloneA;
    delete cloneB;

    return 0;
}
