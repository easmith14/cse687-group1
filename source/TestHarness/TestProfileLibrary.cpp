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
#include "Spacecraft.h"
#include "GaseousCloud.h"

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
    //vector<iTestable*> testProfileVector;
    vector<iTestable*> allAvailableTests;
    //vector<string> allAvailableTestNames;

    /******************
    *Replace/insert desired test class types here */ 

    //celestialBodies
    CelestialBody* celestialBody1 = new CelestialBody("The Sun", "star", 274.0, 0, 1, 3000);
    allAvailableTests.push_back(celestialBody1);
    CelestialBody* celestialBody2 = new CelestialBody("BlackHole Sun", "star", 274.0, 1, 0, 3000);
    allAvailableTests.push_back(celestialBody2);

    //spacecraft
    Spacecraft* spaceCraft1 = new Spacecraft("HydraFleet", 80, 50);
    allAvailableTests.push_back(spaceCraft1);
    Spacecraft* spaceCraft2 = new Spacecraft("Tesla", 0, 34);
    allAvailableTests.push_back(spaceCraft2);

    //gaseous clouds
    GaseousCloud* gaseousCloud1 = new GaseousCloud("Oort", 2222, 454, "Red", false);
    allAvailableTests.push_back(gaseousCloud1);
    GaseousCloud* gaseousCloud2 = new GaseousCloud("Mork", 3434, 3455, "Purple", true);
    allAvailableTests.push_back(gaseousCloud2);

    //****************
        

    //cout << "Classes available for test\n";
    //
    //for (int i = 0; i < allAvailableTests.size(); i++)
    //{
    //    cout << i+1 << ": " << allAvailableTestNames[i] << "\n";
    //}

   // UserPrompter prompter;

    //int selection = prompter.promptForIntWithinRange("Please select desired test class: ", 1, allAvailableTests.size());
    //srand(time(NULL));
    //int selection = rand() % 2 + 1;

    /******************
    *Add else if for additional desired test class selections */

    //testProfileVector.push_back(allAvailableTests.at(selection - 1));

    //****************


    return allAvailableTests;
}
