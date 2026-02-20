/**
 * @file Builder.cpp
 * @brief Implementation of the Builder Creational Pattern.
 * * @details Separates the construction of a complex object from its representation. 
 * This allows for a step-by-step construction process, which is critical in 
 * Mission-Critical systems to ensure all safety parameters are initialized 
 * correctly before the object is used.
 * * @design Highly recommended for initializing complex Hardware Peripheral 
 * configurations (e.g., initializing a multi-channel DMA controller).
 * @author Sergey Petrov
 * @date 2026-02-02
*/

 #include <iostream>
#include <string>

using namespace std;   

// Phone interface
class Phone 
{
    string data;
public:
    Phone()
    {
        data = "Generic Phone Data";
    }    
    string aboutPhone()
    {
        return data;
    }
    void appendData(string str)
    {
        data += " | " + str;    
    }
};

// Builder interface
class PhoneBuilder 
{
protected:
    Phone* phone;
public:
    PhoneBuilder()
    {
        phone = new Phone();
    }
    virtual void buildScreen() = 0;
    virtual void buildBattery() = 0;
    virtual void buildCamera() = 0;
    Phone* getPhone()
    {
        return phone;
    }
    virtual ~PhoneBuilder()
    {
        delete phone;
    }
};  

// Concrete Builder for Basic Phone
class BasicPhoneBuilder : public PhoneBuilder 
{
public:
    void buildScreen() override
    {
        phone->appendData("Basic Screen");
    }
    void buildBattery() override
    {
        phone->appendData("Basic Battery");
    }
    void buildCamera() override
    {
        phone->appendData("Basic Camera");
    }
};  
// Concrete Builder for Advanced Phone
class AdvancedPhoneBuilder : public PhoneBuilder 
{
public:
    void buildScreen() override
    {
        phone->appendData("Advanced Screen with High Resolution");
    }           
    void buildBattery() override
    {
        phone->appendData("Long-lasting Advanced Battery");
    }
    void buildCamera() override
    {
        phone->appendData("High Megapixel Advanced Camera");
    }
};  

// Director
class PhoneDirector 
{
    PhoneBuilder* builder;
public:
    void setBuilder(PhoneBuilder* b)
    {
        builder = b;
    }
    Phone* construct()
    {
        builder->buildScreen();
        builder->buildBattery();
        builder->buildCamera();
        return builder->getPhone();
    }
};

#define V1
int main() 
{
    #ifdef V1

    PhoneDirector director;

    PhoneBuilder* basicBuilder = new BasicPhoneBuilder();
    director.setBuilder(basicBuilder);

    Phone* basicPhone = director.construct();
    cout << "Basic Phone: " << basicPhone->aboutPhone() << endl;
    //delete basicBuilder;
    delete basicPhone;  

    PhoneBuilder* advancedBuilder = new AdvancedPhoneBuilder();
    director.setBuilder(advancedBuilder);

    Phone* advancedPhone = director.construct();
    cout << "Advanced Phone: " << advancedPhone->aboutPhone() << endl;
    //delete advancedBuilder;
    delete advancedPhone;

    #endif

    return 0;
}
