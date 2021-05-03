#pragma once

#include<string>

using std::string;

class TestResult
{
public:
	int Num; // test sequence number
	string Name; // name of test
	bool Result; // pass fail
	string Notes; // placeholder for test comments
};