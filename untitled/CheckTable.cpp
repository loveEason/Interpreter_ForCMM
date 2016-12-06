#include "CheckTable.h"



CheckTable::CheckTable(){}

CheckTable::~CheckTable(){}

void CheckTable::addSymbol(SimpleSymbol *ss) {
	if (containsSymbol(ss)) {
		if (ss->getLayer() > getSymbol(ss->getName())->getLayer()) {
			checkTable.push_back(ss);
		}
		else {
            cout<<"Variable "<<ss->getName()<<" has existed."<<endl;
		}
	}
	checkTable.push_back(ss);
}

void CheckTable::removeLayerSimple(int layer) {
	for (int i = 0; i < checkTable.size(); i++) {
		if (checkTable.at(0)->getLayer() == layer) {
			checkTable.erase(checkTable.begin() + i);
			i--;
		}
	}
}

void CheckTable::clearTable() {
	if (checkTable.empty()) {
		checkTable.clear();
	}
}

bool CheckTable::containsSymbol(SimpleSymbol *ss) {
	for (SimpleSymbol *s : checkTable) {
		if (s->getName() == ss->getName()) {
			return true;
		}
	}
	return false;
}

SimpleSymbol* CheckTable::getSymbol(string name) {
	for (SimpleSymbol *s:checkTable) {
		if (s->getName() == name) {
			return s;
		}
	}
	return NULL;
}
