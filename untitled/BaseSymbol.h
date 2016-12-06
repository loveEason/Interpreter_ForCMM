#pragma once
#include <string>
#include <iostream>
using namespace std;
#define INT 1
#define REAL 2

class BaseSymbol
{
protected:
	string name;
	int type;
	int layer;
public:
	BaseSymbol();
	~BaseSymbol();
	string getName();
	int getType();
	int getLayer();
};

