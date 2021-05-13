#include <stdio.h>
#include <iostream>
#include <vector>

#include "TestExecutor.h"
#include "UserPrompter.h"

using std::vector;

int main()
{
	TestExecutor executor;
	UserPrompter prompter;

	bool isRunning = true;
	while (isRunning)
	{
		executor.Execute();
		string userChoice = prompter.promptForChoice("\n\nDo you want to run another set of tests?\n", vector<string>{"Yes", "No"});

		isRunning = userChoice == "Yes";
	}

}