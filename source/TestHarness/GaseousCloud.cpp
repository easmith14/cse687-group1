#include "GaseousCloud.h"
#include <sstream>

TestResponse GaseousCloud::Test()
{
	TestResponse response;

	//test 1 - always fails
	TestResult sadResult;
	sadResult.LogLevel = 3;
	sadResult.TestName = "Sad Test";
	sadResult.TestNotes = "Always Fails! :(";
	sadResult.TestNumber = 1;
	sadResult.TestSuccess = false;
	response.Results.push_back(sadResult);

	//test 2 - is color red?
	TestResult isColorRed;
	isColorRed.TestName = "Is Color Red?";
	isColorRed.TestNumber = 2;
	isColorRed.TestSuccess = _color == "Red";
	response.Results.push_back(isColorRed);

	//test 3 - is the sum <= 100
	TestResult isExpanding;
	isExpanding.TestName = "Is The Cloud Still Expanding?";
	isExpanding.TestNumber = 3;
	isExpanding.TestSuccess = _isExpanding;
	response.Results.push_back(isExpanding);

	response.Success = false;
	response.Notes = "Uh oh... this cloud is headed right towards us...";

	return response;
}

string GaseousCloud::GetClassDescription()
{
	//recreate the constructor
	std::ostringstream stringStream;
	stringStream << typeid(*this).name() << "(" << _name << ", "
		<< _xPosition << ", "
		<< _yPosition << ", "
		<< _color << ", "
		<< _isExpanding << ")";
	return stringStream.str();
}
