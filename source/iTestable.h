/*
CSE687 - Object Oriented Design
Syracuse University
///////////////////////////////////////////////////////////
// Final Project by Aaron Mendelsohn, Evan Smith, Stephen Woodward, Mike Rice
///////////////////////////////////////////////////////////
5/9/2021
*/

#ifndef __iTestable_H__
#define __iTestable_H__

#include "TestResponse.h"

class iTestable
{
public:
		virtual TestResponse Test();
};

#endif