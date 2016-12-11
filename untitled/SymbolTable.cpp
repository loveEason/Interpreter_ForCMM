#include "SymbolTable.h"

SymbolTable::SymbolTable(){}

SymbolTable::~SymbolTable(){}

void SymbolTable::addSymbol(Symbol *symbol) {
	if (containsSymbol(symbol)) {
        if (getSymbol(symbol->getName())->getLayer() < symbol->getLayer()) {
			Symbol *temp = getSymbol(symbol->getName());
			symbol->setNext(temp);
			symbolTable.erase(symbolTable.begin() + tableIndex);
			symbolTable.insert(symbolTable.begin() + tableIndex, symbol);
			return;
		}
		else {
            cout<<"Variable "<<symbol->getName()<<" existed."<<endl;
		}
	}
	symbolTable.push_back(symbol);
}

void SymbolTable::removeLayerSymbol(int layer) {
	for (int i = 0;i<symbolTable.size();i++) {
		if (symbolTable.at(i)->getLayer() == layer) {
			if (symbolTable.at(i)->hasNext()) {
				Symbol *next = symbolTable[i]->getNext();
				symbolTable[i] = next;
			}
			else {
				symbolTable.erase(symbolTable.begin() + i);
                i--;
			}
		}
	}
}

int SymbolTable::getSymbolIntValue(string name) {
	for (Symbol *symbol : symbolTable) {
		if (symbol->getName() == name) {
			return symbol->getIntValue();
		}
	}
    cout<<"Variable "<<name<<" is not declared before.s"<<endl;
}

double SymbolTable::getSymbolRealValue(string name) {
	for (Symbol *symbol : symbolTable) {
		if (symbol->getName() == name) {
			return symbol->getRealValue();
		}
	}
    cout<<"Variable "<<name<<" is not declared before.s"<<endl;
}

bool SymbolTable::containsSymbol(Symbol *symbol) {
	for (Symbol *sb : symbolTable) {
		if (sb->getName() == symbol->getName()) {
			return true;
		}
	}
	return false;
}

Symbol *SymbolTable::getSymbol(string name) {
	for (int i = 0; i < symbolTable.size(); i++) {
		if (symbolTable.at(i)->getName() == name) {
			tableIndex = i;
			return symbolTable.at(i);
		}
	}
	return NULL;                   //不会从该return返回
}

void SymbolTable::clearTable() {
	if (!symbolTable.empty()) {
		symbolTable.clear();
	}
}

void SymbolTable::printSymbolTable() {
	cout << "Name    " << "Type    " << "Value    " <<"Layer"<< endl;
	for (Symbol *symbol : symbolTable) {
		cout << symbol->getName() << "    "<<symbol->getType()<<"    ";
		if (symbol->getType() == INT) {
			cout << symbol->getIntValue()<<"    ";
		}
		else {
			cout << symbol->getRealValue() <<"    ";
		}
		cout << symbol->getLayer() << endl;
	}
}
