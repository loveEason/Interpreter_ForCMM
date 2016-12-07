#include "Symbol.h"

Symbol::Symbol(){}

Symbol::Symbol(string name, int type, int layer)
{
	this->name = name;
	this->type = type;
	this->layer = layer;
	if (type = INT) {
		this->intValue = 0;
	}
	else {
		this->realValue = 0;
	}
}

Symbol::Symbol(string name, int type, double value, int layer) {
	this->name = name;
	this->type = type;
	this->layer = layer;
	this->realValue = value;
}

Symbol::Symbol(string name, int type, int value, int layer) {
	this->name = name;
	this->type = type;
	this->layer = layer;
	this->intValue = value;
}

Symbol::~Symbol()
{
}

int Symbol::getIntValue() {
	return intValue;
}

double Symbol::getRealValue() {
	return realValue;
}

void Symbol::setIntValue(int value) {
	this->intValue = value;
}

void Symbol::setRealValue(double value) {
	this->realValue = value;
}

void Symbol::setIntArrValue(int index, int value) {
	if (index < length) {
		intArray.push_back(value);
	}
	else {
        cout<<"Out of array size."<<endl;
	}
}

void Symbol::setRealArrValue(int index, double value) {
	if (index < length) {
		realArray.push_back(value);
	}
	else {
        cout<<"Out of array size."<<endl;
	}
}

int Symbol::getIntArrValue(int index) {
	if (index < length) {
		return intArray.at(index);
	}
	else {
        cout<<"Out of array size."<<endl;
	}
}

double Symbol::getRealArrValue(int index) {
	if (index < length) {
		return realArray.at(index);
	}
	else {
        cout<<"Out of array size."<<endl;
	}
}

void Symbol::setNext(Symbol *symbol) {
	this->next = symbol;
}

Symbol *Symbol::getNext() {
	return this->next;
}

bool Symbol::hasNext() {
	if (next) {
		return true;
	}
	else {
		return false;
	}
}
