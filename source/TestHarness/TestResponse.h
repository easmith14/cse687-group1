#pragma once

#include<string>
#include "TestResult.h"

using std::string;
using std::vector;

class TestResponse
{
public:
	TestResponse(vector<TestResult> results, bool success)
		: Results(results), Success(success)
	{
	};

	vector<TestResult> Results;
	bool Success;
};

