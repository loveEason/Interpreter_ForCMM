#include "actuator.h"

//SymbolNode 实现

SymbolNode::SymbolNode(string _name, symbolType _type, int _length = 1){
    name=_name; type=_type; length=_length;
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
    case symbolType::realArray:
        value = new double[length];
        break;
    case symbolType::none:
        break;
    }
}

SymbolNode::SymbolNode(const SymbolNode& node) {
    name = node.name;
    type = node.type;
    length = node.length;
    switch(type) {
    case symbolType::integer:
        value = new int;
        *((int*)value) = *((int*)(node.value));
        break;
    case symbolType::integerArray:
        value = new int[length];
        for (int i=0; i<length; i++)
            ((int*)(value))[i]=((int*)(node.value))[i];
        break;
    case symbolType::real:
        value = new double;
        *((double*)value) = *((double*)(node.value));
        break;
    case symbolType::realArray:
        value = new double[length];
        for (int i=0; i<length; i++)
            ((double*)(value))[i]=((double*)(node.value))[i];
        break;
    case symbolType::none:
        break;
    }

}

SymbolNode::~SymbolNode() {
    switch(type) {
    case symbolType::integer:
        delete (int*) value;
        break;
    case symbolType::real:
        delete (double*)value;
        break;
    case symbolType::integerArray:
        delete[] (int*)value;
        break;
    case symbolType::realArray:
        delete[] (double*)value;
        break;
    case symbolType::none:
        break;
    }
}

int SymbolNode::getIntegerValue(int index) {
    // todo: 错误处理 越界检查 类型检查
    int* x = (int*) value;
    return x[index];
}

double SymbolNode::getDoubleValue(int index) {
    // todo: 错误处理 越界检查 类型检查
    double* x = (double*) value;
    return x[index];
}

void SymbolNode::setIntegerValue(int _value, int index) {
    // todo: 错误处理 越界检查 类型检查
    int* x = (int*) value;
    x[index] = _value;
}

void SymbolNode::setDoubleValue(double _value, int index) {
    // todo: 错误处理 越界检查 类型检查
    double* x = (double*) value;
    x[index] = _value;
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
            return node->second;
            break;
        }
        if (i==symbolTable.begin()) break;
    }
    return {};
}

void Symbol::addNode(symbolType type, string name, int length) {
    auto table = symbolTable.end()-1;
    SymbolNode node(name, type, length);
    table->insert(pair<string, SymbolNode>(name, SymbolNode(name, type, length)));
}


void Symbol::changeNode(string name, double value, int index) {
    // todo: 错误处理 类型检查 越界检查
    for (auto i=symbolTable.end(); ;i--) {
        auto node = i->find(name);
        if (node!=i->end()) {
            node->second.setDoubleValue(value, index);
            break;
        }
        if (i==symbolTable.begin()) break;
    }
}

void Symbol::changeNode(string name, int value, int index) {
    // todo: 错误处理 类型检查 越界检查
    for (auto i=symbolTable.end(); ;i--) {
        auto node = i->find(name);
        if (node!=i->end()) {
            node->second.setIntegerValue(value, index);
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
    return false;
}

bool Actuator::runOnelineCode(InterCode code) {
    string type = code.getInstructType();
    if (type=="INT_DCL") {

    } else if (type=="REAL_DCL") {

    } else if (type=="ASG") {

    } else if (type=="RED") {

    } else if (type=="WRT") {

    } else if (type=="PLU") {

    } else if (type=="MINU") {

    } else if (type=="DIVIDE") {

    } else if (type=="JMP") {

    } else {

    }
    return false;
}

void Actuator::declareInt(string first, string second, string third) {
    // todo: 错误处理
    if (second=="NULL")
        symbolTable.addNode(symbolType::integer, first);
    else
        symbolTable.addNode(symbolType::integerArray, first, atoi(second.c_str()));
    if (third!="NULL") symbolTable.changeNode(first, atoi(third.c_str()));
}

void Actuator::declareReal(string first, string second, string third) {
    // todo: 错误处理
    if (second=="NULL")
        symbolTable.addNode(symbolType::real, first);
    else
        symbolTable.addNode(symbolType::realArray, first, atoi(second.c_str()));
    if (third!="NULL") symbolTable.changeNode(first, atof(third.c_str()));
}


void Actuator::assignment(string first, string second, string third) {
    // todo: 错误处理
    auto node = symbolTable.findNode(first);
    if (second=="NULL") {
        if (node.type==symbolType::integer)
            symbolTable.changeNode(first, atoi(third.c_str()));
        else
            symbolTable.changeNode(first, atof(third.c_str()));
    } else {
        if (node.type==symbolType::integerArray)
            symbolTable.changeNode(first, atoi(third.c_str()), atoi(second.c_str()));
        else
            symbolTable.changeNode(first, atof(third.c_str()), atoi(second.c_str()));
    }
}

void Actuator::plus(string first, string second, string third) {

}

void Actuator::minu(string first, string second, string third) {

}

void Actuator::divide(string first, string second, string third) {

}

void Actuator::jump(string first, string second, string third) {

}
