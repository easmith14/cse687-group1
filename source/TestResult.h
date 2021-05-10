#pragma once

#include<string>

using std::string;

class TestResult
{
public:
	int test_number; // test sequence number
	string test_name; // name of test
	bool test_result; // pass fail
	string test_notes; // placeholder for test comments
};