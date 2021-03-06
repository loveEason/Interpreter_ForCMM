#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <string>
#include <map>
#include "mainwindow.h"
#include "CodeGenerator.h"

class MainWindow;

// 符号类型
enum symbolType {
    none=-1,
    integer = 0,
    integerArray,
    real,
    realArray
};


//符号表节点
struct SymbolNode {
    string name;
    symbolType type;
    int length; //数组长度
    void* value;
    SymbolNode():type(symbolType::none),length(0),value(0){}
    SymbolNode(string _name, symbolType _type, int _length);
    SymbolNode(const SymbolNode&);
    ~SymbolNode();
    int getIntegerValue(int index=0);
    double getDoubleValue(int index=0);
    void setIntegerValue(int value, int index=0);
    void setDoubleValue(double value, int index=0);
};

// 符号表
class Symbol {
public:
    Symbol();
    ~Symbol();
    void addTable(); // 添加新一层符号表
    void deleteTable(); // 删除最内层符号表
    void addNode(symbolType, string, int length=1); // 在当前层添加符号
    SymbolNode findNode(string name); // 查找符号

    // 修改符号
    void changeNode(string name, int value, int index=0);
    void changeNode(string name, double value, int index=0);

private:
    vector<map<string, SymbolNode>> symbolTable;
};

class ActuatorException {
public:
    string message = "";
    ActuatorException() {}
    ActuatorException(string msg) {
        message = msg;
    }
    ActuatorException(const ActuatorException& exc) {
        message = exc.message;
    }
};

// 解释器
class Actuator {
private:
    Symbol symbolTable;
    treeNode* nodes;
    int index = 0;
    bool cmp;
    vector<InterCode> interCode;
    MainWindow *win;
    string errorMsg = "";
public:
    Actuator(vector<InterCode>);
    ~Actuator();
    void bindWin(MainWindow*);
    bool runCode();
    bool runOnelineCode(InterCode);
    void in();
    void out();
    void declareInt(string first, string second, string third);
    void declareReal(string first, string second, string third);
    void assignment(string first, string second, string third);
    void plus(string first, string second, string third);
    void read(string first, string second, string third);
    void write(string first, string second, string third);
    void minu(string first, string second, string third);
    void divide(string first, string second, string third);
    void multiply(string first, string second, string third);
    void jump(string first, string second);
    void compare(string first, string second, string third);
};

#endif // ACTUATOR_H
