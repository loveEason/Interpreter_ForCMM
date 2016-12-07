#pragma once
#include "InterCode.h"
#include "Global.h"
#include "SimpleSymbol.h"
#include "CheckTable.h"
#include <vector>
class CodeGenerator
{
private:
private:
	vector<InterCode *> codeList;
    CheckTable * checkTable;
    int layer = 1;
public:
	CodeGenerator();
	~CodeGenerator();
    void interpretPrg(treeNode * node);
	void interpretDcl(treeNode * node);
	void interpretAsg(treeNode * node);
	void interpretRed(treeNode * node);
	void interpretWrt(treeNode * node);
	void interpretIf(treeNode * node);
	void interpretLoop(treeNode * node);
	string interpretExp(treeNode * node);
	string interpretTerm(treeNode * node);
	string interpretFactor(treeNode * node);
};

