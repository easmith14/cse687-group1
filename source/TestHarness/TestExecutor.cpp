#include <vector>
#include <iostream>

#include "Logger.h"
#include "TestProfileLibrary.h"
#include "iTestable.h"
#include "UserPrompter.h"
#include "TestExecutor.h"

using std::cout;
using std::cin;
using std::to_string;

void TestExecutor::Execute()
{
	//get tests to perform
	TestProfileLibrary library;
	vector<iTestable*> classesToTest = library.GetTestList();

	//make logger
    UserPrompter prompter;
	int maxLoggingLevel = 3;
	Logger logger(prompter.promptForIntWithinRange("Enter Logging Level (0-" + to_string(maxLoggingLevel) + "): ", 0, maxLoggingLevel));

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

		logger.Log(response);
	}
}

