#pragma once
#include <string>
#include <iostream>
#include "BaseSymbol.h"
using namespace std;

class SimpleSymbol:public BaseSymbol
{
private:
	int lineNumber;
    bool isArray = false;
public:
	SimpleSymbol(string name, int type, int layer, int lineNumber, bool isArray);
	int getLineNumber();
	bool isArraySymbol();
	~SimpleSymbol();
};

