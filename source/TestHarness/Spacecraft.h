#pragma once
#include "iTestable.h"
class Spacecraft :
    public iTestable
{
    public:
        Spacecraft(string name, int xPosition, int yPosition) : _name(name), _xPosition(xPosition), _yPosition(yPosition) {}

        //for compatibility with the iTestable interface
        TestResponse Test();
        string GetClassDescription();

private:
    string _name;
    int _xPosition, _yPosition;
};

