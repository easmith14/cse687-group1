#pragma once
#include "iTestable.h"
class GaseousCloud :
    public iTestable
{
public:
    GaseousCloud(string name, int xPosition, int yPosition, string color, bool isExpanding) 
        : _name(name), _xPosition(xPosition), _yPosition(yPosition), _color(color), _isExpanding(isExpanding) {}

    //for compatibility with the iTestable interface
    TestResponse Test();
    string GetClassDescription();

private:
    string _name, _color;
    int _xPosition, _yPosition;
    bool _isExpanding;
};

