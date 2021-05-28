/*
CSE687 - Object Oriented Design
Syracuse University
///////////////////////////////////////////////////////////
// Final Project by Aaron Mendelsohn, Evan Smith, Stephen Woodard, Mike Rice
///////////////////////////////////////////////////////////
5/13/2021
*/

#pragma once
#include "Logger.h"

class TestExecutor
{
public:
	TestExecutor(Logger*);
	void Execute();

private:
	Logger* logger;
};

