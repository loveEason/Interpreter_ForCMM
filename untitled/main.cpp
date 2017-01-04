#include <iosfwd>
#include <iostream>
#include <fstream>
#include "Global.h"
#include "LexAnalysis.h"
#include "Parse.h"
#include "actuator.h"
#include "CodeGenerator.h"

using namespace std;


int lineNo;          //源文件中行的序号
ofstream parseTree_file; //语法树结果文件
#define BUFLEN 256

int main(int argc,char *argv[]) {
    LexAnalysis lexAnalysis;
//    if (argc == 1) {    //不提供参数,默认为从控制台输入源程序
//        lexAnalysis.lexAnalyse();
//    } else if (argc == 2) {     //从参数中打开源代码文件
//        lexAnalysis.lexAnalyse(1,argv[1]);
//    } else {
//        printf("Usage：%s or %s filename\n",argv[0],argv[0]);
//    }

//    string code = "int i=1;\n"
//                  "if(i>0){i=i-1;}";
    string code = "int";
    lexAnalysis.lexAnalyse(code);

    if (lexAnalysis.ifHasError()) {
        cout<<"Invalid token,please rectify:"<<endl;
        errorNode *p = lexAnalysis.getErrorHead();
        while (p->next != NULL) {
            cout<<"Line at "<<p->next->line<<":"<<p->next->content<<endl;
            p = p->next;
        }
    } else {    //词法分析正确,开始语法分析
        normalNode* normalHead = lexAnalysis.getNormalHead();
        Parse parse;
        bool isSuccess = parse.grammarAnalyse(normalHead);
        if(isSuccess == false) {
            ParseError *parseError = parse.getParseError();
            cout<<"there is something wrong happened near line "<<parseError->line<<" :"<<parseError->content<<endl;

            return -1;
        }

        CodeGenerator *cg = new CodeGenerator();
        cg->interpretPrg(parse.getTreeRoot());
        cg->printCode();
        Actuator actuator(cg->getCode());
        actuator.runCode();
        cg->clearCode();
        delete cg;
    }

    return 0;
}
