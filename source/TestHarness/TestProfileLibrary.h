/*
CSE687 - Object Oriented Design
Syracuse University
///////////////////////////////////////////////////////////
// Final Project by Aaron Mendelsohn, Evan Smith, Stephen Woodard, Mike Rice
///////////////////////////////////////////////////////////
5/13/2021
*/

#pragma once

#include <iostream>
#include <vector>
#include "iTestable.h"

using std::vector;

class TestProfileLibrary
{
public:
    //constructor
    TestProfileLibrary();

    //destructor
    ~TestProfileLibrary();

    //instantiates objects and returns vector of created objects
    vector<iTestable*> GetTestList();
};