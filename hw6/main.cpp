// Name: Nina Baffo
// Date: 11/03/22
// Assignment: Hw 6
// Note: Code was modified from Challenge Activity 11.3.1: Overriding member function.
// in the CIE ZyBook class textbook.

#include <iostream>
using namespace std;

class Computer {                        // baseclass (or superclass) Computer
public:
    explicit Computer(const float size = 0);    // Explicit constructor that has default values for all member variables.
    ~Computer();                                // Destructor
    Computer(const Computer & obj);             // Copy constructor
    Computer& operator = (const Computer& obj); // Copy assignment operator

    void setMemorySize(const float memoryVal);
    float getMemorySize() const;
    void setComputerStatus(const string usage, const string status);

    void print() {
        cout << "CPU usage: " << cpuUsage << endl;
        cout << "Internet status: " << internetStatus << endl;
        cout << "Memory size: " << *memorySize << endl;
    }

    // Description: public member function getCpuUsage() returns the cpuUsage
    // Input: None
    // Output: cpuUsage
    const string &getCpuUsage() {
        return cpuUsage;
    }

    // Description: public member function setCpuUsage(const string &cpuUsage) sets the private variable cpuUsage to be
    //              accessible in Laptop
    // Input: string cpuUsage
    // Output: None
    void setCpuUsage(const string &usage) {
        cpuUsage = usage;
    }

    // Description: public member function getInternetStatus() returns the internetStatus
    // Input: None
    // Output: InternetStatus
    const string &getInternetStatus(){
        return internetStatus;
    }

    // Description: public member function setInternetStatus(const string &internetStatus) sets the private variable
    //              internetStatus to be accessible in Laptop.
    // Input: string internetStatus
    // Output: None
    void setInternetStatus(const string &status) {
        internetStatus = status;
    }

private:
    string cpuUsage;
    string internetStatus;
    float* memorySize;
};

// Description: public member function setComputerStatus takes two strings and sets them to cpuUsage and internetStatus
// Input: const string usage, const string status
// Output: None
void Computer::setComputerStatus(const string usage, const string status) {
    cpuUsage = usage;
    internetStatus = status;
}

// Description: public member function setMemorySize(float *memorySize) should allocate memory for
//              memorySize if it is a nullptr. If the new command returns the nullptr, then the setter
//              should call return without doing anything.
// Input: float *memorySize
// Output: None
void Computer::setMemorySize(const float memoryVal) {
    *memorySize = memoryVal;
}

// Description: public member function getMemorySize() returns the floating-point value that
//              memorySize points to if memorySize is not the nullptr or zero otherwise.
// Input: None
// Output: memorySize
float Computer::getMemorySize() const {
    return *memorySize;
}

// Constructor. Memory Allocated here
Computer::Computer(const float size){
    memorySize = new float;
    *memorySize = 0;
    cpuUsage = "";
    internetStatus = "";
}

// Destructor. Memory De-allocated here.
Computer::~Computer(){
    cout << "In the Computer Destructor." << endl;
    print();
    delete memorySize;
}

// Copy constructor. Memory Allocated
Computer::Computer(const Computer & obj){
    memorySize = new float;
    *memorySize = obj.getMemorySize();
}

// Copy assignment operator
Computer& Computer::operator = (const Computer& obj){
    if (this != &obj){
        delete memorySize;
        memorySize = new float;
        *memorySize = *(obj.memorySize);
    }
    return *this;
}

// Derived class Laptop inherits Computer class
class Laptop : public Computer {
public:
    explicit Laptop(float size = 0, string wifi = ""): Computer(size), wifiQuality(wifi) {
        print();
    }
    ~Laptop() {
        cout<< "In the Laptop Destructor." << endl;
        print();
    }

    // Description: public member function setComputerStatus(string usage, string status, string quality)
    //              takes three user inputted strings and sets them to cpuUsage, internetStatus, wifiQuality
    // Input: string usage, string status, string quality
    // Output: None
    void setComputerStatus(const string usage, const string status, const string quality) {
        Computer::setCpuUsage(usage);
        Computer::setInternetStatus(status);
        wifiQuality = quality;
    };

    // Description: public member function print() prints out CPU usage, Internet Status and WiFi quality.
    //              Derived class has a member function with the same name and parameters as base class's function,
    //              so print() in class Laptop overrides print() in class Computer.
    // Input: None
    // Output: prints out CPU usage, Internet Status and WiFi quality
    void print() {
        Computer::print(); {
            cout << "WiFi quality: " << wifiQuality << endl;
        }
    }

private:
    string wifiQuality;
};

int main() {
    Laptop myLaptop; // create object of type Laptop class
    Laptop myLaptop2; // set and print myLaptop data
    myLaptop.setComputerStatus("25%", "connected", "good");
    myLaptop.print();
    myLaptop = myLaptop2; // copy class object using copy assignment operator
    myLaptop.setComputerStatus("30%", "connected", "bad"); // set myLaptop data
    cout << "myLaptop: ";
    myLaptop.print(); //print data values for each laptop object
    cout << "myLaptop2: ";
    myLaptop2.print();

    Computer myComputer;    // create an object of type Computer
    myComputer.setMemorySize(10);
    myComputer.getMemorySize();
    myComputer.print();
    myLaptop.setMemorySize(5);
    myLaptop.print();
    return 0;
}