// testHarnessProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Aaron Mendelsohn
CSE 687 - M401 Object Oriented Design
Syracuse University
///////////////////////////////////////////////////////////
// Final Project by Aaron Mendelsohn
///////////////////////////////////////////////////////////
4/29/2021
*/

// main program to test object under test
//
// program flow:
//		initialize class iTestable which is the object to be tested in the project
//		execute iTestable.BIST()
//		test results are stored in a vector testResults
//		vector is a struct for test num, test name, test_result, test_notes.

#include "pch.h"
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include "iTestable.h"

using std::cout;
using std::vector;
using std::endl;
using std::cin;

int main()
{
	//
	// initialize objectUnderTest
	//
	iTestable objectUnderTest("The Sun", "star", 274.0, 9, 1, 3000);
	objectUnderTest.runBIST(); // executes self-test
	int M;
	M = objectUnderTest.testResults.size();  // find out number of tests run & print results
	for (int i = 0; i < M; ++i) {
		cout << "test number: " << objectUnderTest.testResults.at(i)->test_num << "\t";
		cout << "test_name: " << objectUnderTest.testResults.at(i)->test_name << "\t";
		cout << "test_result: " << objectUnderTest.testResults.at(i)->test_result << "\t";
		cout << "test_notes: " << objectUnderTest.testResults.at(i)->test_notes << "\n";
	}
}