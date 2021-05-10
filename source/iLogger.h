#ifndef __ILOGGER_H__
#define __ILOGGER_H__

#include <fstream>
#include <string>
#include "TestResult.h"

using std::string;
using std::fstream;

class iLogger
{
public:
	// constructor
	iLogger(int a);

	// destructor
	~iLogger();

	// primary interface for the TestExecutor.  
	// takes TestResult object as input.
	void log(TestResult);

private:
	int logLevel;
	fstream logfile;
	string getFileTimeStamp();
	string getMessageTimeStamp();

};

#endif
