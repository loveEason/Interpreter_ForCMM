#include "CheckTable.h"



CheckTable::CheckTable(){}

CheckTable::~CheckTable(){}

void CheckTable::addSymbol(SimpleSymbol *ss) {
    if (containsSymbol(ss->getName(), ss->getLayer())) {
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

bool CheckTable::containsSymbol(string name, int layer) {
    int count = checkTable.size();
    for(int i=0;i<count;i++){
        if(checkTable.at(i)->getName()==name&&checkTable.at(i)->getLayer()<=layer){
            return true;
        }
    }
    return false;
}

SimpleSymbol* CheckTable::getSymbol(string name) {
    for (int i=0;i<checkTable.size();i++) {
        if (checkTable[i]->getName() == name) {
            return checkTable[i];
		}
	}
	return NULL;
}
