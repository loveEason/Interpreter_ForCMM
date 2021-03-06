#include "actuator.h"
#include "math.h"


int isnumber(string x) {
    int length = x.length();
    if (length<1) return -1;
    bool flag = false;

    if (x[0]=='0') {
        if (length==1)
            return 0;
        else if (x[1]=='.') {
            if (length<3) return -1;
            for (int i=2; i<length; i++) {
                if (x[i]<'0'||x[i]>'9') return -1;
            }
            return 1;
        } else {
            return -1;
        }
    } else if (x[0]<='9'&&x[0]>'0') {
        for (int i=1; i<length; i++){
            if (x[i]=='.') {
                if (flag) return -1;
                flag = true;
            } else if (x[i]>'9'&&x[i]<'0') return -1;
        }
        if (flag) return 1; else return 0;
    }

    return -1;
}

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
    if (index>=this->length) throw ActuatorException("Error: array out of bouds!\nFunction: getIntegerValue.");
    if (this->type!=symbolType::integer && this->type!=symbolType::integerArray)
        throw ActuatorException("Internal Error: get int but the element is not int!");
    int* x = (int*) value;
    return x[index];
}

double SymbolNode::getDoubleValue(int index) {
    // todo: 错误处理 越界检查 类型检查
    if (index>=this->length) throw ActuatorException("Error: array out of bouds!\nFunction: getDoubleValue.");
    if (this->type!=symbolType::real && this->type!=symbolType::realArray)
        throw ActuatorException("Internal Error: get real but the element is not real!\nname: "+this->name);
    double* x = (double*) value;
    return x[index];
}

void SymbolNode::setIntegerValue(int _value, int index) {
    // todo: 错误处理 越界检查 类型检查
    if (index>=this->length) throw ActuatorException("Error: array out of bouds!\nFunction: setIntegerValue.");
    if (this->type!=symbolType::integer && this->type!=symbolType::integerArray)
        throw ActuatorException("Internal Error: set int but the element is not int!");
    int* x = (int*) value;
    x[index] = _value;
}

void SymbolNode::setDoubleValue(double _value, int index) {
    // todo: 错误处理 越界检查 类型检查
    if (index>=this->length) throw ActuatorException("Error: array out of bouds!\nFunction: setDoubleValue.");
    if (this->type!=symbolType::real && this->type!=symbolType::realArray)
        throw ActuatorException("Internal Error: set real but the element is not real!");
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
    for (auto i=symbolTable.end()-1; ;i--) {
        if (symbolTable.size()==0) break;
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
    for (auto i=symbolTable.end()-1; ;i--) {
        if (symbolTable.size()==0) break;
        auto node = i->find(name);
        if (node!=i->end()) {
            node->second.setDoubleValue(value, index);
            break;
        }
        if (i==symbolTable.begin()) {
            throw ActuatorException("Internal Error: Can't change \""+name+"\" because I can't find it!\nFunction: ChangeNode(double).");
            break;
        }
    }
}

void Symbol::changeNode(string name, int value, int index) {
    // todo: 错误处理 类型检查 越界检查
    for (auto i=symbolTable.end()-1; ;i--) {
        if (symbolTable.size()==0) break;
        auto node = i->find(name);
        if (node!=i->end()) {
            node->second.setIntegerValue(value, index);
            break;
        }
        if (i==symbolTable.begin()) {
            throw ActuatorException("Internal Error: Can't change \""+name+"\" because I can't find it!\nFunction: ChangeNode(int).");
            break;
        }
    }
}


// Actuator 实现

Actuator::Actuator(vector<InterCode> code) {
    interCode = code;
}

Actuator::~Actuator() {

}

bool Actuator::runCode() {
    try {
        while(true) {
            runOnelineCode(interCode[index]);
            index++;
            if (index>=(int)interCode.size()) break;
        }
    } catch (ActuatorException e) {
        win->addoutput(e.message+"\n");
        return false;
    }

    return true;
}

bool Actuator::runOnelineCode(InterCode code) {
    string type = code.getInstructType();
    if (type=="INT_DCL") {
        declareInt(code.getSecondElm(), code.getThirdElm(), code.getFourthElm());
    } else if (type=="REAL_DCL") {
        declareReal(code.getSecondElm(), code.getThirdElm(), code.getFourthElm());
    } else if (type=="ASG") {
        assignment(code.getSecondElm(), code.getThirdElm(), code.getFourthElm());
    } else if (type=="RED") {
        read(code.getSecondElm(), code.getThirdElm(), code.getFourthElm());
    } else if (type=="WRT") {
        write(code.getSecondElm(), code.getThirdElm(), code.getFourthElm());
    } else if (type=="PLU") {
        plus(code.getSecondElm(), code.getThirdElm(), code.getFourthElm());
    } else if (type=="MINU") {
        minu(code.getSecondElm(), code.getThirdElm(), code.getFourthElm());
    } else if (type=="DIVIDE") {
        divide(code.getSecondElm(), code.getThirdElm(), code.getFourthElm());
    } else if (type=="JMP") {
        jump(code.getSecondElm(), code.getThirdElm());
    } else if (type=="MULTIPLY") {
        multiply(code.getSecondElm(), code.getThirdElm(), code.getFourthElm());
    } else if (type=="IN") {
        in();
    } else if (type=="OUT") {
        out();
    } else {
        compare(type, code.getSecondElm(), code.getThirdElm());
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
    double value;
    if (isnumber(third)>=0) {
        value = atof(third.c_str());
    } else {
        auto node = symbolTable.findNode(third);
        if (node.type==symbolType::integer)
            value = node.getIntegerValue();
        else
            value = node.getDoubleValue();
    }

    int index = 0;
    if (second!="NULL") {
        if (isnumber(second)==0)
            index = atoi(second.c_str());
        else {
            auto node = symbolTable.findNode(second);
            if (node.type==symbolType::integer)
                index = node.getIntegerValue();
            else {
                // todo: error
            }
        }
    }

    auto node = symbolTable.findNode(first);

    if (node.type==symbolType::integer || node.type==symbolType::integerArray)
        symbolTable.changeNode(first, (int)value, index);
    else
        symbolTable.changeNode(first, value, index);

}

void Actuator::plus(string first, string second, string third) {
    double num = 0; bool isreal = false;
    auto t = symbolTable.findNode(third);
//    if (t.type==symbolType::none) {
//        symbolTable.addNode(symbolType::real, third);
//    }

    if (isnumber(first)==0)
        num += atoi(first.c_str());
    else if (isnumber(first)==1) {
        isreal = true;
        num += atof(first.c_str());
    }
    else {
        auto x = symbolTable.findNode(first);
        if (x.type==symbolType::integer)
            num += x.getIntegerValue();
        else if (x.type==symbolType::real) {
            num += x.getDoubleValue();
            isreal = true;
        }
        else {
            if (x.type==symbolType::integerArray)
                num += x.getIntegerValue(atoi(second.c_str()));
            else if (x.type==symbolType::realArray) {
                isreal = true;
                num += x.getDoubleValue(atoi(second.c_str()));
            }

            if (t.type == symbolType::none) {
                if (isreal) {
                    symbolTable.addNode(symbolType::real, third);

                } else {
                    symbolTable.addNode(symbolType::integer, third);

                }
            }
            if (isreal) {
                symbolTable.changeNode(third, num);
            } else {
                symbolTable.changeNode(third, (int)num);
            }
            return ;
        }
    }

    if (isnumber(second)==0)
        num += atoi(second.c_str());
    else if (isnumber(second)==1)
        num += atof(second.c_str());
    else {
        auto x = symbolTable.findNode(second);
        if (x.type==symbolType::integer)
            num += x.getIntegerValue();
        else
            num += x.getDoubleValue();
    }

    if (t.type == symbolType::none) {
        if (isreal) {
            symbolTable.addNode(symbolType::real, third);
        }
        else {
            symbolTable.addNode(symbolType::integer, third);
        }
    }
    if (isreal) {
        symbolTable.changeNode(third, num);
    } else {
        symbolTable.changeNode(third, (int)num);
    }

}

void Actuator::minu(string first, string second, string third) {
    double num = 0;
    auto t = symbolTable.findNode(third);
    if (t.type==symbolType::none) {
        symbolTable.addNode(symbolType::real, third);
    }

    if (isnumber(first)==0)
        num += atoi(first.c_str());
    else if (isnumber(first)==1)
        num += atof(first.c_str());
    else {
        auto x = symbolTable.findNode(first);
        if (x.type==symbolType::integer)
            num += x.getIntegerValue();
        else
            num += x.getDoubleValue();
    }

    if (isnumber(second)==0)
        num -= atoi(second.c_str());
    else if (isnumber(second)==1)
        num -= atof(second.c_str());
    else {
        auto x = symbolTable.findNode(second);
        if (x.type==symbolType::integer)
            num -= x.getIntegerValue();
        else
            num -= x.getDoubleValue();
    }

    if (t.type==symbolType::integer)
        symbolTable.changeNode(third, (int)num);
    else
        symbolTable.changeNode(third, num);
}

void Actuator::divide(string first, string second, string third) {
    // todo: chushu 0 check
    double num = 0;
    auto t = symbolTable.findNode(third);
    auto f = symbolTable.findNode(first);
    auto s = symbolTable.findNode(second);
    if (t.type==symbolType::none) {
        symbolTable.addNode(symbolType::real, third);
    }

    if (s.type == symbolType::none) {
        if (isnumber(second)==0) {
            if (atoi(second.c_str()) == 0) throw ActuatorException("Can't divide 0!");
        } else if (isnumber(second)>0) {
            if (abs(atof(second.c_str()))<(1e-8)) throw ActuatorException("Can't divide 0!");
        } else {
            throw ActuatorException("Can't recogize \""+second+"\"!");
        }
    } else if (s.type == symbolType::real) {
        if (abs(s.getDoubleValue())<(1e-8)) throw ActuatorException("Can't divide 0!");
    } else if (s.type == symbolType::integer) {
        if (s.getIntegerValue()==0) throw ActuatorException("Can't divide 0!");
    }

    if (s.type == symbolType::none && f.type == symbolType::none) {
        if (isnumber(second)>0||isnumber(first)>0) {
            num = atof(first.c_str())/atof(second.c_str());
        } else {
            num = atoi(first.c_str())/atoi(second.c_str());
        }
    } else if (f.type != symbolType::none) {
        if (s.type != symbolType::none) {
            if (f.type == symbolType::real || f.type == symbolType::real) {
                if (f.type == symbolType::real)
                    num += f.getDoubleValue();
                else
                    num += f.getIntegerValue();

                if (s.type == symbolType::real)
                    num /= s.getDoubleValue();
                else
                    num /= s.getIntegerValue();
            } else {
                num = f.getIntegerValue()/s.getIntegerValue();
            }
        } else {
            if (f.type == symbolType::real || isnumber(second)>0) {
                if (f.type == symbolType::real)
                    num += f.getDoubleValue();
                else
                    num += f.getIntegerValue();

                num /= atof(second.c_str());
            } else {
                num = f.getIntegerValue()/atoi(second.c_str());
            }
        }
    } else {
        if (isnumber(first)>0||s.type==symbolType::real) {
            num += atof(first.c_str());
            if (s.type==symbolType::real)
                num /= s.getDoubleValue();
            else
                num /= s.getIntegerValue();
        } else {
            num = atoi(first.c_str())/s.getIntegerValue();
        }
    }

    if (t.type==symbolType::integer) {
        symbolTable.changeNode(third, (int)num);
    } else {
        symbolTable.changeNode(third, (double)num);
    }
}

void Actuator::read(string first, string second, string third) {
    auto node = symbolTable.findNode(first);
    if (node.type!=symbolType::none) {
        string input = win->getinput();
        if (node.type==symbolType::integer) {
            if (isnumber(input)==0)
                symbolTable.changeNode(first, atoi(input.c_str()));
            else {
                // todo: error
                throw ActuatorException("\""+input+"\" is not a integer!");
            }
        } else {
            if (isnumber(input)>=0)
                symbolTable.changeNode(first, atof(input.c_str()));
            else {
                // todo: error
                throw ActuatorException("\""+input+"\" is not a number!");
            }
        }
    } else {
        //todo: error
    }
}

void Actuator::write(string first, string second, string third) {
   if (isnumber(first)>=0)
        this->win->addoutput(first+"\n");
    else {
        auto node = symbolTable.findNode(first);
        if (node.type==symbolType::integer)
            this->win->addoutput(to_string(node.getIntegerValue())+"\n");
        else
            this->win->addoutput(to_string(node.getDoubleValue())+"\n");
    }
}

void Actuator::multiply(string first, string second, string third) {
    double num = 0;
    auto t = symbolTable.findNode(third);
    if (t.type==symbolType::none) {
        symbolTable.addNode(symbolType::real, third);
    }

    if (isnumber(first)==0)
        num += atoi(first.c_str());
    else if (isnumber(first)==1)
        num += atof(first.c_str());
    else {
        auto x = symbolTable.findNode(first);
        if (x.type==symbolType::integer)
            num += x.getIntegerValue();
        else
            num += x.getDoubleValue();
    }

    if (isnumber(second)==0)
        num *= atoi(second.c_str());
    else if (isnumber(second)==1)
        num *= atof(second.c_str());
    else {
        auto x = symbolTable.findNode(second);
        if (x.type==symbolType::integer)
            num *= x.getIntegerValue();
        else
            num *= x.getDoubleValue();
    }

    if (t.type==symbolType::integer)
        symbolTable.changeNode(third, (int)num);
    else
        symbolTable.changeNode(third, num);
}

void Actuator::jump(string first, string second) {
    if (second=="NULL") {
        index = atoi(first.c_str()) - 1;
    } else {
        if (cmp)
            index = atoi(first.c_str()) - 1;
        else
            index = atoi(second.c_str()) - 1;
    }
}

void Actuator::in() {
    symbolTable.addTable();
}

void Actuator::out() {
    symbolTable.deleteTable();
}

void Actuator::compare(string first, string second, string third) {
    double a, b;

    if (isnumber(second)>=0) {
        a = atof(second.c_str());
    } else {
        auto x = symbolTable.findNode(second);
        if (x.type == symbolType::integer) {
            a = x.getIntegerValue();
        } else if (x.type==symbolType::real) {
            a = x.getDoubleValue();
        } else {
            return;
        }
    }

    if (isnumber(third)>=0) {
        b = atof(third.c_str());
    } else {
        auto x = symbolTable.findNode(third);
        if (x.type == symbolType::integer) {
            b = x.getIntegerValue();
        } else if (x.type==symbolType::real) {
            b = x.getDoubleValue();
        } else {
            return;
        }
    }


    if (first==">") {
        if (a>b) cmp = true; else cmp = false;
    } else if (first==">=") {
        if (a-b>=0) cmp = true; else cmp = false;
    } else if (first=="==") {
        if (abs(a-b)<1e-6) cmp = true; else cmp = false;
    } else if (first=="<") {
        if (a<b) cmp = true; else cmp = false;
    } else if (first=="<=") {
        if (b-a>=0) cmp = true; else cmp = false;
    } else if (first=="<>") {
        if (abs(b-a)<1e-6) cmp = true; else cmp = false;
    } else {
        return;
    }
}

void Actuator::bindWin(MainWindow * win) {
    this->win = win;
}
