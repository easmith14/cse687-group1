#ifndef TESTPROFILELIBRARY_H
#define TESTPROFILELIBRARY_H

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
    void getTestList(vector<iTestable>&);

};

#endif