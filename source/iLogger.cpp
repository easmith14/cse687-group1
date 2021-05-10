#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "iLogger.h"
#include "TestResult.h"

using std::string;
using std::cout;

// constructor
iLogger::iLogger(int input)
{
	int logLevel = input;
	string logfilePath = "logs\\TestHarness_";
	logfilePath.append(getFileTimeStamp());
	logfilePath.append(".log");
	logfile.open(logfilePath, std::ios::out);

	cout << "Logger has been instantiated!\n";
}

// destructor
iLogger::~iLogger()
{
	logfile.close();
	cout << "Logger has been destroyed!\n";
}

// accepts input from test executor for logging to file
//    logLevel should be an int of the tier of logging for the given message
//    logMessage should be a descriptive string of what to log
void iLogger::log(TestResult messageFromExecutor)
{
	if (logLevel >= messageFromExecutor.logLevel)
	{
		logfile << getMessageTimeStamp();
		logfile << ", TEST CASE: ";
		logfile << messageFromExecutor.testCaseName;
		logfile << "-";
		logfile << std::to_string(messageFromExecutor.testCaseNum);
		if (messageFromExecutor.result != NULL)
		{
			if (messageFromExecutor.result == true)
			{
				logfile << " has PASSED.";
			}
			else if (messageFromExecutor.result == false)
			{
				logfile << " has FAILED.";
			}
		}
		if (messageFromExecutor.message != "")
		{
			logfile << " \"";
			logfile << messageFromExecutor.message;
			logfile << "\"";
		}
		logfile << "\n";

	}
	else
	{
		// message is ignored
	}
}

// provides current date as a string in YYYYMMDD_HHMMSS format
string iLogger::getFileTimeStamp()
{
	time_t systemTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	tm localTime = *localtime(&systemTime);

	string timeString;
	timeString.append(std::to_string(localTime.tm_year + 1900));
	if (localTime.tm_mon + 1 < 10)
	{
		timeString.append("0");
	}
	timeString.append(std::to_string(localTime.tm_mon + 1));

	if (localTime.tm_mday < 10)
	{
		timeString.append("0");
	}
	timeString.append(std::to_string(localTime.tm_mday));

	timeString.append("_");

	if (localTime.tm_hour < 10)
	{
		timeString.append("0");
	}
	timeString.append(std::to_string(localTime.tm_hour));

	if (localTime.tm_min < 10)
	{
		timeString.append("0");
	}
	timeString.append(std::to_string(localTime.tm_min));

	if (localTime.tm_sec < 10)
	{
		timeString.append("0");
	}
	timeString.append(std::to_string(localTime.tm_sec));

	return timeString;
}

string iLogger::getMessageTimeStamp()
{
	time_t systemTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	tm localTime = *localtime(&systemTime);

	string timeString;
	if (localTime.tm_hour < 10)
	{
		timeString.append("0");
	}
	timeString.append(":");
	timeString.append(std::to_string(localTime.tm_hour));

	if (localTime.tm_min < 10)
	{
		timeString.append("0");
	}
	timeString.append(":");
	timeString.append(std::to_string(localTime.tm_min));

	if (localTime.tm_sec < 10)
	{
		timeString.append("0");
	}
	timeString.append(":");
	timeString.append(std::to_string(localTime.tm_sec));

	return timeString;
}
