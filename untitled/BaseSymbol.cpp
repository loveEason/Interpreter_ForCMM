#include "BaseSymbol.h"



BaseSymbol::BaseSymbol(){}


BaseSymbol::~BaseSymbol(){}

string BaseSymbol::getName() {
	return this->name;
}

int BaseSymbol::getLayer() {
	return this->layer;
}

int BaseSymbol::getType() {
	return this->type;
}
