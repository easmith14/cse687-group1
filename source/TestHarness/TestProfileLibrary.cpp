#include "TestProfileLibrary.h"
#include "UserPrompter.h"
#include "CelestialBody.h"

using std::cout;
using std::cin;

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
vector<iTestable*> TestProfileLibrary::GetTestList()
{
    vector<iTestable*> testProfileVector;
    vector<iTestable*> allAvailableTests;
    vector<string> allAvailableTestNames;

    /******************
    *Replace/insert desired test class types here */ 

    CelestialBody* celestialBody = new CelestialBody("The Sun", "star", 274.0, 0, 1, 3000);
    allAvailableTests.push_back(celestialBody);
    allAvailableTestNames.push_back(typeid(*celestialBody).name());
    

    //****************
        

    cout << "Classes available for test\n";
    
    for (int i = 0; i < allAvailableTests.size(); i++)
    {
        cout << i+1 << ": " << allAvailableTestNames[i] << "\n";
    }

    UserPrompter prompter;

    int selection = prompter.promptForIntWithinRange("Please select desired test class: ", 1, allAvailableTests.size());

    /******************
    *Add else if for additional desired test class selections */

    testProfileVector.push_back(allAvailableTests.at(selection - 1));

    //****************


    return testProfileVector;

}