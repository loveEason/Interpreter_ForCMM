#include "actuator.h"

//SymbolNode 实现

SymbolNode::SymbolNode(string _name, symbolType _type, int _length = 1):name(_name),type(_type),length(_length){
    switch(type) {
    case symbolType::integer:
        value = new int;
        break;
    case symbolType::integerArray:
        value = new int[length];
        break;
    case symbolType::real:
        value = new double;
        break;
    case symbolType::realAarray:
        value = new double[length];
        break;
    }
}

SymbolNode::SymbolNode(SymbolNode node) {
    name = node.name;
    type = node.type;
    length = node.length;
    switch(type) {
    case symbolType::integer:
        value = new int;
        *((int*)value) = *((int*)(node->value));
        break;
    case symbolType::integerArray:
        value = new int[length];
        for (int i=0; i<length; i++)
            ((int*)(value))[i]=((int*)(node->value))[i];
        break;
    case symbolType::real:
        value = new double;
        *((double*)value) = *((double*)(node->value));
        break;
    case symbolType::realAarray:
        value = new double[length];
        for (int i=0; i<length; i++)
            ((double*)(value))[i]=((double*)(node->value))[i];
        break;
    }

}

SymbolNode::~SymbolNode() {
    switch(type) {
    case symbolType::integer:
    case symbolType::real:
        delete value;
        break;
    case symbolType::integerAarray:
    case symbolType::realAarray:
        delete[] value;
        break;
    }
}

int SymbolNode::getIntegerValue(int index=0) {
    // todo: 错误处理 越界检查 类型检查
    int* x = (int*) value;
    return x[index];
}

double SymbolNode::getDoubleValue(int index=0) {
    // todo: 错误处理 越界检查 类型检查
    double* x = (double*) value;
    return x[index];
}

void SymbolNode::setIntegerValue(int value, int index=0) {
    // todo: 错误处理 越界检查 类型检查
    int* x = (int*) value;
    x[index] = value;
}

void SymbolNode::setDoubleValue(double value, int index=0) {
    // todo: 错误处理 越界检查 类型检查
    double* x = (double*) value;
    x[index] = value;
}

//Symbol 实现
Symbol::Symbol() {
    addTable();
}

Symbol::~Symbol() {

}

void Symbol::addTable() {
    symbolTable.push_back(map<string, SymbolNode>());
}

void Symbol::deleteTable() {
    symbolTable.pop_back();
}

SymbolNode Symbol::findNode(string name) {
    for (auto i=symbolTable.end(); ;i--) {
        auto node = i->find(name);
        if (node!=i->end()) {
            return *node;
            break;
        }
        if (i==symbolTable.begin()) break;
    }
    return {};
}

void Symbol::addNode(symbolType type, string name, int length=1) {
    auto table = symbolTable.end()-1;
    auto node = SymbolNode(name, type, length);
    table->insert(pair<string, SymbolNode>(name, node));
}


void Symbol::changeNode(string name, double value, int index=0) {
    // todo: 错误处理 类型检查 越界检查
    for (auto i=symbolTable.end(); ;i--) {
        auto node = i->find(name);
        if (node!=i->end()) {
            node->setDoubleValue(value, index);
            break;
        }
        if (i==symbolTable.begin()) break;
    }
}

void Symbol::changeNode(string name, int value, int index=0) {
    // todo: 错误处理 类型检查 越界检查
    for (auto i=symbolTable.end(); ;i--) {
        auto node = i->find(name);
        if (node!=i->end()) {
            node->setIntegerValue(value, index);
            break;
        }
        if (i==symbolTable.begin()) break;
    }
}


// Actuator 实现

Actuator::Actuator() {

}

Actuator::~Actuator() {

}

bool Actuator::runCode() {

}

bool Actuator::runOnelineCode() {

}

void Actuator::declareInt(string first, string second, string third) {
    // todo: 错误处理
}

void Actuator::declareReal(string first, string second, string third) {
    // todo: 错误处理
}

void Actuator::assignment(string first, string second, string third) {
    // todo: 错误处理
}

void Actuator::plus(string first, string second, string third) {

}

void Actuator::minu(string first, string second, string third) {

}

void Actuator::divide(string first, string second, string third) {

}

void Actuator::jump(string first, string second, string third) {

}
