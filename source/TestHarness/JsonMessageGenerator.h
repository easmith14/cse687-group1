#pragma once
#include <vector>
#include <map>

#include "iTestable.h"
#include "json.h"

using std::map;

class JsonMessageGenerator
{
public:
	JsonMessageGenerator(string caller, string source, string destination)
		: caller(caller), source(source), destination(destination)
	{

	}

	enum MessageType { Error, ClassSelection, ClassOptions, TestResult, UIMessage, UserCommand, Exit };

	const char* GenerateMessage(string message, MessageType messageType);

	const char* GenerateMessageFromClassNames(map<string, iTestable*> classOptions);

	const char* GenerateMessageFromTestResponse(TestResponse response);

	Json::Value GetValueFromJsonString(string jsonString);

	std::string GetStringFromClassesJson(Json::Value val);

private:
	std::string caller, source, destination;
	Json::Value generateBaseMessage();
	std::string sourceAddress = "SourceAddress";
	std::string destinationAddress = "DestinationAddress";
	std::string messageType = "MessageType";
	std::string author = "Author";
	std::string currentDatetime = "CurrentDateTime";
	std::string body = "Body";
};

