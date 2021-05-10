/*
Aaron Mendelsohn
CSE687 - Object Oriented Design
Syracuse University
///////////////////////////////////////////////////////////
// Final Project by Aaron Mendelsohn
///////////////////////////////////////////////////////////
4/29/2021
*/

#pragma once

#include <string>
#include <vector>
#include "ITestable.h"
#include "TestResponse.h"

using std::string;


class CelestialBody : iTestable
{
public:

	// initialization constructor
	CelestialBody(string bodyName, string bodyType, double gravity, int numberSatellites, double distanceFromEarth, double surfaceHeight);

	// set'ers and get'ers

	string getbodyName();
	string getbodyType();
	int getnumberSatellites();
	double getGravity();
	double getdistanceFromEarth();
	double getsurfaceHeight();

	
	void printinfo();
	void setnumberSatellites(int);
	void setdistanceFromEarth(double);
	void setgravity(double);
	void setbodyName(string);
	void setbodyType(string);
	void setsurfaceHeight(double,double);


	//test function for harness compatibility
	TestResponse Test();

private:
	string bodyName;
	string bodyType;
	int numberSatellites;
	double gravity;
	double distanceFromEarth;
	double surfaceHeight;
};