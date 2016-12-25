#pragma once
#include <iostream>
#include <string>
using namespace std;

#define INT_DCL "INT_DCL"
#define REAL_DCL "REAL_DCL"
#define ASG "ASG"
#define ASGRA "ASGRA"   //
#define RED "RED"
#define WRT "WRT"
#define JMP "JMP"

#define PLU "PLU"
#define MINU "MINU"
#define MULTIPLY "MULTIPLY"
#define DIVIDE "DIVIDE"
#define REM "REM"

#define EQUAL "EQUAL"
#define GREATER_THAN "GREATER_THAN"
#define LESS_THAN "LESS_THAN"
#define NO_GREATER_THAN "NO_GREATER_THAN"
#define NO_LESS_THAN "NO_LESS_THAN"
#define NOT_EQUAL 1"NOT_EQUAL"
//#define TRUE "TRUE"
//#define FALSE "FALSE"
class InterCode
{
private:
    string instructType;
	string secondElm;
	string thirdElm;
	string fourthElm;
    bool isDelete;     //在优化过程中使用，记录是否该中间代码是否需要删除
    bool isModified;   //记录在优化过程中该中间代码是否被修改过
    int line;
public:
    InterCode(string instructType, string secondElm, string thirdElm, string fourthElm);
    InterCode(string instructType, string secondElm, string thirdElm, string fourthElm, int line);
    string getInstructType();
	string getSecondElm();
	string getThirdElm();
	string getFourthElm();
    bool getIsDelete();
    bool getIsModified();
    int getLine();
	void setSecondElm(string secondElm);
	void setThirdElm(string thirdElm);
	void setFourthElm(string fourthElm);
    void setLine(int line);
    void setIsDelete(bool isDelete);
    void setIsModified(bool isModified);
	void printCode();
	~InterCode();
};

