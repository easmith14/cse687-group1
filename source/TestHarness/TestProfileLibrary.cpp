/*
CSE687 - Object Oriented Design
Syracuse University
///////////////////////////////////////////////////////////
// Final Project by Aaron Mendelsohn, Evan Smith, Stephen Woodward, Mike Rice
///////////////////////////////////////////////////////////
5/13/2021
*/
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

    CelestialBody* celestialBody1 = new CelestialBody("The Sun", "star", 274.0, 0, 1, 3000);
    allAvailableTests.push_back(celestialBody1);
    allAvailableTestNames.push_back(typeid(*celestialBody1).name());
    CelestialBody* celestialBody2 = new CelestialBody("BlackHole Sun", "star", 274.0, 1, 0, 3000);
    allAvailableTests.push_back(celestialBody2);
    allAvailableTestNames.push_back(typeid(*celestialBody2).name());

 
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
