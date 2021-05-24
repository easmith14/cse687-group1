/*
CSE687 - Object Oriented Design
Syracuse University
///////////////////////////////////////////////////////////
// Final Project by Aaron Mendelsohn, Evan Smith, Stephen Woodward, Mike Rice
///////////////////////////////////////////////////////////
5/13/2021
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>


#include "TestExecutor.h"
#include "UserPrompter.h"

using std::vector;
std::mutex mtx1;

int main()
{
	TestExecutor *task1ptr = new TestExecutor;
	TestExecutor *task2ptr = new TestExecutor;
	UserPrompter prompter;

	bool isRunning = true;
	std::cout << "\n  main thread id = " << std::this_thread::get_id() << "\n";
	while (isRunning)
	{
		std::thread th1(&TestExecutor::Execute, task1ptr);
		std::thread th2(&TestExecutor::Execute, task2ptr);
		std::cout << "\n  in callback thread id = " << std::this_thread::get_id() << "\n";
		th1.join();
		std::cout << "\n  in callback thread id = " << std::this_thread::get_id() << "\n";
		th2.join();
		
		string userChoice = prompter.promptForChoice("\n\nDo you want to run another set of tests?\n", vector<string>{"Yes", "No"});
		isRunning = userChoice == "Yes";
		


	}

}