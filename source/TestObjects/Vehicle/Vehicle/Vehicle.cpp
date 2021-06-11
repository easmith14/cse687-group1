#include <string>
#include "pch.h"
#include "Vehicle.h"
#include "../../../TestHarness/TestResponse.h"
#include "../../../TestHarness/TestResult.h"
using std::string;

static string _VehicleName;
static int _xPos;
static int _yPos;
static int _xVel;
static int _yVel;
static string _VehicleColor;

void create_vehicle(const string a, const int b, const int c, const int d, const int e)
{
	_VehicleName = a;
	_xPos = b;
	_yPos = c;
	_xVel = d;
	_yVel = e;

	if (_xVel + _yVel >= 100)
	{
		_VehicleColor = "RED";
	}
	else
	{
		_VehicleColor = "DONT CARE";
	}
}

void move_vehicle(const int a, const int b)
{
	_xPos = a;
	_yPos = b;
}

void accelerate_vehicle(const int a, const int b)
{
	_xVel = _xVel + a;
	_yVel = _yVel + b;
}

void decelerate_vehicle(const int a, const int b)
{
	_xVel = _xVel - a;
	_yVel = _yVel - b;
}

int get_vehicle_xpos()
{
	return _xPos;
}

int get_vehicle_ypos()
{
	return _yPos;
}

void update_vehicle_pos(int a)
{
	// a is a unit of time over which vehicle has traveled
	_xPos = _xPos + _xVel * a;
	_yPos = _yPos + _yVel * a;
}

TestResponse test()
{
	TestResponse response;

	// Test Case 1 : Passing Case
	TestResult passResult;
	passResult.LogLevel = 3;
	passResult.TestName = "PASS Test";
	passResult.TestNotes = "This test will always pass";
	passResult.TestNumber = 1; 
	passResult.TestSuccess = true;
	response.Results.push_back(passResult);

	// Test Case 2 : Position Update Check
	TestResult posUpdateCheck;
	posUpdateCheck.LogLevel = 3;
	posUpdateCheck.TestName = "Position Update Check";
	posUpdateCheck.TestNotes = "Updating position to check if function works as intended";
	posUpdateCheck.TestNumber = 2;
	int origXPos = get_vehicle_xpos();
	int origYPos = get_vehicle_ypos();
	update_vehicle_pos(10);
	if (origXPos != get_vehicle_xpos() || _xVel == 0)
	{
		if (origYPos != get_vehicle_ypos() || _yVel == 0)
		{
			posUpdateCheck.TestSuccess = true;
		}
	}
	else
	{
		posUpdateCheck.TestSuccess = false;
	}
	response.Results.push_back(posUpdateCheck);

	// Test Case 3 : Brake Check
	TestResult brakeCheck;
	brakeCheck.LogLevel = 3;
	brakeCheck.TestName = "Brake Check";
	brakeCheck.TestNotes = "Check the brakes of the vehicle by attempting to decelerate";
	brakeCheck.TestNumber = 3;
	int origXVel = _xVel;
	int origYVel = _yVel;
	decelerate_vehicle(1, 1);
	if (_xVel < origXVel && _yVel < origYVel)
	{
		brakeCheck.TestSuccess = true;
	}
	else
	{
		brakeCheck.TestSuccess = false;
	}
	response.Results.push_back(brakeCheck);
	response.Notes = "Testing of the Vehicle class is complete!";

	return response;
}
