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
#include "WS2tcpip.h"

#pragma warning(disable : 4996)

using std::cout;
using std::cin;
using std::to_string;

//TestExecutor::TestExecutor(Logger* a)
//	: logger(a)
//{
//
//}

TestResponse TestExecutor::Execute(string dllToTest)
{
    typedef TestResponse(__cdecl* f_test_ptr)();
    char* cstr = new char[dllToTest.length() + 1];
    std::strcpy(cstr, dllToTest.c_str());
    HMODULE hGetMod = LoadLibraryA(cstr);

    // call the DLL function from here directly
    f_test_ptr test_ptr = (f_test_ptr)GetProcAddress(hGetMod, "test");

	TestResponse response;
	try
	{
		response = test_ptr();
	}
	catch (const char* msg)
	{
		response.Success = false;
		response.Notes = msg;
	}

    FreeLibrary(hGetMod);
	return response;

}

