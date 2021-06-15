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

#include "Logger.h"
#include "TestProfileLibrary.h"
#include "iTestable.h"
#include "UserPrompter.h"
#include "TestExecutor.h"

using std::cout;
using std::cin;
using std::to_string;

//TestExecutor::TestExecutor(Logger* a)
//	: logger(a)
//{
//
//}

TestResponse TestExecutor::Execute(iTestable* testClass)
{
	//std::cout << "\n  in executor function thread id = " << std::this_thread::get_id() << "\n";

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

	response.ClassName = testClass->GetClassDescription();

	return response;
	//logger->Log(response);
}

