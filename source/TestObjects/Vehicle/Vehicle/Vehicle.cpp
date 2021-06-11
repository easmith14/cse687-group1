#include <string>
#include "pch.h"
#include "Vehicle.h"
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
