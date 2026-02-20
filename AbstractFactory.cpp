#include <iostream>

using namespace std;

// Product interface
class Product {
public:
    virtual void use() = 0;
    virtual ~Product() {}
};

// Concrete Product A1
class ConcreteProductA1 : public Product {
public:

    void use() override {
        cout << "Using ConcreteProductA1" << endl;
    }
};
// Concrete Product A2
class ConcreteProductA2 : public Product {
public:
    void use() override {
        cout << "Using ConcreteProductA2" << endl;
    }
};
// Concrete Product B1
class ConcreteProductB1 : public Product {
public:
    void use() override {
        cout << "Using ConcreteProductB1" << endl;
    }
};  
// Concrete Product B2
class ConcreteProductB2 : public Product {
public:
    void use() override {
        cout << "Using ConcreteProductB2" << endl;
    }
};

// Abstract Factory interface
class AbstractFactory {
public:
    virtual Product* createProductA() = 0;
    virtual Product* createProductB() = 0;
    virtual ~AbstractFactory() {}
};
// Concrete Factory 1
class ConcreteFactory1 : public AbstractFactory {
public:
    Product* createProductA() override {
        return new ConcreteProductA1();
    }
    Product* createProductB() override {
        return new ConcreteProductB1();
    }
};
// Concrete Factory 2
class ConcreteFactory2 : public AbstractFactory {
public:
    Product* createProductA() override {
        return new ConcreteProductA2();
    }
    Product* createProductB() override {
        return new ConcreteProductB2();
    }
}; 
//#define V1
int main() 
{

    #ifdef V1
    AbstractFactory* factory1 = new ConcreteFactory1();
    Product* productA1 = factory1->createProductA();
    Product* productB1 = factory1->createProductB();
    productA1->use();
    productB1->use();
    delete productA1;
    delete productB1;
    delete factory1;

    AbstractFactory* factory2 = new ConcreteFactory2();
    Product* productA2 = factory2->createProductA();
    Product* productB2 = factory2->createProductB();
    productA2->use();
    productB2->use();
    delete productA2;
    delete productB2;
    delete factory2;
    
    #else
    AbstractFactory* factory[] = {new ConcreteFactory1(), new ConcreteFactory2()};
    for (AbstractFactory* f : factory) {
        Product* productA = f->createProductA();
        Product* productB = f->createProductB();
        productA->use();
        productB->use();
        delete productA;
        delete productB;
        delete f;
    }

    #endif

    return 0;
}