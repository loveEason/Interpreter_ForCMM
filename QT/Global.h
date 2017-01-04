//
// Created by huxijie on 16-10-18.
// 全局设置的头文件


#ifndef CMM_INTERPRETER_GLOBAL_H
#define CMM_INTERPRETER_GLOBAL_H

#include <iostream>
#include <vector>

#include <fstream>
using namespace std;


//const int FALSE = 0;
//const int TRUE = 1;
const int MAXCHILDREN = 20;
const int MAXTREENODE = 1024;
const int BUFLEN = 256;

//token的类型
typedef enum {
    ENDFILE,ERROR,
    //标识符
    IDENTIFIER,
    //整数与实数
    INT_VAL,FLOAT_VAL,
    //保留字
    IF,ELSE,WHILE,FOR,READ,WRITE,INT,REAL,
    BREAK,SWITCH,CASE,RETURN,
    //运算符
    PLUS,PLUS_PLUS,PLUS_EQL,                // + ++ +=
    MINUS,MINUS_MINUS,MINUS_EQL,            // - -- -=
    MUL,MUL_EQL,                            // * *=
    DIV,DIV_EQL,                            // / /=
    MOD,MOD_EQL,                            // % %=
    ASSIGN,LES,LES_EQL,GRT,GRT_EQL,EQL,NOT_EQL,    // = < <= > >= == <>
    //限界符
    LEFT_BRA,RIGHT_BRA,                     // ( )
    LEFT_INDEX,RIGHT_INDEX,                 // [ ]
    LEFT_BOUNDER,RIGHT_BOUNDER,             // { }
    POINTER,COMMA,SEMI,SIN_QUE,DOU_QUE,   // . , ; ' "
    //注释
    LINE_NOTE,                              // //注释
    MUL_NOTE                                // /**/注释
} TokenType;


struct normalNode {          //普通节点，用来组织成token链表，最后链表作为输入符号串用于语法分析过程中
    string content;         //内容
    int type;               //类型
    string tokenStr;        //以字符串形式表示的token
    int addr;               //入口地址，除去标识符以外的token入口地址都默认为-1
    int line;               //所在行数
    normalNode *next;        //下个节点
};

struct identifierNode {     //标识符节点，用来组织成标识符链表
    string content;         //内容
    int addr;               //入口地址，意思是所有同个标识符的入口地址将会一样，都是标识符第一次出现时的地址
    int line;               //所在行数
    identifierNode *next;   //下个节点
};

struct errorNode {          //错误节点，用来组织成错误链表
    string content;         //内容
    int line;               //所在行数
    errorNode *next;        //下个节点
};

struct treeNode {           //语法树节点
    string content;         //文法符号内容
    int type;               //类型
    string tokenStr;        //以字符串形式表示的token
    string value;           //常量或变量表示的值
    int line;               //所在行数
    int childNum;           //孩子数目
    treeNode* children[MAXCHILDREN];
    treeNode(string s) {    //构造函数
        content = s;
        type = -1;
        tokenStr = "\0";
        value = "\0";
        line = -1;
        childNum = 0;
    }


    treeNode() {
        content = "\0";
        type = -1;
        tokenStr = "\0";
        value = "\0";
        line = -1;
        childNum = 0;
    }
};

struct ParseError {         //语法分析出错信息
    string content;         //出错处文法符号内容
    int line;               //所在行数
};

////栈结构，实现长度自动增长缩小
//struct myStack {
//    string *item = NULL;
//    int max;                //能存的元素最大个数
//    int n;                  //已存的元素个数
//
//    myStack(int newMax) {
//        max = newMax;
//        item = new string[max];
//        n = 0;
//    }
//
//    void resize(int newMax) {
//        max = newMax;
//        string *temp = new string[newMax];
//        for (int i = 0; i < n; ++i) {
//            temp[i] = item[i];
//        }
//        delete[] item;
//        item = temp;
//    }
//    void push(string s) {
//        if (n == max) resize(max * 2);
//        item[n++] = s;
//    }
//    string top() {
//        return item[n - 1];
//    }
//
//    void pop() {
//        n--;
//        item[n] = '\0';
//        if (n > 0 && n == max / 4) resize(max / 2);
//    }
//};

//栈结构，实现长度自动增长缩小
struct myStack {
    treeNode **item = NULL;
    int max;                //能存的元素最大个数
    int n;                  //已存的元素个数

    myStack(int newMax) {
        max = newMax;
        item = new treeNode*[max];
        n = 0;
    }

    void resize(int newMax) {
        max = newMax;
        treeNode **temp = new treeNode*[newMax];
        for (int i = 0; i < n; ++i) {
            temp[i] = item[i];
        }
        delete[] item;
        item = temp;
    }
    void push(treeNode *s) {
        if (n == max) resize(max * 2);
        item[n++] = s;
    }
    treeNode* top() {
        return item[n - 1];
    }

    void pop() {
        n--;
        item[n] = NULL;
        if (n > 0 && n == max / 4) resize(max / 2);
    }
};

//DFA的状态
typedef enum {
    START,
    INNUM,INREAL0,INREAL,INID,INPLUS,INMIN,INMUL,INDIV,INMOD,INSPECIAL,
    INASSIGN,INLES,INGRT,
    INLINECOMMENT,INMULCOMMENT1,INMULCOMMENT2,
    DONE
} StateType;

//存放产生式的结构
struct production{
    string noneTerminalSymbol;  //非终结符
    vector<string> generation;  //该非终结符的产生式右部
};



#endif //CMM_INTERPRETER_GLOBAL_H



