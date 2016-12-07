#pragma once
#include <iostream>
#include <string>
using namespace std;

#define INT_DCL 1
#define REAL_DCL 2
#define ASG 3
#define RED 4
#define WRT 5
#define JMP 6
//À„ ı‘ÀÀ„∑˚
#define PLU 7
#define MINU 8
#define MULTIPLE 9
#define DIVIDE 10
//¬ﬂº≠‘ÀÀ„∑˚
#define EQUAL 11
#define GREATER_THAN 12
#define LESS_THAN 13
#define NO_GREATER_THAN 14
#define NO_LESS_THAN 15
#define NOT_EQUAL 16
#define TRUE 17
#define FALSE 18
class InterCode
{
private:
	int instructType;
	string secondElm;
	string thirdElm;
	string fourthElm;
public:
	InterCode(int instructType, string secondElm, string thirdElm, string fourthElm);
	int getInstructType();
	string getSecondElm();
	string getThirdElm();
	string getFourthElm();
	void setSecondElm(string secondElm);
	void setThirdElm(string thirdElm);
	void setFourthElm(string fourthElm);
	void printCode();
	~InterCode();
};

