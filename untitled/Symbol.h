#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "BaseSymbol.h"
using namespace std;

class Symbol:public BaseSymbol
{
private:
	int intValue;
	double realValue;
	int length;            //用于记录数组长度
	vector<int> intArray;
	vector<double> realArray;
	Symbol *next;       //用于指向较低层的同名Symbol
public:
	Symbol();
	Symbol(string name, int type, int layer);
	Symbol(string name, int type, double value, int layer);
	Symbol(string name, int type, int value, int layer);
	int getIntValue();
	double getRealValue();
	void setIntValue(int intValue);
	void setRealValue(double realValue);
	int getIntArrValue(int index);
	double getRealArrValue(int index);
	void setIntArrValue(int index, int intValue);
	void setRealArrValue(int index, double realValue);
	void setNext(Symbol *symbol);
	Symbol* getNext();
	bool hasNext();
	~Symbol();
};

