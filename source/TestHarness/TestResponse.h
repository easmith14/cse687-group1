/*
CSE687 - Object Oriented Design
Syracuse University
///////////////////////////////////////////////////////////
// Final Project by Aaron Mendelsohn, Evan Smith, Stephen Woodard, Mike Rice
///////////////////////////////////////////////////////////
5/13/2021
*/
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