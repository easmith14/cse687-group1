#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "iLogger.h"

using std::string;
using std::cout;

// constructor
ILogger::ILogger()
{
	string logfilePath = "logs\\TestHarness_";
	logfilePath.append(getCurrentTimeAsString());
	logfilePath.append(".log");
	logfile.open(logfilePath, std::ios::out);

	cout << "Logger has been instantiated!\n";
}

// destructor
ILogger::~ILogger()
{
	logfile.close();
	cout << "Logger has been destroyed!\n";
}

// accepts input from test executor for logging to file
//    logLevel should be a string of the tier of logging for the given message
//    logMessage should be a descriptive string of what to log
void ILogger::Log(string logLevel, string logMessage)
{
	logfile << getCurrentTimeAsString() << ", ";
	logfile << logLevel << ", ";
	logfile << logMessage << "\n";
}

// provides current date as a string in YYYYMMDD_HHMMSS format
string ILogger::getCurrentTimeAsString()
{
	time_t systemTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	tm localTime = *localtime(&systemTime);

	string outputTime;
	outputTime.append(std::to_string(localTime.tm_year + 1900));
	if (localTime.tm_mon + 1 < 10)
	{
		outputTime.append("0");
	}
	outputTime.append(std::to_string(localTime.tm_mon + 1));

	if (localTime.tm_mday < 10)
	{
		outputTime.append("0");
	}
	outputTime.append(std::to_string(localTime.tm_mday));

	outputTime.append("_");

	if (localTime.tm_hour < 10)
	{
		outputTime.append("0");
	}
	outputTime.append(std::to_string(localTime.tm_hour));

	if (localTime.tm_min < 10)
	{
		outputTime.append("0");
	}
	outputTime.append(std::to_string(localTime.tm_min));

	if (localTime.tm_sec < 10)
	{
		outputTime.append("0");
	}
	outputTime.append(std::to_string(localTime.tm_sec));

	return outputTime;
}
