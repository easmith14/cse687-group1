/*
Aaron Mendelsohn
CIS 687 - M401 Object Oriented Design
Syracuse University
///////////////////////////////////////////////////////////
// Final Project by Aaron Mendelsohn to use polymorhism
///////////////////////////////////////////////////////////
3/18/2020
*/

#include "CelestialBody.h"
#include "TestResult.h"
#include <string>
#include <iostream>
#include <vector>


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
	
}

double CelestialBody::getsurfaceHeight() {
	return surfaceHeight;
}

TestResponse CelestialBody::Test() {

	vector<TestResult> results;
	// dummy test function 1
	// create test results node
	TestResult result1;

	result1.test_number = 1; // test sequence number
	result1.test_name = "test1"; // name of test
	result1.test_result = false; // pass fail
	result1.test_notes = "placeholder notes1"; // placeholder for test comments
	
	results.push_back(result1);
	// dummy tests function 2
	TestResult result2;

	result2.test_number = 2; // test sequence number
	result2.test_name = "test2"; // name of test
	result2.test_result = true; // pass fail
	result2.test_notes = "placeholder notes2"; // placeholder for test comments

	results.push_back(result2);

	TestResult result3;
	result3.test_number = 3; // test sequence number
	result3.test_name = "test3"; // name of test
	int a = 10;
	int b = 0;
	try
	{
		setsurfaceHeight(a, b);
	}
	catch (const char* msg)
	{
		result3.test_notes = msg;
	}
	result3.test_result = false; // pass fail
	 // placeholder for test comments

	results.push_back(result3);

	TestResponse response; //function decides whether it was a success as a whole
	response.results = results;
	response.success = true;

	return response;
}