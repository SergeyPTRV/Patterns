#include <iostream>

using namespace std;

class Data // Class representing the data structure that will be iterated over, which contains an array of integers and provides methods to access the data and its size
{
    int *data; // Pointer to an array of integers that holds the data to be iterated over
    int size; // Integer representing the size of the data array, which is used to determine the bounds of iteration
public:
    friend class Iterator; // Declare the Iterator class as a friend of the Data class, allowing the Iterator to access the private members of the Data class for iteration purposes
    Data() : data(nullptr), size(0) {} // Default constructor to initialize the Data object with a null pointer and size of 0, indicating that there is no data to iterate over 
    Data(int *d, int s) : data(d), size(s) {} // Constructor to initialize the Data object with a pointer to an array of integers and its size, allowing the object to manage the data and provide access to it for iteration
    Data(const Data& other) // Copy constructor to create a new Data object by copying the data and size from another Data object, allowing for the creation of a new instance with the same data for iteration purposes
    {
        size = other.size;
        if (other.data != nullptr) // Check if the other Data object has a non-null data pointer before copying the data, ensuring that we only attempt to copy data if it exists
        {
            data = new int[size];
            for (int i = 0; i < size; ++i) 
            {
                data[i] = other.data[i];
            }
        } 
        else 
        {
            data = nullptr;
        }
    }
    Data& operator=(const Data& other) 
    {
    if (this == &other) // Check for self-assignment by comparing the address of the current object with the address of the other object, and return the current object if they are the same to avoid unnecessary copying
    {
        return *this;
    }

    delete[] data;  // Clean up existing data to prevent memory leaks before copying new data from the other object

    size = other.size;
    if (other.data != nullptr) { // Check if the other Data object has a non-null data pointer before copying the data, ensuring that we only attempt to copy data if it exists 
        data = new int[size];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    } else {
        data = nullptr;
    }

    // 4. Возвращаем ссылку на текущий объект
    return *this;
}    
    int getSize() const { return size; } // Method to return the size of the data array, which is used by the iterator to determine the bounds of iteration
    int getData(int index) const { return data[index]; } // Method to return the integer value at a specific index in the data array, which is used by the iterator to access the data during iteration
    int pushBack(int value) { // Method to add a new integer value to the end of the data array, which allows for dynamic resizing of the data structure as new values are added
        int *newData = new int[size + 1]; // Create a new array of integers with a size one greater than the current size to accommodate the new value
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i]; // Copy existing values from the old data array to the new data array
        }
        newData[size] = value; // Add the new value to the end of the new data array
        delete[] data; // Delete the old data array to free up memory
        data = newData; // Update the data pointer to point to the new data array
        return ++size; // Increment the size of the data and return the new size
    }
    int popBack() { // Method to remove the last integer value from the data array, which allows for dynamic resizing of the data structure as values are removed
        if (size == 0) return -1; // Check if the data array is empty and return -1 to indicate that there are no values to pop
        int value = data[size - 1]; // Store the value of the last element in the data array before removing it
        int *newData = new int[size - 1]; // Create a new array of integers with a size one less than the current size to accommodate the remaining values after popping
        for (int i = 0; i < size - 1; ++i) {
            newData[i] = data[i]; // Copy existing values from the old data array to the new data array, excluding the last element that is being popped
        }
        delete[] data; // Delete the old data array to free up memory
        data = newData; // Update the data pointer to point to the new data array
        --size; // Decrement the size of the data to reflect the removal of an element
        return value; // Return the value that was popped from the data array
    }

    ~Data() { delete[] data; } // Destructor to clean up the dynamically allocated data array when the Data object is destroyed, preventing memory leaks 
}; 

class Iterator // Class representing an iterator for the Data class, which provides methods to traverse the data structure and access its elements in a sequential manner
{
    const Data &data; // Reference to the Data object that the iterator will traverse, allowing the iterator to access the data and its size for iteration purposes
    int index; // Integer representing the current index of the iteration, which is used to keep track of the position within the data array during traversal
public:
    Iterator(const Data &d) : data(d), index(0) {} // Constructor to initialize the iterator with a reference to a Data object and set the initial index to 0, indicating the start of the iteration
    bool hasNext() const { return index < data.getSize(); } // Method to check if there are more elements to iterate over by comparing the current index with the size of the data array, returning true if there are more elements and false if the end of the data array has been reached
    int next() { return data.getData(index++); } // Method to return the next integer value in the data array and increment the index to move to the next position for the next call to next(), allowing for sequential access to the elements of the data array during iteration
    void operator++() { ++index; } // Method to increment the index, allowing for sequential traversal of the data array during iteration   
    void operator--() { --index; } // Method to decrement the index, allowing for reverse traversal of the data array during iteration  
    int operator*() const { return data.getData(index); } // Method to dereference the iterator and return the current integer value in the data array at the current index, allowing for access to the element at the current position during iteration    
    bool operator() () const { return index != data.getSize() + 1; } // Method to check if the iterator has more elements to iterate over by comparing the current index with the size of the data array, returning true if there are more elements and false if the end of the data array has been reached, allowing for use in range-based for loops and other iteration contexts    
    void reset() { index = 0; } // Method to reset the index back to the beginning of the data array, allowing for re-iteration over the elements of the data array from the start  
};

bool operator==(const Data &d1, const Data &d2) // Overloaded equality operator to compare two Data objects, which checks if the sizes of the data arrays are equal and if all corresponding elements in the data arrays are equal, returning true if the Data objects are considered equal and false otherwise
{
    if (d1.getSize() != d2.getSize()) return false; // Check if the sizes of the data arrays are different and return false if they are not equal
    for (int i = 0; i < d1.getSize(); ++i) {
        if (d1.getData(i) != d2.getData(i)) return false; // Check if any corresponding elements in the data arrays are different and return false if they are not equal
    }
    return true; // Return true if the sizes of the data arrays are equal and all corresponding elements are equal, indicating that the Data objects are considered equal
}

int main() {
    Data data1; // Create an instance of the Data class to represent the data structure that will be iterated over
    data1.pushBack(1); // Add the integer value 1 to the data array using the pushBack method
    data1.pushBack(2); // Add the integer value 2 to the data array using the pushBack method
    data1.pushBack(3); // Add the integer value 3 to the data array using the pushBack method

    Iterator it(data1); // Create an instance of the Iterator class, passing a reference to the Data object to initialize the iterator for traversal

    cout << "data1" <<endl;
    while (it.hasNext()) { // Use a while loop to iterate over the elements in the data array as long as there are more elements to iterate over, checking with the hasNext method
        cout << it.next() << " "; // Output the next integer value in the data array followed by a space, using the next method to access each element during iteration
    }
    cout << endl; // Output a newline character after iterating through all elements in the data array

    Data data2(data1); // Create another instance of the Data class to represent a second data structure for comparison
    Iterator it2(data2); // Create an instance of the Iterator class for the second Data object, allowing for traversal of the second data structure
    
    cout << "data2" <<endl;
    while (it2.hasNext()) { // Use a while loop to iterate over the elements in the data array as long as there are more elements to iterate over, checking with the hasNext method
        cout << it2.next() << " "; // Output the next integer value in the data array followed by a space, using the next method to access each element during iteration
    }
    cout << endl; // Output a newline character after iterating through all elements in the data array

    cout << "\nData objects are " << (data1 == data2 ? "equal" : "not equal") << endl; // Output a message indicating whether the two Data objects are considered equal or not by using the overloaded equality operator to compare them 

    data2.pushBack(4); // Add the integer value 4 to the second data array using the pushBack method, which will make the two Data objects different in terms of their contents 
    cout << "After modifying data2, Data objects are " << (data1 == data2 ? "equal" : "not equal") << endl; // Output a message indicating whether the two Data objects are considered equal or not after modifying the second Data object, which should now be different from the first Data object due to the addition of a new element    

    cout << "data1" <<endl;
    it.reset(); // Reset the iterator for the first Data object back to the beginning of the data array, allowing for re-iteration over the elements of the data array from the start   
    while (it.hasNext()) { // Use a while loop to iterate over the elements in the data array as long as there are more elements to iterate over, checking with the hasNext method
        cout << it.next() << " "; // Output the next integer value in the data array followed by a space, using the next method to access each element during iteration
    }
    cout << endl; // Output a newline character after iterating through all elements in the data array

    cout << "data2" <<endl;
    it2.reset(); // Reset the iterator for the second Data object back to the beginning of the data array, allowing for re-iteration over the elements of the data array from the start 
    while (it2.hasNext()) { // Use a while loop to iterate over the elements in the data array as long as there are more elements to iterate over, checking with the hasNext method
        cout << it2.next() << " "; // Output the next integer value in the data array followed by a space, using the next method to access each element during iteration
    }
    cout << endl; // Output a newline character after iterating through all elements in the data array

    return 0; // Return 0 to indicate successful execution of the program
}   
