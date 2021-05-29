/*
CSE687 - Object Oriented Design
Syracuse University
///////////////////////////////////////////////////////////
// Final Project by Aaron Mendelsohn, Evan Smith, Stephen Woodard, Mike Rice
///////////////////////////////////////////////////////////
5/13/2021
*/
#include <stdio.h>
#include <iostream>
#include <vector>

#include "TestExecutor.h"
#include "UserPrompter.h"
#include "Logger.h"

using std::vector;
using std::to_string;

int main()
{
	// make objects
	UserPrompter prompter;
	int maxLoggingLevel = 3;
	Logger logger(prompter.promptForIntWithinRange("Enter Logging Level (0-" + to_string(maxLoggingLevel) + "): ", 0, maxLoggingLevel));
	TestExecutor executor(&logger);

	bool isRunning = true;
	while (isRunning)
	{
		executor.Execute();
		string userChoice = prompter.promptForChoice("\n\nDo you want to run another set of tests?\n", vector<string>{"Yes", "No"});

		isRunning = userChoice == "Yes";
	}

}