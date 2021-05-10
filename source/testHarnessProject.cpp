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
#include "CelestialBody.h"
#include "TestResponse.h"

using std::cout;
using std::vector;
using std::endl;
using std::cin;

int main()
{
	//
	// initialize objectUnderTest
	//
	CelestialBody objectUnderTest("The Sun", "star", 274.0, 9, 1, 3000);
	TestResponse M;
	M=objectUnderTest.Test(); // executes self-test
	int m_size;
	m_size = M.results.size();
	

	for (int i = 0; i < m_size; ++i) {
		cout << "test number: " << M.results.at(i).test_number << "\t";
		cout << "test_name: " << M.results.at(i).test_name << "\t";
		cout << "test_result: " << M.results.at(i).test_result << "\t";
		cout << "test_notes: " << M.results.at(i).test_notes << "\n";
	}
	
}