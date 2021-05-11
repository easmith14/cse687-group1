#include "TestProfileLibrary.h"

using std::cout;
using std::cin;
using std::endl;


//constructor
TestProfileLibrary::TestProfileLibrary()
{
    //cout << "TestProfileLibrary created\n";
}



//destructor
TestProfileLibrary::~TestProfileLibrary()
{
    //cout << "TestProfileLibrary destroyed\n";
}



//instantiates objects and returns vector of created objects
vector<iTestable> TestProfileLibrary::getTestList()
{
    vector<iTestable> testProfileVector;
    vector<iTestable> allAvailableTests;
    int selection = 0;
  
    /******************
    *Replace/insert desired test class types here */ 

    iTestable testObj1;
    allAvailableTests.push_back(testObj1);
    

    //****************
        

    cout << "Classes available for test\n";
    
    for (int i = 0; i < allAvailableTests.size(); i++)
    {
        cout << i+1 << ": " << typeid(allAvailableTests[i]).name() << endl;
    }

    cout << endl << "Please select desired test class: ";
    cin >> selection;


    /******************
    *Add else if for additional desired test class selections */

    if (selection == 1)
    {
        testProfileVector.push_back(testObj1);
    }

    //****************


    return testProfileVector;

}
