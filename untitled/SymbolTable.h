#pragma once
#include "BaseSymbol.h"
#include "Symbol.h"

class SymbolTable
{
private:
	vector<Symbol *> symbolTable;
	int tableIndex = 0;
public:
	SymbolTable();
	~SymbolTable();
	void addSymbol(Symbol *symbol);
	void removeLayerSymbol(int layer);
	int getSymbolIntValue(string name);
	double getSymbolRealValue(string name);
	void clearTable();
	void printSymbolTable();
	bool containsSymbol(Symbol *symbol);
	Symbol *getSymbol(string name);
};

