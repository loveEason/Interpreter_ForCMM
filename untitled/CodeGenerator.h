#pragma once
#include "InterCode.h"
#include "Global.h"
#include "SimpleSymbol.h"
#include "CheckTable.h"
#include <vector>

#define TEMP "0temp"+to_string(tpCount++)

class CodeGenerator
{
private:
    vector<InterCode> codeList;
    CheckTable * checkTable;
    int layer = 0;
    int tpCount = 0;   //用来记录在中间代码中使用的中间变量的序号，作为中间变量名字的一部分
    int jmpBcOff = 0;     //标记在多层嵌套中循环语句需要跳回的地址的偏移量，每进一个程序块则加一
public:
	CodeGenerator();
	~CodeGenerator();
    void interpretPrg(treeNode * node);
	void interpretDcl(treeNode * node);
	void interpretAsg(treeNode * node);
    void interpretRed(treeNode * node);
    void interpretWrt(treeNode * node, int line);
	void interpretIf(treeNode * node);
	void interpretLoop(treeNode * node);
	string interpretExp(treeNode * node);
	string interpretFactor(treeNode * node);
    string interpretSubFct(treeNode * node);   //解析<因式>
    vector<InterCode> getCode();
    void printCode();
    void clearCode();
private:
    void createCode(string op, string second, string third, string fourth, int line);
    void createCode(string op, string second, string third, string fourth);  //生成一条四元式并加入codeList
    string calIndex(treeNode * node);  //计算数组下标，传入参数为<因式>结点
    void printError(string error, int pos);
    //对数组进行初始化时调用，解析“{}”中的每个数据，传入赋值号左边的<ID>结点和<数据>结点
    void parseValue(treeNode * ident, treeNode * node, string index);
    //判断该变量为单一变量还是数组变量，并进行对应的操作（赋值、read、write）
    void parseVar(string op, treeNode * ident, treeNode * index, string value);
    //判断该变量为单一变量还是数组变量，并对其进行计算（+=、-=、*=、/=、%=）
    void calVar(string op, treeNode * ident, treeNode * index, string value);
    bool checkSymbol(treeNode * id);      //检查使用变量前是否已声明，传入<ID>结点
    bool checkIsArray(treeNode * id);     //检查变量是否是数组，传入<ID>结点
    //对数组元素进行操作，op为运算符，ident为数组变量名，index为下标，value为操作数
    void opArrayElm(string op, string ident, string index, string value, int line);
};

