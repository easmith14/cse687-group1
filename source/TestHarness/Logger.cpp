/*
CSE687 - Object Oriented Design
Syracuse University
///////////////////////////////////////////////////////////
// Final Project by Aaron Mendelsohn, Evan Smith, Stephen Woodard, Mike Rice
///////////////////////////////////////////////////////////
5/13/2021
*/
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#include "Logger.h"

using std::string;
using std::cout;
using std::to_string;

// constructor
Logger::Logger(int input)
{
	mLogLevel = input;
	string logfilePath = "..\\..\\logs\\TestHarness_";
	logfilePath.append(getFileTimeStamp());
	logfilePath.append(".log");
	mLogfile.open(logfilePath, std::ios::out);

	cout << "Logger has been instantiated!\n";
}

// destructor
Logger::~Logger()
{
	mLogfile.close();
	cout << "Logger has been destroyed!\n";
}

void Logger::Log(TestResponse response)
{
	//log overall information about all tests opn the class
	string overallSuccess = response.Success ? "SUCCESS" : "FAIL";
	mLogfile << this->getMessageTimeStamp() << " Testing overall for " << response.ClassName << ": " << overallSuccess << "\n";
	mLogfile << this->getMessageTimeStamp() << " " << response.Notes << "\n";

	//log information about each test
	for (TestResult result : response.Results)
	{
		logTestResult(result);
	}

}

// accepts input from test executor for logging to file
//    logLevel should be an int of the tier of logging for the given message
//    logMessage should be a descriptive string of what to log
void Logger::logTestResult(TestResult messageFromExecutor)
{
	if (mLogLevel >= messageFromExecutor.LogLevel)
	{
		mLogfile << getMessageTimeStamp();
		mLogfile << ", TEST CASE: ";
		mLogfile << messageFromExecutor.TestName;
		mLogfile << "-";
		mLogfile << std::to_string(messageFromExecutor.TestNumber);
		if (messageFromExecutor.TestSuccess != NULL)
		{
			if (messageFromExecutor.TestSuccess == true)
			{
				mLogfile << " has PASSED.";
			}
			else if (messageFromExecutor.TestSuccess == false)
			{
				mLogfile << " has FAILED.";
			}
		}
		if (messageFromExecutor.TestNotes != "")
		{
			mLogfile << " \"";
			mLogfile << messageFromExecutor.TestNotes;
			mLogfile << "\"";
		}
		mLogfile << "\n";

	}
}

// provides current date as a string in YYYYMMDD_HHMMSS format
string Logger::getFileTimeStamp()
{
	time_t systemTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	tm localTime; 
	localtime_s(&localTime, &systemTime);

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

string Logger::getMessageTimeStamp()
{
	time_t systemTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	
	tm localTime;
	localtime_s(&localTime, &systemTime);

	string timeString;
	if (localTime.tm_hour < 10)
	{
		timeString.append("0");
	}
	timeString.append(std::to_string(localTime.tm_hour));

	timeString.append(":");
	if (localTime.tm_min < 10)
	{
		timeString.append("0");
	}
	timeString.append(std::to_string(localTime.tm_min));

	timeString.append(":");
	if (localTime.tm_sec < 10)
	{
		timeString.append("0");
	}
	timeString.append(std::to_string(localTime.tm_sec));

	return timeString;
}
