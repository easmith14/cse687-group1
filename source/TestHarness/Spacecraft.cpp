#include "Spacecraft.h"
#include <sstream>

TestResponse Spacecraft::Test()
{
	TestResponse response;

	//test 1 - always works
	TestResult happyResult;
	happyResult.LogLevel = 3;
	happyResult.TestName = "Happy Test";
	happyResult.TestNotes = "Always Succeeds! :)";
	happyResult.TestNumber = 1;
	happyResult.TestSuccess = true;
	response.Results.push_back(happyResult);

	//test 2 - is X > Y?
	TestResult xGreaterResult;
	xGreaterResult.TestName = "Is X Position Greater Than Y?";
	xGreaterResult.TestNumber = 2;
	xGreaterResult.TestSuccess = _xPosition > _yPosition;
	response.Results.push_back(xGreaterResult);

	//test 3 - is the sum <= 100
	TestResult sumLessThan100;
	sumLessThan100.TestName = "Is The Sum Of The Positions <= 100?";
	sumLessThan100.TestNumber = 3;
	sumLessThan100.TestSuccess = _xPosition + _yPosition <= 100;
	response.Results.push_back(sumLessThan100);

	response.Success = true;
	response.Notes = "This spacecraft is currently flying! Wow!";

	return response;
}

string Spacecraft::GetClassDescription()
{
	//recreate the constructor
	std::ostringstream stringStream;
	stringStream << typeid(*this).name() << "(" << _name << ", "
		<< _xPosition << ", "
		<< _yPosition << ")";
	return stringStream.str();
}
