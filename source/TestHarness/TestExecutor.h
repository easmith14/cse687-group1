/*
CSE687 - Object Oriented Design
Syracuse University
///////////////////////////////////////////////////////////
// Final Project by Aaron Mendelsohn, Evan Smith, Stephen Woodward, Mike Rice
///////////////////////////////////////////////////////////
5/13/2021
*/

#pragma once
#include "Logger.h"
#include "TestResponse.h"
#include "iTestable.h"

class TestExecutor
{
public:
	TestResponse Execute(string testClass);
};

