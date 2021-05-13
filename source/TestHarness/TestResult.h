#pragma once

#include<string>

using std::string;

class TestResult
{
public:
	int LogLevel; //level of logging that should output this information
	int TestNumber; // test sequence number
	string TestName; // name of test
	bool TestSuccess; // pass fail
	string TestNotes; // placeholder for test comments
};