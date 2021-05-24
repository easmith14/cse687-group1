/*
CSE687 - Object Oriented Design
Syracuse University
///////////////////////////////////////////////////////////
// Final Project by Aaron Mendelsohn, Evan Smith, Stephen Woodward, Mike Rice
///////////////////////////////////////////////////////////
5/13/2021
*/

#include <vector>
#include <iostream>
#include <thread>
#include <mutex>

#include "Logger.h"
#include "TestProfileLibrary.h"
#include "iTestable.h"
#include "UserPrompter.h"
#include "TestExecutor.h"

using std::cout;
using std::cin;
using std::to_string;
std::mutex mtx;

void TestExecutor::Execute()
{
	//get tests to perform
	TestProfileLibrary library;
	mtx.lock();
	vector<iTestable*> classesToTest = library.GetTestList();
	mtx.unlock();
	//make logger
    UserPrompter prompter;
	int maxLoggingLevel = 3;
	mtx.lock();
	Logger logger(prompter.promptForIntWithinRange("Enter Logging Level (0-" + to_string(maxLoggingLevel) + "): ", 0, maxLoggingLevel));
	mtx.unlock();

	std::cout << "\n  in executor function thread id = " << std::this_thread::get_id() << "\n";

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

