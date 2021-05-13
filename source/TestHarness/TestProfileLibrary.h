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