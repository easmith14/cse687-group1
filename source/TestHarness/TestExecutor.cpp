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

    //// lol a lot of this is hard coded for now because I didn't think well enough ahead
    //if (dllToTest == "Character.dll")
    //{
    //    f_char_ptr create_character_ptr = (f_char_ptr)GetProcAddress(hGetMod, "create_character");
    //    cout << "\nPreparing to load DLL function...\n";
    //    create_character_ptr("Sigmar", 500);
    //    if (!create_character_ptr)
    //    {
    //        cout << "Failed to load function!!\n\n";
    //    }
    //    else
    //    {
    //        cout << "Function loaded!!\n\n";
    //    }
    //}
    //else if (dllToTest == "Vehicle.dll")
    //{
    //    f_vehicle_ptr create_vehicle_ptr = (f_vehicle_ptr)GetProcAddress(hGetMod, "create_vehicle");
    //    create_vehicle_ptr("Cybertruck", 30, 19, 4, 7);
    //    if (!create_vehicle_ptr)
    //    {
    //        cout << "Failed to load function!!\n\n";
    //    }
    //    else
    //    {
    //        cout << "Function loaded!!\n\n";
    //    }
    //}
    //else
    //{
    //    // Something probably went bad and didn't work so here is a random character
    //    f_char_ptr create_character_ptr = (f_char_ptr)GetProcAddress(hGetMod, "create_character");
    //    create_character_ptr("Grombrindal", 100);
    //    if (!create_character_ptr)
    //    {
    //        cout << "Failed to load function!!\n\n";
    //    }
    //    else
    //    {
    //        cout << "Function loaded!!\n\n";
    //    }
    //}

    // temporarily circumventing test executor until it can be refactored
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

