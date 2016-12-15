#ifndef OPTIMIZE_H
#define OPTIMIZE_H
#include <map>
#include <string>
#include <vector>
#include <stdlib.h>
#include "InterCode.h"
#include "CodeGenerator.h"
#include "Parse.h"

class Optimize
{
private:
    vector<InterCode> optmCodeList;
    map<string, double> tempMap;   //用来存每个中间变量名和其存储的运算结果
    typedef struct addr{
        int add1;
        int add2;
        int delNum;   //记录当前跳转语句前删除的中间代码数
    }addr;
    typedef struct jmpAddr{//用来记录跳转返回代码的最后一次引用数
        int seq;           //seq为返回跳转代码的序数
        int lastIndex;     //lastIndex为最后一次跳至该代码的代码的序数
    }jmpAddr;
    typedef struct jmpDelNum{
        int index;         //跳转语句的序数
        int delNum;        //执行到该语句时删除的代码条数
    }jmpDelNum;
    vector<jmpDelNum> delNumList;
    vector<jmpAddr> jmpList;
    vector<addr> addrList;
public:
    Optimize();
    void optmOprt();  //优化运算
    void printCode();
    void printIndex();
    vector<InterCode> getCode();
private:
    bool realIsInt(double number);      //判断一个double类型的小数部分是否都为0
    bool isNumber(string number);
    bool isIntNumber(string number);
    bool isOperator(string op);
    bool containsTemp(string temp);     //判断该中间变量是否是前面运算语句所得结果
    bool isLogicOp(string op);          //判断是否进行的是比较运算
    int jmpBcLastIndex(int seq);        //获取最后一个指向跳转返回语句的跳转语句的序数，没有则返回0
    void delJmpIndex(int seq);
    double getTempValue(string temp);   //得到中间变量所存储的值
    int doOperation(string op, int num1, int num2);
    double doOperation(string op, double num1, double num2);
    void cgScdAddr(int delCodeNum);      //改变跳转语句的第二个地址
    void optmCondStmt();                 //判断逻辑表达式是否成立，删除跳转不到的语句
    void deleteCode();                   //删除被标记的中间代码
    void setIndex();                     //初始化jpBcMap
    int getCodeDelNum(int index);        //得到运行到某条中间代码时删除的代码条数
};

#endif // OPTIMIZE_H
