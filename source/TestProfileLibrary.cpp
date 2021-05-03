#include "TestProfileLibrary.h"

using std::cout;

//constructor
TestProfileLibrary::TestProfileLibrary()
{
    cout << "TestProfileLibrary created\n";
}

//destructor
TestProfileLibrary::~TestProfileLibrary()
{
    cout << "TestProfileLibrary destroyed\n";
}

//instantiates objects and returns vector of created objects
void TestProfileLibrary::getTestList(vector<iTestable>& objectsVector)
{
    iTestable testObj1;
    iTestable testObj2;

    objectsVector.push_back(testObj1);
    objectsVector.push_back(testObj2);
}