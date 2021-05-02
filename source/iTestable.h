/*
Aaron Mendelsohn
CSE687 - Object Oriented Design
Syracuse University
///////////////////////////////////////////////////////////
// Final Project by Aaron Mendelsohn
///////////////////////////////////////////////////////////
4/29/2021
*/

#ifndef __iTestable_H__
#define __iTestable_H__

#include <string>
#include <vector>

using std::string;


typedef struct testNode {
	int test_num; // test sequence number
	string test_name; // name of test
	bool test_result; // pass fail
	string test_notes; // placeholder for test comments
} testNode;

class iTestable
{
public:

	// default constructor
	iTestable();

	// initialization constructor
	iTestable(string bodyName, string bodyType, double gravity, int numberSatellites, double distanceFromEarth, double surfaceHeight);

	// destructor
	~iTestable();

	// set'ers and get'ers

	virtual string getbodyName();
	virtual string getbodyType();
	virtual int getnumberSatellites();
	virtual double getGravity();
	virtual double getdistanceFromEarth();
	virtual double getsurfaceHeight();

	
	virtual void printinfo();
	virtual void setnumberSatellites(int);
	virtual void setdistanceFromEarth(double);
	virtual void setgravity(double);
	virtual void setbodyName(string);
	virtual void setbodyType(string);
	virtual void setsurfaceHeight(double);
	virtual void runBIST();

	std::vector<testNode*> testResults;

private:
	string bodyName;
	string bodyType;
	int numberSatellites;
	double gravity;
	double distanceFromEarth;
	double surfaceHeight;
	
};

#endif