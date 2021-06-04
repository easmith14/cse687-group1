/*
CSE687 - Object Oriented Design
Syracuse University
///////////////////////////////////////////////////////////
// Final Project by Aaron Mendelsohn, Evan Smith, Stephen Woodward, Mike Rice
///////////////////////////////////////////////////////////
5/13/2021
*/

#include "CelestialBody.h"
#include "TestResult.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds


using std::string;
using std::cout;
using std::vector;


// initializer constructor
CelestialBody::CelestialBody(string bName, string bType, double g, int nSat, double dFromEarth, double sHeight)
{
	setbodyName(bName);
	setbodyType(bType);
	setgravity(g);
	setnumberSatellites(nSat);
	setdistanceFromEarth(dFromEarth);
	setsurfaceHeight(sHeight,sHeight);
}

string CelestialBody::getbodyName() {
	return bodyName;
}

string CelestialBody::getbodyType() {
	return bodyType;
}

int CelestialBody::getnumberSatellites() {
	return numberSatellites;
}

double CelestialBody::getGravity() {
	return gravity;
}

double CelestialBody::getdistanceFromEarth() {
	return distanceFromEarth;
}

// base class to print info regarding central body
void CelestialBody::printinfo() {
	cout << "Welcome to the solar system the central body is: \n";
	cout << bodyName << " is a " << bodyType << " which is " << distanceFromEarth << " astronomical units from Earth.\n";
	cout << bodyName << " has " << numberSatellites << " orbiting satellites\n";
}

void CelestialBody::setnumberSatellites(int a) {
	numberSatellites = a;
}

void CelestialBody::setdistanceFromEarth(double b) {
	distanceFromEarth = b;
}

void CelestialBody::setgravity(double c) {
	gravity = c;
}

void CelestialBody::setbodyName(string d) {
	bodyName = d;
}

void CelestialBody::setbodyType(string e) {
	bodyType = e;
}

void CelestialBody::setsurfaceHeight(double a, double b) {
		
		if (b == 0)
		{
			throw "Division by zero condition!";
		}
		else {
			surfaceHeight=(a / b);
		}
		srand(time(NULL));
		int runtime = rand() % 5 + 1;
		//cout << runtime << "thread delay time\n";
		std::this_thread::sleep_for(std::chrono::seconds(runtime));
}

double CelestialBody::getsurfaceHeight() {
	return surfaceHeight;
}

TestResponse CelestialBody::Test() {

	vector<TestResult> results;
	// dummy test function 1
	// create test results node
	TestResult result1;

	result1.TestNumber = 1; // test sequence number
	result1.TestName = "test1"; // name of test
	result1.TestSuccess = false; // pass fail
	result1.TestNotes = "placeholder notes1"; // placeholder for test comments
	
	results.push_back(result1);
	// dummy tests function 2
	TestResult result2;

	result2.TestNumber = 2; // test sequence number
	result2.TestName = "test2"; // name of test
	result2.TestSuccess = true; // pass fail
	result2.TestNotes = "placeholder notes2"; // placeholder for test comments

	results.push_back(result2);

	TestResult result3;
	result3.TestNumber = 3; // test sequence number
	result3.TestName = "test3"; // name of test
	int a = distanceFromEarth;
	int b = numberSatellites;

	setsurfaceHeight(a, b);

	result3.TestSuccess = true; // pass fail
	 // placeholder for test comments

	results.push_back(result3);

	TestResponse response; //function decides whether it was a success as a whole
	response.Results = results;
	response.Success = true;

	return response;
}

string CelestialBody::GetClassDescription()
{
	//recreate the constructor
	std::ostringstream stringStream;
	stringStream << typeid(*this).name() << "(" << bodyName << ", " 
												<< bodyType << ", " 
												<< gravity << ", " 
												<< numberSatellites << ", " 
												<< distanceFromEarth << ", " 
												<< surfaceHeight << ")";
	return stringStream.str();
}
