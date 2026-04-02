#include <iostream>
#include <string>

using namespace std;

class Employee // Class representing an employee in the mediator pattern, which contains a reference to the mediator and provides methods to perform actions that will be communicated through the mediator
{
    //string name; // String representing the name of the employee, which is used for identification and communication purposes in the mediator pattern
protected:
    class Mediator *mediator; // Pointer to the Mediator object that the employee will communicate with, allowing the employee to send notifications and receive messages through the mediator
public:
    Employee(Mediator *m =nullptr) : mediator(m) {} // Constructor to initialize the Employee with a name and a pointer to the Mediator, allowing the employee to communicate through the mediator
    //void send(string event) { mediator->notify(name, event); } // Method to send a notification to the mediator, which takes an event as input and uses the mediator's notify method to communicate the event along with the employee's name to other components that are registered with the mediator
    //void receive(string message) { cout << name << " received: " << message << endl; } // Method to receive a message from the mediator, which takes a message as input and outputs it to the console along with the employee's name, indicating that the employee has received a message from the mediator
    
    void setMediator(Mediator *m) // Method to set the mediator for the employee, allowing the employee to establish a communication link with the mediator after the employee has been created, which is useful for scenarios where the mediator is not available at the time of employee creation   
    { 
        mediator = m; 
    } 

    virtual ~Employee() {} // Virtual destructor to ensure proper cleanup of resources when deleting objects through a pointer to the base class
};

class Mediator // Class representing the mediator in the mediator pattern, which defines the interface for communication between different components and manages their interactions
{
public:    
    virtual void notify(Employee* sender, string event) = 0; // Pure virtual method to be implemented by concrete mediators, which defines how the mediator will handle notifications from different components based on the sender and the event

    virtual ~Mediator() {} // Virtual destructor to ensure proper cleanup of resources when deleting objects through a pointer to the base class
};  

class EmployeeConcreteA : public Employee // Concrete class representing a specific type of employee in the mediator pattern, which implements the receive method to handle messages received from the mediator in a specific way
{
    bool isBusy; // Boolean variable to represent whether the employee is currently busy or not, which can be used to determine how the employee will respond to messages received from the mediator
public:
    EmployeeConcreteA(Mediator *m = nullptr) : Employee(m), isBusy(false) {} // Constructor to initialize the EmployeeConcreteA with a pointer to the Mediator and set the isBusy variable to false, indicating that the employee is initially not busy and can receive messages from the mediator  
    
    void Execute()
    {
        cout << "EmployeeConcreteA is executing a task." << endl; // Output a message indicating that this employee is executing a task, which can be used to demonstrate the employee's actions in the context of the mediator pattern 
        mediator->notify(this, "EmployeeConcreteA is executing a task."); // Method to execute a task and notify the mediator about the action being performed by this employee, allowing the mediator to communicate this information to other components that are registered with the mediator    
    }
    void SetBusy(bool busy) // Method to set the busy status of the employee, allowing other components or the mediator to update the employee's status based on certain conditions or events
    { 
        isBusy = busy; 
        if(isBusy) {
            cout << "EmployeeConcreteA is now busy." << endl; // Output a message indicating that this employee is now busy, which can be used to demonstrate the change in the employee's status in the context of the mediator pattern
        } else {
            cout << "EmployeeConcreteA is now available." << endl; // Output a message indicating that this employee is now available, which can be used to demonstrate the change in the employee's status in the context of the mediator pattern
        }
    } 
};

class EmployeeConcreteB : public Employee // Concrete class representing another specific type of employee in the mediator pattern, which implements the receive method to handle messages received from the mediator in a different way than EmployeeConcreteA
{
    string currentTask; // String variable to represent the current task that the employee is working on, which can be used to determine how the employee will respond to messages received from the mediator based on the task they are currently engaged in   
public:
    EmployeeConcreteB(Mediator *m = nullptr) : Employee(m), currentTask("") {} // Constructor to initialize the EmployeeConcreteB with a pointer to the Mediator and set the currentTask variable to an empty string, indicating that the employee is initially not working on any task and can receive messages from the mediator
    
    void Execute(string task) 
    {
        currentTask = task; // Update the current task that this employee is working on, allowing the employee to keep track of their current workload and respond to messages from the mediator accordingly
        cout << "EmployeeConcreteB is executing task: " << currentTask << endl; // Output a message indicating that this employee is executing a specific task, which can be used to demonstrate the employee's actions in the context of the mediator pattern 
        mediator->notify(this, "EmployeeConcreteB is executing task: " + currentTask); // Method to execute a task and notify the mediator about the action being performed by this employee, allowing the mediator to communicate this information to other components that are registered with the mediator    
    }
};

class ConcreteMediator : public Mediator // Concrete class representing the mediator in the mediator pattern, which implements the notify method to define how the mediator will handle notifications from different components based on the sender and the event
{
    EmployeeConcreteA *employeeA; // Pointer to an instance of EmployeeConcreteA, allowing the mediator to communicate with this specific type of employee and manage its interactions with other components
    EmployeeConcreteB *employeeB; // Pointer to an instance of EmployeeConcreteB, allowing the mediator to communicate with this specific type of employee and manage its interactions with other components
public:
    ConcreteMediator(EmployeeConcreteA *a, EmployeeConcreteB *b) : employeeA(a), employeeB(b) // Constructor to initialize the ConcreteMediator with pointers to instances of EmployeeConcreteA and EmployeeConcreteB, allowing the mediator to manage the interactions between these specific types of employees   
    {
        employeeA->setMediator(this); // Set the mediator for employeeA to this instance of ConcreteMediator, allowing employeeA to communicate through this mediator
        employeeB->setMediator(this); // Set the mediator for employeeB to this instance of ConcreteMediator, allowing employeeB to communicate through this mediator
    } 
    void notify(Employee* sender, string event) override // Override of the notify method to define how the mediator will handle notifications from different components based on the sender and the event, allowing the mediator to manage the interactions between employeeA and employeeB based on their actions and statuses
    {
        if(auto *a = dynamic_cast<EmployeeConcreteA*>(sender)) { // Check if the sender is an instance of EmployeeConcreteA, allowing the mediator to handle notifications specifically from this type of employee  
            if(event == "EmployeeConcreteA is executing a task.") {
                employeeB->Execute("Task assigned by EmployeeConcreteA");
            }
        } else if(auto *b = dynamic_cast<EmployeeConcreteB*>(sender)) { // Check if the sender is an instance of EmployeeConcreteB, allowing the mediator to handle notifications specifically from this type of employee   
            if(event.find("EmployeeConcreteB is executing task: ") != string::npos) {
                cout << "Mediator received notification from EmployeeConcreteB: " << event << endl;
            }
        }
    }
};

int main() {
    EmployeeConcreteA *employeeA = new EmployeeConcreteA(); // Create an instance of EmployeeConcreteA to represent a specific type of employee in the mediator pattern
    EmployeeConcreteB *employeeB = new EmployeeConcreteB(); // Create an instance of EmployeeConcreteB to represent another specific type of employee in the mediator pattern
    ConcreteMediator *mediator = new ConcreteMediator(employeeA, employeeB); // Create an instance of ConcreteMediator, passing the instances of EmployeeConcreteA and EmployeeConcreteB to manage their interactions through the mediator
    
    employeeA->Execute(); // Call the Execute method on employeeA to demonstrate its actions and how it communicates with the mediator, which will in turn communicate with employeeB based on the defined behavior in the notify method of the ConcreteMediator

    employeeB->Execute("Independent task for EmployeeConcreteB"); // Call the Execute method on employeeB with a specific task to demonstrate its actions and how it communicates with the mediator, which will output a message based on the defined behavior in the notify method of the ConcreteMediator 

    employeeA->Execute(); // Call the Execute method on employeeA to demonstrate its actions and how it communicates with the mediator, which will in turn communicate with employeeB based on the defined behavior in the notify method of the ConcreteMediator

    //delete employeeA; // Clean up the dynamically allocated instance of EmployeeConcreteA to prevent memory leaks
    //delete employeeB; // Clean up the dynamically allocated instance of EmployeeConcreteB to prevent memory leaks
    //delete mediator; // Clean up the dynamically allocated instance of ConcreteMediator to prevent memory leaks

    return 0; // Return 0 to indicate successful execution of the program
}   