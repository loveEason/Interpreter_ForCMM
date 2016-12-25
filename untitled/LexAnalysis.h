//
// Created by huxijie on 16-10-18.
// 词法分析头文件

#ifndef CMM_INTERPRETER_LEXANALYSIS_H
#define CMM_INTERPRETER_LEXANALYSIS_H

#include "Global.h"
#include <map>



class LexAnalysis{
private:
    std::string tokenString;
    map<const string,int> keyMap;     //存放保留字的map,用于检索
    map<const string,int> specialMap; //存入特殊token的map,用于检索。特殊token指的是双字符的token
    bool hasError;                           //词法分析中是否出现错误
    ifstream source_file;    //源文件
    fstream lex_file;       //词法分析结果文件

    char lineBuf[BUFLEN];    //存放每一行
    int lineNo;              //源文件中行的序号
    int bufSize;         //目前行的长度
    int linepos;         //目前行中的字符当前位置
    int EOF_flag;
    char check[18] = {'+','-','*','/','%','=','<','>','(',')','[',']','{','}',',',';','\'','\"'};
    map<const string,int>::iterator iter;
    normalNode *normalHead;
    identifierNode *idenHead;
    errorNode *errorHead;
    int iden_addr;                      //标识符的入口地址起点

    void initKeyMap();                       //初始化keyMap
    void initSpecialMap();                   //初始化specialMap
    void initNode();                         //初始化节点，链表都是由空的头节点组织成的

    char getNextChar(istream &source_file,ostream &lex_file,int flag);
    void unGetNextChar();    //取消获取下一个字符，也就是撤消上一次的取字符操作
    bool isBlank(char c);   //判断字符是否为空白
    bool isFirst(char c);   //判断字符是否为运算符、限界符、注释的第一个字符
    void createNewNode(string content,int type,string tokenStr,int addr, int line);    //生成新normalNode
    int createNewIden(string content,int addr, int line);   //生成新identifierNode,返回值是标志符第一次出现时的入口地址
    void createNewError(string content, int line);          //生成新errorNode
    void printToken(std::istream &,std::ostream &,TokenType,const std::string);    //打印token,通过istream和ostream实现多态,达到控制台输入输出或者文件输入输出

    //用来从源文件中解析出下个token
    //传递参数istream和ostream,实现多态流操作
    //最后一个参数是用来分辨控制台输入还是文件输入,以实现不同的控制
    TokenType getToken(std::istream&,std::ostream&,int);

public:
    LexAnalysis();
    ~LexAnalysis();

    bool ifHasError();                       //词法分析是否出错，给外部调用
    normalNode* getNormalHead();
    identifierNode* getIdenHead();
    errorNode* getErrorHead();


    void lexAnalyse();
    void lexAnalyse(string sourceName);
};



#endif //CMM_INTERPRETER_LEXANALYSIS_H
