#pragma once

#include <string>
#include <vector>
#include "TestResponse.h"

using std::string;

class ITestable
{
public:
	virtual TestResponse Test() = 0;
};