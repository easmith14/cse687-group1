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

using std::string;

class TestResult
{
public:
	TestResult()
	{
		LogLevel = 1;
		TestNumber = 0;
		TestName = "Unnamed";
		TestSuccess = true;
		TestNotes = "No Notes";
	}

	int LogLevel; //level of logging that should output this information
	int TestNumber; // test sequence number
	string TestName; // name of test
	bool TestSuccess; // pass fail
	string TestNotes; // placeholder for test comments
};