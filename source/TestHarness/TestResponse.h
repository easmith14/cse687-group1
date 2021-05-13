#pragma once
#include<string>
#include <vector>
#include "TestResult.h"

using std::string;
using std::vector;

class TestResponse
{
public:
	TestResponse()
		:Success(true)
	{

	}

	vector<TestResult> Results;
	bool Success;
	string ClassName;
	string Notes;
};