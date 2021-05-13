#pragma once
#include <fstream>
#include <string>
#include "TestResult.h"
#include "TestResponse.h"

using std::string;
using std::fstream;

class Logger
{
public:
	// constructor
	Logger(int a);

	// destructor
	~Logger();

	// primary interface for the TestExecutor.  
	// takes TestResponse object as input.
	void Log(TestResponse response);

private:
	int mLogLevel;
	fstream mLogfile;
	string getFileTimeStamp();
	string getMessageTimeStamp();
	void logTestResult(TestResult result);
};