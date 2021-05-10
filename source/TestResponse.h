#pragma once
#include<string>
#include <vector>
#include "TestResult.h"

using std::string;
using std::vector;

class TestResponse
{
public:
	vector<TestResult> results;
	bool success;

};