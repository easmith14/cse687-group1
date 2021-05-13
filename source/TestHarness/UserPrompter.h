/*
Evan Smith
CIS 554 - M401 Object Oriented Programming in C++
Syracuse University
General Library
Last Updated: 3 / 10 / 21
This file describes a series of functions to facilitate safe prompting of users and parsing of their responses.
*/

#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

class UserPrompter
{
public:
	//prints provided prompt and returns parsed int, or reprompts.
	int promptForInt(string prompt);
	//prints provided prompt and returns parsed positive int, or reprompts.
	int promptForPositiveInt(string prompt);
	//prints provided prompt and returns parsed non-negative int, or reprompts.
	int promptForNonNegativeInt(string prompt);
	//prints provided prompt and returns parsed non-negative or sentinal int, or reprompts.
	int promptForNonNegativeIntOrSentinal(string prompt, int sentinal);
	//prints provided prompt and returns parsed double, or reprompts.
	double promptForDouble(string prompt);
	//prints provided prompt and returns parsed non-negative double, or reprompts.
	double promptForNonNegativeDouble(string prompt);
	//prints each element in the provided vector along with a prompt and returns the string that was selected, or reprompts.
	string promptForChoice(string prompt, vector<string> options);
	//prints provided prompt and returns parsed int between bounds, or reprompts.
	int promptForIntWithinRange(string prompt, int lowerBound, int upperBound);
	//prints provided prompt and returns parsed double between bounds, or reprompts.
	double promptForDoubleWithinRange(string prompt, double lowerBound, double upperBound);
	//prints provided prompt and returns string which uses only supplied chars, or reprompts.
	string promptForStringWithApprovedChars(string prompt, vector<char> approvedChars);
};

