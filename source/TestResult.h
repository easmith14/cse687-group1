#ifndef __TESTRESULT_H__
#define __TESTRESULT_H__

#include<string>

using std::string;

class TestResult
{
public:
	// constructor with: RESULT and NO MESSAGE
	TestResult(int a, string b, int c, bool d)
		: logLevel(a), testCaseName(b), testCaseNum(c), result(d)
	{
		message = "";
	};

	// constructor with: NO RESULT and MESSAGE
	TestResult(int a, string b, int c, string d)
		: logLevel(a), testCaseName(b), testCaseNum(c), message(d)
	{
		result = NULL;
	};

	// constructor with: RESULT and MESSAGE
	TestResult(int a, string b, int c, bool d, string e)
		: logLevel(a), testCaseName(b), testCaseNum(c), result(d), message(e)
	{
		// nothing todo
	};

	// destructor
	~TestResult()
	{
		// nothing todo
	};

	int logLevel;        // REQUIRED: integer between 1-3.  When log level is set in iLogger, all
	                     //           messages received with a greater value will be discarded.
	                     //              1 - minimal logging
	                     //              2 - moderate logging
	                     //              3 - all logging
	string testCaseName; // REQUIRED: string of the test case name
	int testCaseNum;     // REQUIRED: unique identifier number for test case number
	bool result;         // OPTIONAL: return true for pass and false for failure
	string message;      // OPTIONAL: return message 

};

#endif