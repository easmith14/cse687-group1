#pragma warning(disable : 4996)

#include "JsonMessageGenerator.h"
#include <ctime>

const char* JsonMessageGenerator::GenerateMessageFromClassNames(map<string, iTestable*> classOptions)
{
    //generate Json Value for class names
    Json::Value classNames;

    for (auto className : classOptions)
    {
        classNames.append(className.first);
    }

    //set values for base message
    Json::Value baseMessage = generateBaseMessage();
    baseMessage[messageType] = MessageType::ClassOptions;
    baseMessage[body] = classNames;
    return _strdup(baseMessage.toStyledString().c_str());
}

std::string JsonMessageGenerator::GetStringFromClassesJson(Json::Value val)
{
    std::ostringstream stringStream;
    Json::Value classes = val["Body"];
    int i = 1;
    for (Json::Value className : classes)
    {
        stringStream << "\n[" << i++ << "]  " << className.asString() << "\n";
    }
    stringStream << "\n>";

    return stringStream.str();
}

const char* JsonMessageGenerator::GenerateMessageFromTestResponse(TestResponse response)
{
    //generate Json Value for class names
    Json::Value testResponse;

    testResponse["ClassName"] = response.ClassName;
    testResponse["Notes"] = response.Notes;
    testResponse["Success"] = response.Success;

    if (response.Results.size() > 0)
    {
        Json::Value testResults;
        for (auto result : response.Results)
        {
            Json::Value formattedResult;

            formattedResult["TestName"] = result.TestName;
            formattedResult["LogLevel"] = result.LogLevel;
            formattedResult["TestNotes"] = result.TestNotes;
            formattedResult["TestNumber"] = result.TestNumber;
            formattedResult["TestSuccess"] = result.TestSuccess;

            testResults.append(formattedResult);
        }

        testResponse["Results"] = testResults;
    }
    else
    {
        testResponse["Results"] = "N/A";
    }

    //set values for base message
    Json::Value baseMessage = generateBaseMessage();
    baseMessage[messageType] = MessageType::TestResult;
    baseMessage[body] = testResponse;
    return _strdup(baseMessage.toStyledString().c_str());
}

const char* JsonMessageGenerator::GenerateMessage(string value, MessageType messageType)
{
    Json::Value baseMessage = generateBaseMessage();
    baseMessage[this->messageType] = messageType;
    baseMessage[body] = value;
    return _strdup(baseMessage.toStyledString().c_str());
}


Json::Value JsonMessageGenerator::GetValueFromJsonString(string jsonString)
{
    Json::Reader reader;
    Json::Value output;
    if (reader.parse(jsonString, output))
    {
        return output;
    }
    return Json::Value();
}

Json::Value JsonMessageGenerator::generateBaseMessage()
{
    Json::Value message;
    //Source Address
    message[sourceAddress] = source;

    //Destination addresses
    message[destinationAddress] = destination;

    //Message type (default to error)
    message[messageType] = MessageType::Error;

    //Author
    message[author] = caller;

    //Current Datetime
    time_t t = time(NULL);
    std::string dateTimeString(asctime(gmtime(&t)));
    message[currentDatetime] = dateTimeString;

    //Body
    message[body] = "placeholder";


    return message;
}
