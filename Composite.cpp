/*
* @file Composite.cpp
* @brief Implementation of the Composite design pattern.
* @details The Composite pattern allows you to compose objects into tree structures to represent part-whole hierarchies. 
* It lets clients treat individual objects and compositions of objects uniformly.
* @author Sergey Petrov
* @date 2026-03-16
*/  

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Component
{
    protected:
        string _name; // Name of the component, used for identification
        string _data; // Data associated with the component, can be used for various purposes in the operation method

    public:    
        Component(string n) : _name(n) {} // Constructor to initialize the component with a name

        void setData(string d) // Method to set the data for the component
        {
            _data = d; // Set the data for the component
        } 

        virtual void add(Component* component) {};// Virtual method to add a child component, can be overridden by composite classes
        virtual void remove(Component* component) {}; // Virtual method to remove a child component, can be overridden by composite classes
        virtual void operation() = 0; // Pure virtual method to perform an operation, to be implemented by leaf and composite classes
        //virtual ~Component() {} //
    };

class Leaf : public Component
{
public:    
    Leaf(string n) : Component(n) {} // Constructor to initialize the leaf with a name
    void add(Component* component) override {} // Leaf does not support adding child components, so this method is empty
    void remove(Component* component) override {} // Leaf does not support removing child components, so this method is empty

    void operation() override // Implement the operation for a leaf component
    {
        cout << "Leaf " << _name << " operation with data: " << _data << endl; // Output the leaf's name and data when the operation is performed
    }
};

class Composite : public Component
{
    vector<Component*> children; // Vector to hold child components, allowing for a tree structure
public:    
    Composite(string n) : Component(n) {} // Constructor to initialize the composite with a name

    void add(Component* component) override // Implement adding a child component to the composite
    {
        component->setData(/*"Data for " + component*/ this->_name); // Set data for the child component based on its name
        children.push_back(component); // Add the child component to the vector of children
    }

    void remove(Component* component) override // Implement removing a child component from the composite
    {
        children.erase(std::remove(children.begin(), children.end(), component), children.end()); // Remove the specified child component from the vector of children
    }

    void operation() override // Implement the operation for a composite component
    {
        cout << "Composite " << _name << " operation with data: " << _data << endl; // Output the composite's name and data when the operation is performed
        for (Component* child : children) { // Iterate through each child component and perform its operation
            child->operation(); // Call the operation method on each child component, allowing for recursive operations in a tree structure
        }
    }
};

int main() {
    cout << "Composite Pattern Example" << endl;

    Component* root = new Composite("Root"); // Create the root composite component
    Component* child1 = new Leaf("Child1"); // Create a leaf component named Child1
    Component* child2 = new Leaf("Child2"); // Create a leaf component named Child2
    Component* child3 = new Composite("Child3"); // Create a composite component named Child3   

    root->add(child1); // Add Child1 to the root composite
    root->add(child2); // Add Child2 to the root composite
    root->add(child3); // Add Child3 to the root composite

    Component* grandchild1 = new Leaf("Grandchild1"); // Create a leaf component named Grandchild1
    Component* grandchild2 = new Leaf("Grandchild2"); // Create a leaf component named Grandchild2
    child3->add(grandchild1); // Add Grandchild1 to Child3 composite
    child3->add(grandchild2); // Add Grandchild2 to Child3 composite

    root->operation(); // Perform the operation on the root composite, which will recursively perform operations on all child components

    child3->remove(grandchild1); // Remove Grandchild1 from Child3 composite
    cout << "\nAfter removing Grandchild1 from Child3:\n" << endl; // Output a message indicating that Grandchild1 has been removed from Child3
    root->operation(); // Perform the operation on the root composite again to see the effect of removing Grandchild1

    return 0;
}
 