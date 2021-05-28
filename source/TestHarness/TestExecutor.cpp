/*
CSE687 - Object Oriented Design
Syracuse University
///////////////////////////////////////////////////////////
// Final Project by Aaron Mendelsohn, Evan Smith, Stephen Woodard, Mike Rice
///////////////////////////////////////////////////////////
5/13/2021
*/

#include <vector>
#include <iostream>

#include "TestProfileLibrary.h"
#include "iTestable.h"
#include "UserPrompter.h"
#include "TestExecutor.h"
#include "Logger.h"

using std::cout;
using std::cin;

TestExecutor::TestExecutor(Logger* a)
	: logger(a)
{

}

void TestExecutor::Execute()
{
	//get tests to perform
	TestProfileLibrary library;
	vector<iTestable*> classesToTest = library.GetTestList();

	for (iTestable* testClass : classesToTest)
	{
		TestResponse response;

		try
		{
			response = testClass->Test();
		}
		catch (const char* msg)
		{
			response.Success = false;
			response.Notes = msg;
		}

		response.ClassName = testClass->GetTypeName();

		logger->Log(response);
	}
}

