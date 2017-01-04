//
// Created by huxijie on 16-11-15.
// 语法分析头文件

#ifndef CMM_INTERPRETER_PARSE_H
#define CMM_INTERPRETER_PARSE_H

#include "Global.h"
#include <vector>
#include <list>
#include <set>
#include <map>
#include <stack>

const int MAXNT = 128;                                  //非终结符的最大数量
const int MAX = 256;                                    //每行字符串最大长度


class Parse{
private:
    set<string> terminalSymbols ;                        //终结符集
    set<string> noneTerminalSymbols ;                    //非终结符集
    string startToken ;                                  //文法的开始符
    string totalProductions[MAXNT] ;                     //存放文法文件的每一行
    production productions[MAXNT] ;                      //将所有产生式存储为结构体。假定产生式"->"左右两边都有空格
    int productionSum;                                   //产生式数目
    map<string,set<string>> firstSet;                    //存有所有文法符号的first集合
    map<int ,set<string>> productionFirstSet;            //存有所有产生式的first集合
    map<string,set<string>> followSet;                   //存有所有非终结符的follow集合
    map<int,set<string>> selectSet;                      //存有所有产生式的select集合
    map<string,map<string,string>> predictionTable;      //预测分析表
    treeNode *treeRoot;
    myStack *analysisStack;                              //分析栈
    treeNode *treeStack[MAXTREENODE];
    int top;                                             //分析栈的栈顶指针
    ifstream grammar_file;                               //文法文件
    fstream parse_file;                                  //语法分析结果文件
    ofstream set_file;                                   //存放LL1分析中自动生成的集合以及预测分析表
    ofstream parseTree_file;                             //语法树结果文件

    //分隔字符串
    list<string> strtok_plus(string text,string delim);
    //保存非终结符到文件中
    void saveNoneTerminal(set<string> noneTerminalSymbols,ofstream &out);
    //保存终结符到文件中
    void saveTerminal(set<string> terminalSymbols,ofstream &out);
    //保存文法符号的first集到文件中
    void saveFirst(map<string,set<string>> firstSet,ofstream &out);
    //保存产生式的first集到文件中
    void saveProductionFirst(map<int,set<string>> productionFirstSet,ofstream &out);
    //保存非终结符的follow集到文件中
    void saveFollow(map<string,set<string>> followSet,ofstream &out);
    //保存产生式的select集到文件中
    void saveProductionSelect(map<int,set<string>> selectSet,ofstream &out);
    //保存预测分析表到文件中
    void savePredictionTable(map<string,map<string,string>> predictionTable,ofstream &out);
    //存入树中
    void addToTree(treeNode *tNode);
    //得到语法树栈的当前根节点
    treeNode *getTopNode();
    //保存语法树到xml文件中
    void saveTree(treeNode *pTree, ofstream &out);
    //处理文法中的运算符和限界符符号,转换为对应的英文说明
    string dealTerminalSymbols(string oldStr);
    //处理文法中的非终结符符号,去掉包围的<>
    string dealNoneTerminalSymbols(string oldStr);

    void saveProduction(string grammar_name);            //将文法文件中的产生式存储在数据结构中
    void buildFirstSet();                                //求所有文法符号的first集合
    void buildProductionFirstSet();                      //求所有产生式的first集合
    void buildFollowSet();                               //求所有非终结符的follow集合
    void buildSelectSet();                               //求所有产生式的select集合
    void buildPredictionTable();                         //构建预测分析表
    void showAnalysisStack(myStack *analysisStack);      //输出分析栈的内容
    void showRemainToken(normalNode *pCurrent);          //输出剩余输入串的内容

public:
    Parse();
    ~Parse();

    void grammarAnalyse(normalNode*);                    //正式进行语法分析
    treeNode* getTreeRoot();
};


#endif //CMM_INTERPRETER_PARSE_H
