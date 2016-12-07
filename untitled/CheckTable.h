#pragma once
#include "SimpleSymbol.h"
#include <vector>
#include <iostream>
using namespace std;
class CheckTable
{
private:
	vector<SimpleSymbol *> checkTable;
public:
	CheckTable();
	~CheckTable();
	void addSymbol(SimpleSymbol *ss);
	void removeLayerSimple(int layer);
	void clearTable();
	bool containsSymbol(SimpleSymbol *ss);
	SimpleSymbol* getSymbol(string name);
};

