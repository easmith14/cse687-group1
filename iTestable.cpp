/*
Aaron Mendelsohn
CIS 687 - M401 Object Oriented Design
Syracuse University
///////////////////////////////////////////////////////////
// Final Project by Aaron Mendelsohn to use polymorhism
///////////////////////////////////////////////////////////
3/18/2020
*/

#include "pch.h"
#include "iTestable.h"
#include <string>
#include <iostream>
#include <vector>


using std::string;
using std::cout;
using std::vector;

iTestable::iTestable()
{
	// no body needed. everthing was done in the initialization list
}

// initializer constructor
iTestable::iTestable(string bName, string bType, double g, int nSat, double dFromEarth, double sHeight)
{
	setbodyName(bName);
	setbodyType(bType);
	setgravity(g);
	setnumberSatellites(nSat);
	setdistanceFromEarth(dFromEarth);
	setsurfaceHeight(sHeight);
}

iTestable::~iTestable()
{
	// nothing to do at this time.
}

string iTestable::getbodyName() {
	return bodyName;
}

string iTestable::getbodyType() {
	return bodyType;
}

int iTestable::getnumberSatellites() {
	return numberSatellites;
}

double iTestable::getGravity() {
	return gravity;
}

double iTestable::getdistanceFromEarth() {
	return distanceFromEarth;
}

// base class to print info regarding central body
void iTestable::printinfo() {
	cout << "Welcome to the solar system the central body is: \n";
	cout << bodyName << " is a " << bodyType << " which is " << distanceFromEarth << " astronomical units from Earth.\n";
	cout << bodyName << " has " << numberSatellites << " orbiting satellites\n";
}

void iTestable::setnumberSatellites(int a) {
	numberSatellites = a;
}

void iTestable::setdistanceFromEarth(double b) {
	distanceFromEarth = b;
}

void iTestable::setgravity(double c) {
	gravity = c;
}

void iTestable::setbodyName(string d) {
	bodyName = d;
}

void iTestable::setbodyType(string e) {
	bodyType = e;
}

void iTestable::setsurfaceHeight(double a) {
	surfaceHeight = a;
}

double iTestable::getsurfaceHeight() {
	return surfaceHeight;
}

void iTestable::runBIST() { // BIST = built in self test
	// dummy test function 1
	// create test results node
	testNode* test1 = new testNode;
	test1->test_num = 1; // test sequence number
	test1->test_name = "test1"; // name of test
	test1->test_result = false; // pass fail
	test1->test_notes = "placeholder notes1"; // placeholder for test comments
	
	testResults.push_back(test1);
	// dummy tests function 2
	testNode* test2 = new testNode;
	test2->test_num = 2; // test sequence number
	test2->test_name = "test2"; // name of test
	test2->test_result = true; // pass fail
	test2->test_notes = "placeholder notes2"; // placeholder for test comments

	testResults.push_back(test2);
}