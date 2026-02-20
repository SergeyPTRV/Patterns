#include <iostream>

using namespace std;

// Product interface
class Product {
public:
    virtual void use() = 0;
    virtual ~Product() {}
};  
// Concrete Product A
class ConcreteProductA : public Product {
public:
    void use() override {
        cout << "Using ConcreteProductA" << endl;
    }
};
// Concrete Product B
class ConcreteProductB : public Product {
public:
    void use() override {
        cout << "Using ConcreteProductB" << endl;
    }
};

class ConcreteProductC : public Product {
public:
    void use() override {
        cout << "Using ConcreteProductC" << endl;
    }
};  

// Creator interface
class Creator {
public:
    virtual Product* factoryMethod() = 0;
    virtual ~Creator() {}
};
// Concrete Creator A
class ConcreteCreatorA : public Creator {
public:
    Product* factoryMethod() override {
        return new ConcreteProductA();
    }
};
// Concrete Creator B
class ConcreteCreatorB : public Creator {
public:
    Product* factoryMethod() override {
        return new ConcreteProductB();
    }
};

class ConcreteCreatorC : public Creator {
public:
    Product* factoryMethod() override {
        return new ConcreteProductC();
    }
};  

//#define V1
int main() 
{
    #ifdef V1
    Creator* creatorA = new ConcreteCreatorA();
    Product* productA = creatorA->factoryMethod();
    productA->use();    
    delete productA;
    delete creatorA;  

    Creator* creatorB = new ConcreteCreatorB();
    Product* productB = creatorB->factoryMethod();
    productB->use();    
    delete productB;
    delete creatorB;

    Creator* creatorC = new ConcreteCreatorC();
    Product* productC = creatorC->factoryMethod();
    productC->use();    
    delete productC;
    delete creatorC;


    #else
    Creator* creators[] = {new ConcreteCreatorA(), new ConcreteCreatorB(), new ConcreteCreatorC()};
    for (Creator* creator : creators) {
        Product* product = creator->factoryMethod();
        product->use();
        delete product;
        delete creator;
    }

    #endif
    return 0;
}