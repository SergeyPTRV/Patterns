/* @file Command.cpp
 * @brief Implementation of the Command design pattern in C++14.
 * @details The Command pattern is a behavioral design pattern that encapsulates a request as an object, allowing for parameterization of clients with queues, requests, and operations. In this implementation, we have an `ICommand` interface that defines the methods for incrementing and decrementing actions, a `Motor` class that represents the receiver of the commands, and concrete command classes `MotorCommand` and `MotorSpeedCommand` that implement the `ICommand` interface to perform specific actions on the motor. The `RemoteControl` class acts as the invoker that manages and executes commands, while also providing undo functionality by maintaining a history of executed commands.
 * @author Sergey Petrov
 * @date 2026-03-23
*/


#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

class ICommand // Interface representing a command in the command pattern, which defines the methods for incrementing and decrementing actions that concrete command classes will implement
{
public:
    virtual void increment() = 0; // Pure virtual method to be implemented by concrete command classes, which defines the action to increment a value
    virtual void decrement() = 0; // Pure virtual method to be implemented by concrete command classes, which defines the action to decrement a value
};

class Motor // Class representing the receiver of the commands in the command pattern, which defines the methods to start, stop, increase speed, and decrease speed of the motor, allowing concrete command classes to perform actions on the motor by calling these methods
{
public:
    void start() { cout << "Motor started." << endl; } // Method to start the motor, which outputs a message indicating that the motor has started
    void stop() { cout << "Motor stopped." << endl; } // Method to stop the motor, which outputs a message indicating that the motor has stopped    
    void increaseSpeed() { cout << "Motor speed increased." << endl; } // Method to increase the speed of the motor, which outputs a message indicating that the motor speed has been increased
    void decreaseSpeed() { cout << "Motor speed decreased." << endl; } // Method to decrease the speed of the motor, which outputs a message indicating that the motor speed has been decreased 
};

class MotorCommand : public ICommand // Concrete command class that implements the ICommand interface, which defines the actions to increment and decrement the motor's speed by calling the appropriate methods on the Motor class
{
    Motor *motor; // Pointer to the Motor object that the command will operate on, allowing the command to control the motor's behavior
public:
    MotorCommand(Motor *m) : motor(m) {} // Constructor to initialize the MotorCommand with a pointer to a Motor object, allowing the command to control the motor's behavior   
    void increment() { motor->start(); } // Method to start the motor by calling the start method on the Motor object
    void decrement() { motor->stop(); } // Method to stop the motor by calling the stop method on the Motor object
};

class MotorSpeedCommand : public ICommand // Concrete command class that implements the ICommand interface, which defines the actions to increment and decrement the motor's speed by calling the appropriate methods on the Motor class
{
    Motor *motor; // Pointer to the Motor object that the command will operate on, allowing the command to control the motor's behavior
public:
    MotorSpeedCommand(Motor *m) : motor(m) {} // Constructor to initialize the MotorSpeedCommand with a pointer to a Motor object, allowing the command to control the motor's behavior
    void increment() override { motor->increaseSpeed(); } // Override of the increment method to increase the motor's speed by calling the increaseSpeed method on the Motor object
    void decrement() override { motor->decreaseSpeed(); } // Override of the decrement method to decrease the motor's speed by calling the decreaseSpeed method on the Motor object
};

class RemoteControl // Class representing the invoker in the command pattern, which manages and executes commands for the motor, while also providing undo functionality by maintaining a history of executed commands
{
vector<ICommand *> commands; // Vector to store pointers to ICommand objects, allowing the remote control to manage multiple commands
stack<ICommand *> commandHistory; // Stack to store the history of executed commands, allowing the remote control to support undo functionality
public:
    RemoteControl() // Constructor to initialize the RemoteControl, which can be used to set up commands and manage command execution
    {
        commands.resize(2);
    } 
    void setCommand(int index, ICommand *command) // Method to add a command to the remote control by pushing it onto the commands vector
    { 
        commands[index] = command; 
    } 
    void pressButton(int index) 
    { // Method to execute a command based on its index in the commands vector, which also pushes the executed command onto the command history stack for undo functionality
        if (index >= 0 && index < commands.size()) {
            commands[index]->increment(); // Execute the increment action of the command at the specified index
            commandHistory.push(commands[index]); // Push the executed command onto the command history stack for potential undo operations
        }
    }
    void undo() 
    { // Method to undo the last executed command by popping it from the command history stack and calling its decrement method
        if (!commandHistory.empty()) {
            commandHistory.top()->decrement(); // Call the decrement action of the last executed command to undo its effect
            commandHistory.pop(); // Remove the last executed command from the command history stack after undoing it
        }
    }
};

int main() {
    Motor *motor = new Motor(); // Create an instance of the Motor class to represent the motor that will be controlled by the remote control
    RemoteControl* remote = new RemoteControl(); // Create an instance of the RemoteControl class to manage and execute commands for the motor
    
    remote->setCommand(0, new MotorCommand(motor)); // Set the first command in the remote control to be the motor command for starting and stopping the motor
    remote->setCommand(1, new MotorSpeedCommand(motor)); // Set the second command in the remote control to be the motor speed command for incrementing and decrementing the motor's speed

    remote->pressButton(0); // Press the first button on the remote control to start the motor
    remote->pressButton(1); // Press the second button on the remote control to increase the motor's speed
    remote->undo(); // Call undo on the remote control to decrease the motor's speed back to its previous state 
    remote->undo(); // Call undo on the remote control again to stop the motor, undoing the start command

    return 0; // Return 0 to indicate successful execution of the program
}   
