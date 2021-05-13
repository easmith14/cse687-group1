/*
CSE687 - Object Oriented Design
Syracuse University
///////////////////////////////////////////////////////////
// Final Project by Aaron Mendelsohn, Evan Smith, Stephen Woodward, Mike Rice
///////////////////////////////////////////////////////////
5/9/2021
*/
#pragma once

#include "TestResponse.h"

class iTestable
{
public:
		virtual TestResponse Test() = 0;
		virtual string GetTypeName() = 0;
};