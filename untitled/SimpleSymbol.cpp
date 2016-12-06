#include "SimpleSymbol.h"



SimpleSymbol::SimpleSymbol(string name, int type, int layer, int lineNumber)
{
	this->name = name;
	this->type = type;
	this->layer = layer;
	this->lineNumber = lineNumber;
	this->isArray = false;
}

SimpleSymbol::SimpleSymbol(string name, int type, int layer, int lineNumber, bool isArray) {
	this->name = name;
	this->type = type;
	this->layer = layer;
	this->lineNumber = lineNumber;
    this->isArray = isArray;
}

SimpleSymbol::~SimpleSymbol()
{
}


int SimpleSymbol::getLineNumber() {
	return this->lineNumber;
}

bool SimpleSymbol::isArraySymbol() {
	return this->isArray;
}
