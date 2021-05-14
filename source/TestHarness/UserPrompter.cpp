/*
CSE687 - Object Oriented Design
Syracuse University
///////////////////////////////////////////////////////////
// Final Project by Aaron Mendelsohn, Evan Smith, Stephen Woodward, Mike Rice
///////////////////////////////////////////////////////////
5/13/2021
*/

#include <iostream>
#include "UserPrompter.h"
using std::cout;
using std::cin;

//prompt the user using the provided string, then verify that it can be cast to an int.
//If bad input provided, reprompt until it's correct
int UserPrompter::promptForInt(string prompt)
{
    bool success = false;
    string userInput = "";
    int parsedInt;

    while (!success)
    {
        cout << prompt;
        cin >> userInput;
        try
        {
            parsedInt = std::stoi(userInput);
            success = true;
        }
        catch (std::exception e)
        {
            cout << "Please enter an integer!\n";
        }
    }

    return parsedInt;
}

//an extension of prompForInt which enforces that the response is non-negative
//If bad input provided, reprompt until it's correct
int UserPrompter::promptForPositiveInt(string prompt)
{
    bool success = false;
    int parsedInt = -1;

    while (!success)
    {
        parsedInt = promptForInt(prompt);

        if (parsedInt <= 0)
        {
            cout << "Please enter a positive integer!\n";
        }
        else
        {
            success = true;
        }
    }

    return parsedInt;
}

//an extension of prompForInt which enforces that the response is non-negative
//If bad input provided, reprompt until it's correct
int UserPrompter::promptForNonNegativeInt(string prompt)
{
    bool success = false;
    int parsedInt = -1;

    while (!success)
    {
        parsedInt = promptForInt(prompt);

        if (parsedInt < 0)
        {
            cout << "Please enter a non-negative integer!\n";
        }
        else
        {
            success = true;
        }
    }
    
    return parsedInt;
}

//an extension of prompForInt which enforces that the response is non-negative OR is a given sentinal value
//If bad input provided, reprompt until it's correct
int UserPrompter::promptForNonNegativeIntOrSentinal(string prompt, int sentinal)
{
    bool success = false;
    int parsedInt = -1;

    while (!success)
    {
        parsedInt = promptForInt(prompt);

        if (parsedInt < 0 && parsedInt != sentinal)
        {
            cout << "Please enter a non-negative integer or " << sentinal << "!\n";
        }
        else
        {
            success = true;
        }
    }

    return parsedInt;
}

//prompt the user using the provided string, then verify that it can be cast to a double.
//If bad input provided, reprompt until it's correct
double UserPrompter::promptForDouble(string prompt)
{
    bool success = false;
    string userInput = "";
    double parsedDouble;

    while (!success)
    {
        cout << prompt;
        cin >> userInput;
        try
        {
            parsedDouble = std::stod(userInput);
            success = true;
        }
        catch (std::exception e)
        {
            cout << "Please enter a double!\n";
        }
    }

    return parsedDouble;
}

//an extension of prompForDouble which enforces that the response is non-negative
//If bad input provided, reprompt until it's correct
double UserPrompter::promptForNonNegativeDouble(string prompt)
{
    bool success = false;
    double parsedDouble = -1;

    while (!success)
    {
        parsedDouble = promptForDouble(prompt);

        if (parsedDouble < 0)
        {
            cout << "Please enter a non-negative integer!\n";
        }
        else
        {
            success = true;
        }
    }

    return parsedDouble;
}

//prompt the user using the provided set of strings alongside an index, then verify that it can be cast to a double.
//If bad input provided, reprompt until it's correct
string UserPrompter::promptForChoice(string prompt, vector<string> options)
{
    bool success = false;
    string userInput = "";
    string selectedOption;

    while (!success)
    {
        string compiledPrompt = prompt;

        for (size_t i = 0; i < options.size(); i++)
        {
            compiledPrompt += "[" + std::to_string(i+1) + "] - " + options[i] + "\n";
        }

        int userSelection = promptForPositiveInt(compiledPrompt);
        if (userSelection <= options.size())
        {
            selectedOption = options.at(userSelection-1);
            success = true;
        }
        else
        {
            cout << "Please select an option from the list!\n";
        }
    }

    return selectedOption;
}

//an extension of prompForInt which enforces that the response is within the given bounds (inclusive)
//If bad input provided, reprompt until it's correct
int UserPrompter::promptForIntWithinRange(string prompt, int lowerBound, int upperBound)
{
    bool success = false;
    int parsedInt = -1;

    while (!success)
    {
        parsedInt = promptForInt(prompt);

        if (parsedInt < lowerBound || parsedInt > upperBound)
        {
            cout << "Please enter an integer between " + std::to_string(lowerBound) + " and " + std::to_string(upperBound) + ".\n";
        }
        else
        {
            success = true;
        }
    }

    return parsedInt;
}

//an extension of prompForDouble which enforces that the response is within the given bounds (inclusive)
//If bad input provided, reprompt until it's correct
double UserPrompter::promptForDoubleWithinRange(string prompt, double lowerBound, double upperBound)
{
    bool success = false;
    double parsedDouble = -1;

    while (!success)
    {
        parsedDouble = promptForDouble(prompt);

        if (parsedDouble >= lowerBound && parsedDouble <= upperBound)
        {
            cout << "Please enter a double between " + std::to_string(lowerBound) + " and " + std::to_string(upperBound) + ".\n";
        }
        else
        {
            success = true;
        }
    }

    return parsedDouble;
}

//prompts for a string, then enforces that the given string is composed only of approved characters
//If bad input provided, reprompt until it's correct
string UserPrompter::promptForStringWithApprovedChars(string prompt, vector<char> approvedChars)
{
    bool success = false;
    string parsedString = "";

    string approvedCharsString = "";
    for (char ch : approvedChars)
    {
        approvedCharsString += ch + " ";
    }

    while (!success)
    {
        cout << prompt;
        string rawString;
        cin >> rawString;

        success = true;
        for (char ch : rawString)
        {
            bool chApproved = false;
            for (char approvedCh : approvedChars)
            {
                if (ch == approvedCh)
                {
                    chApproved = true;
                    break;
                }
            }

            if (!chApproved)
            {
                cout << "Please only use approved characters from this list: " + approvedCharsString + ".\n";
                success = false;
                break;
            }
            else
            {
                parsedString += ch;
            }
        }
    }

    return parsedString;
}
