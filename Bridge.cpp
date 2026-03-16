/*
 * @file Bridge.cpp
 * @brief Implementation of the Bridge design pattern.
 * @details The Bridge pattern decouples an abstraction from its implementation so that the two can vary independently. 
 * In this example, `DataProcessor` acts as the abstraction, while `DataReader` provides the implementation. 
 * This approach is highly effective in embedded systems and industrial automation, as it allows changing 
 * data sources (CSV, JSON, XML) at runtime without modifying the processing logic, or vice versa.
 * @author Sergey Petrov
 * @date 2026-03-16
 */

#include <iostream>
#include <string>

using namespace std;

// DataReader interface
class DataReader
{
public:
    virtual string readData() = 0; // Pure virtual method to read data, to be implemented by concrete readers
};

// Concrete DataReader implementations for CSV files
class CSVReader : public DataReader
{
public:
    string readData() override // Implement reading data from a CSV file
    {
        return "Data read from CSV file";
    }
}; 

// Concrete DataReader implementations for JSON files
class JSONReader : public DataReader
{
public:
    string readData() override // Implement reading data from a JSON file
    {
        return "Data read from JSON file";
    }
};

// Concrete DataReader implementations for XML files
class XMLReader : public DataReader
{
public:
    string readData() override // Implement reading data from an XML file
    {
        return "Data read from XML file";
    }
};

// DataProcessor class that uses a DataReader to process data
class DataProcessor
{
    DataReader* _reader; // Composition: DataProcessor has a DataReader
public:
    DataProcessor(DataReader* reader) : _reader(reader) {} // Constructor to initialize DataProcessor with a DataReader
    string processData() // Method to process data using the current DataReader
    {
        return _reader->readData();
    }
    void setReader(DataReader* reader) // Method to change the DataReader at runtime
    {
        _reader = reader; // Change the reader at runtime
    }
    virtual void transmitData() = 0; // Pure virtual method to transmit data, to be implemented by concrete processors
};

// Concrete DataProcessor for CSV data
class CSVDataProcessor : public DataProcessor
{
public:    
    CSVDataProcessor(DataReader* reader) : DataProcessor(reader) {} // Constructor to initialize CSVDataProcessor with a DataReader
    void transmitData() override // Implement transmitting CSV data
    {
        cout << "Transmitting CSV data: " << processData() << endl;
    }
};

// Concrete DataProcessor for JSON data
class JSONDataProcessor : public DataProcessor
{public:
    JSONDataProcessor(DataReader* reader) : DataProcessor(reader) {} // Constructor to initialize JSONDataProcessor with a DataReader
    void transmitData() override
    {
        cout << "Transmitting JSON data: " << processData() << endl;
    }
};

// Concrete DataProcessor for XML data
class XMLDataProcessor : public DataProcessor
{public:
    XMLDataProcessor(DataReader* reader) : DataProcessor(reader) {} // Constructor to initialize XMLDataProcessor with a DataReader
    void transmitData() override
    {
        cout << "Transmitting XML data: " << processData() << endl;
    }
};  

int main () 
{
    cout << "Pattern - Bridge" << endl;
    
    DataProcessor* processor = new CSVDataProcessor(new CSVReader());
    processor->transmitData();
    processor->setReader(new JSONReader()); 
    processor->transmitData();
    processor->setReader(new XMLReader());
    processor->transmitData();

    processor = new XMLDataProcessor(new CSVReader());
    processor->transmitData();
    processor->setReader(new JSONReader());
    processor->transmitData();
    processor->setReader(new XMLReader());
    processor->transmitData();

    processor = new JSONDataProcessor(new CSVReader());
    processor->transmitData();
    processor->setReader(new JSONReader());
    processor->transmitData();
    processor->setReader(new XMLReader());
    processor->transmitData();

    return 0;
}