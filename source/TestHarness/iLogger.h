#ifndef __ILOGGER_H__
#define __ILOGGER_H__

#include <fstream>
#include <string>

using std::string;
using std::fstream;

class iLogger
{
public:
	// constructor
	iLogger();

	// desctructor
	~iLogger();

	// accepts input from test executor for logging to file
	//    logLevel should be a string of the tier of logging for the given message
	//    logMessage should be a descriptive string of what to log
	void log(string, string);

private:
	fstream logfile;
	string getCurrentTimeAsString();

};

#endif
