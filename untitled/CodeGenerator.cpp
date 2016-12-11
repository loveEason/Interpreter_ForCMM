#include "CodeGenerator.h"



CodeGenerator::CodeGenerator(){
    checkTable = new CheckTable();
}


CodeGenerator::~CodeGenerator(){
    delete checkTable;
}

void CodeGenerator::interpretPrg(treeNode * node) {
    if(node->content=="<program>"){
        if(node->children[0]->content=="$"){
            return;
        }
        node = node->children[0];   //node为<block>
    }
    if(node->children[0]->content==";"){
        return;
    }

    if(node->children[0]->children[0]->content!="$"){
        interpretDcl(node->children[0]);     //传入<declare_closure>结点
    }

    if(node->children[1]->children[0]->content!="$"){
        node = node->children[1];  //node为<block_closure>

        treeNode *node1 = node->children[0];  //node1为各类语句节点
        treeNode *node2 = node->children[1];  //node2为程序块
        if(node1->content=="<if_stmt>"){
            interpretIf(node1);
        }else if(node1->content=="<while_loop>"){
            interpretLoop(node1);
        }else if(node1->content=="<for_loop>"){
            interpretLoop(node1);
        }else if(node1->content=="<assignment>"){
            interpretAsg(node1);
        }else if(node1->content=="<functions>"){
            treeNode * func = node1->children[0]->children[0];
            treeNode * param = func->children[2];     //param为函数参数结点
            if(func->children[0]->content=="read"){
                interpretRed(param);
            }else{
                interpretWrt(param);
            }
        }
        interpretPrg(node2);
    }
}

void CodeGenerator::interpretDcl(treeNode * node) {
    treeNode * node1 = NULL;
    if(node->content=="<declare_closure>"){    //node1为<declare>
        node1 = node->children[0]->children[0];
    }else{
        node1 = node->children[0];
    }
    treeNode * type = node1->children[0];
    string decType = type->children[0]->content=="int"?INT_DCL:REAL_DCL;  //判断声明的类型
    treeNode * var = node1->children[1];
    treeNode * ident = var->children[0]->children[0];
    treeNode * index = var->children[1];               //index为<index>
    bool isArray = false;
    if(index->children[0]->content!="$"){              //数组下标不为空的情况下
        isArray = true;
        treeNode * idex = index->children[1];  //idex为<factor_type>
        string id = calIndex(idex);
        createCode(decType, ident->value, id, "");
    }

    SimpleSymbol *s = new SimpleSymbol(ident->value, type->children[0]->type, layer, ident->line, isArray);
    checkTable->addSymbol(s);

    if(node1->children[2]->children[0]->content!="$"){         //判断是否初始化变量
        treeNode * value = node1->children[2]->children[1];    //value为<right_value>
        if(value->children[0]->content=="<expression>"&&isArray){   //判断初始化的方式是否合理
            printError("Invalid initialization for array", ident->line);
        }else if(value->children[0]->content=="<expression>"&&!isArray){
            string v = interpretExp(value->children[0]);
            createCode(decType, ident->value, "", v);
        }else if(value->children[0]->content=="{"&&!isArray){           //value为多个值（数组声明时赋值）
            printError("Invalid initialization for variable", ident->line);
        }else if(value->children[0]->content=="{"&&isArray){
            treeNode * values = value->children[1];              //values为<datas>
            treeNode * data = values->children[0];               //data为<data>
            parseValue(ident, data, "0");
            treeNode * nextData = values->children[1];           //nextData为<data_closure>
            for(int i=1;nextData->children[0]->content!="$";i++){
                treeNode * data = nextData->children[1];
                parseValue(ident, data, to_string(i));
                nextData = nextData->children[2];
            }
        }
    }else{
        createCode(decType, ident->value, "", "");
    }


    treeNode * node2 = node->children[1];    //node2为<declare_closure>
    if(node2->content==";"){
        return;
    }else if(node2->children[0]->content!="$"){
        interpretDcl(node2);
    }
}

void CodeGenerator::interpretAsg(treeNode * node) {
    if(node->children[0]->content=="<self_op>"){
        treeNode * op = node->children[0]->children[0];  //op为++或--
        treeNode * ident = node->children[1]->children[0]->children[0];
        if(checkSymbol(ident)){
            treeNode * index = node->children[1]->children[1];
            string opt = op->content=="++"?PLU:MINU;
            calVar(opt, ident, index, "1");
        }
    }else if(node->children[0]->content=="<variable>"){
        treeNode * ident = node->children[0]->children[0]->children[0];
        if(checkSymbol(ident)){
            treeNode * index = node->children[0]->children[1];
            treeNode * assign = node->children[1];   //assign为<assign>
            treeNode * op = assign->children[0];
            if(op->content!="<self_op>"){
                string value = interpretExp(assign->children[1]->children[0]);  //value为右值的值
                if(op->content=="="){
                    parseVar(ASG, ident, index, value);
                }else if(op->content=="+="){
                    calVar(PLU, ident, index, value);
                }else if(op->content=="-="){
                    calVar(MINU, ident, index, value);
                }else if(op->content=="*="){
                    calVar(MULTIPLY, ident, index, value);
                }else if(op->content=="/="){
                    calVar(DIVIDE, ident, index, value);
                }else if(op->content=="%="){
                    calVar(REM, ident, index, value);
                }
            }else{
                string opt = op->children[0]->content=="++"?PLU:MINU;
                calVar(opt, ident, index, "1");
            }
        }
    }
}

void CodeGenerator::interpretRed(treeNode * node) {
    treeNode * ident = node->children[0]->children[0];    //id为<ID>结点
    if(checkSymbol(ident)){
        treeNode * index = node->children[1];              //index为<数组下标>结点
        parseVar(RED, ident, index, "");
    }
}

void CodeGenerator::interpretWrt(treeNode * node) {
    if(node->children[0]->content=="<constant>"){
        treeNode * constValue = node->children[0]->children[0]->children[0];
        createCode(WRT, constValue->value, "", "");
    }else if(node->children[0]->content=="<variable>"){
        treeNode * ident = node->children[0]->children[0]->children[0];   //ident为<ID>结点
        if(checkSymbol(ident)){
            treeNode * index = node->children[0]->children[1];        //index为<index>结点
            parseVar(WRT, ident, index, "");
        }
    }else if(node->children[0]->content=="<expression>"){
        treeNode * exp = node->children[0];
        string value = interpretExp(exp);
        createCode(WRT, value, "", "");
    }
}

void CodeGenerator::interpretIf(treeNode * node) {
    treeNode * condBlock = node->children[1];          //condBlock为<if_block>
    treeNode * condition = condBlock->children[1];     //condition为<logic_exp>
    treeNode * proBlock = condBlock->children[3];      //proBlock为<cpd_block>
    treeNode * elseBlock = condBlock->children[4];     //elseBlock为<else>
    treeNode * leftExp = condition->children[0];
    treeNode * logicOp = condition->children[1]->children[0];
    treeNode * rightExp = condition->children[2];
    string leftValue = interpretExp(leftExp);
    string rightValue = interpretExp(rightExp);
    createCode(logicOp->content, leftValue, rightValue, "");

    treeNode * block = proBlock->children[1];
    int pos = codeList.size();          //jmpCode插入codeList的位置
    InterCode *jmpCode = new InterCode(JMP, to_string(pos+1), "", "");

    layer++;
    interpretPrg(block);
    layer--;

    int jmpPos = codeList.size()+1;     //条件不满足时应该跳至的位置
    jmpCode->setThirdElm(to_string(jmpPos));
    codeList.insert(codeList.begin()+pos, jmpCode);

    if(elseBlock->children[0]->content!="$"){
        treeNode * elsePro = elseBlock->children[1]->children[1];
        layer++;
        interpretPrg(elsePro);
        layer--;
    }
}

void CodeGenerator::interpretLoop(treeNode * node) {
    if(node->content=="<while_loop>"){         //当为while循环
        treeNode * whileBlock = node->children[1];    //whileBlock为<while_block>
        treeNode * condition = whileBlock->children[1];  //condition为<logic_exp>
        treeNode * proBlock = whileBlock->children[3];   //proBlock为<cpd_block>
        treeNode * leftExp = condition->children[0];
        treeNode * logicOp = condition->children[1]->children[0];
        treeNode * rightExp = condition->children[2];
        string leftValue = interpretExp(leftExp);
        string rightValue = interpretExp(rightExp);
        createCode(logicOp->content, leftValue, rightValue, "");

        treeNode * block = proBlock->children[1];
        int pos = codeList.size();
        InterCode *jmpCode = new InterCode(JMP, to_string(pos+1), "", "");

        layer++;
        interpretPrg(block);
        layer--;

        int jmpPos = codeList.size()+2;        //循环条件不满足时应该跳至的位置
        jmpCode->setThirdElm(to_string(jmpPos));
        codeList.insert(codeList.begin()+pos, jmpCode);
        createCode(JMP, to_string(pos-1), "", "");   //执行完一次循环后跳转至条件判断处
    }else{                                   //当为for循环
        treeNode * forBlock = node->children[1];
        treeNode * decOrAsg = forBlock->children[1];
        treeNode * condition = forBlock->children[2];
        treeNode * innerAsg = forBlock->children[4];
        treeNode * block = forBlock->children[6]->children[1];

        layer++;
        if(decOrAsg->children[0]->content=="<declaration>"){
            interpretDcl(decOrAsg->children[0]);
        }else{
            interpretAsg(decOrAsg->children[0]);
        }

        treeNode * leftExp = condition->children[0];
        treeNode * logicOp = condition->children[1]->children[0];
        treeNode * rightExp = condition->children[2];
        string leftValue = interpretExp(leftExp);
        string rightValue = interpretExp(rightExp);
        createCode(logicOp->content, leftValue, rightValue, "");

        int pos = codeList.size();
        InterCode * jmpCode = new InterCode(JMP, to_string(pos+1), "", "");

        interpretPrg(block);
        interpretAsg(innerAsg);
        layer--;
        int jmpPos = codeList.size()+2;
        jmpCode->setThirdElm(to_string(jmpPos));
        codeList.insert(codeList.begin()+pos, jmpCode);
        createCode(JMP, to_string(pos-1), "", "");

    }

}

string CodeGenerator::interpretExp(treeNode * node) {
    treeNode * factor = node->children[0];     //factor为<factor>
    treeNode * term = node->children[1];       //term为<term>
    string temp1 = interpretFactor(factor);    //temp1为解析第一个<factor>所得结果
    if(term->children[0]->content=="$"){
        return temp1;
    }else{
        while(term->children[0]->content!="$"){
            string op = term->children[0]->content;
            string fctRs = interpretFactor(term->children[1]);
            string temp2 = TEMP;
            if(op=="+"){
                createCode(PLU, temp1, fctRs, temp2);
            }else{
                createCode(MINU, temp1, fctRs, temp2);
            }
            term = term->children[2];
            temp1 = temp2;
        }
        return temp1;
    }

}

string CodeGenerator::interpretSubFct(treeNode *node){   //传入参数为<因式>结点
    if(node->children[0]->content=="<number>"){
        treeNode * num = node->children[0]->children[0];
        return num->value;
    }else if(node->children[0]->content=="<variable>"){
        treeNode * ident = node->children[0]->children[0]->children[0];
        if(checkSymbol(ident)){
            treeNode * index = node->children[0]->children[1];
            if(index->children[0]->content!="$"&&checkIsArray(ident)){     //数组下标不为空且该变量为数组
                treeNode * idex = index->children[1];          //idex为<因式>结点
                string id = calIndex(idex);
                string temp = TEMP;
                createCode(ASGRA, temp, ident->value, id);
                return temp;
            }else if(index->children[0]->content=="$"&&!checkIsArray(ident)){  //数组下标为空且该变量不为数组
                return ident->value;
            }else if(ident->children[0]->content=="$"&&checkIsArray(ident)){   //数组下标为空而该变量为数组则默认下标为0
                string temp = TEMP;
                createCode(ASGRA, temp, ident->value, "0");
                return temp;
            }else{       //数组下标不为空而该变量不为数组，报错
                printError("Variable can't be accessed by index", ident->line);
            }
        }
    }else if(node->children[1]->content=="<expression>"){
        treeNode * exp = node->children[1];
        return interpretExp(exp);
    }
    return "";
}

string CodeGenerator::interpretFactor(treeNode * node) {
    treeNode * subFct = node->children[0];    //subFct为<factor_type>
    treeNode * nextFct = node->children[1];   //nextFct为<factor_recursion>
    string temp = interpretSubFct(subFct);    //temp为解析第一个<factor_type>所得结果
    string temp2 = temp;     //若<factor_recursion>为空，则直接返回解析<factor_type>所得结果
    while(nextFct->children[0]->content!="$"){
        string op = nextFct->children[0]->content;
        string subFctRs = interpretSubFct(nextFct->children[1]);
        temp2 = TEMP;
        if(op=="*"){
            createCode(MULTIPLY, temp, subFctRs, temp2);
        }else if(op=="/"){
            createCode(DIVIDE, temp, subFctRs, temp2);
        }else{
            createCode(REM, temp, subFctRs, temp2);
        }
        nextFct = nextFct->children[2];
        temp = temp2;
    }
    return temp2;
}

void CodeGenerator::createCode(string op, string second, string third, string fourth){
    InterCode *code = new InterCode(op, second, third, fourth);
    codeList.push_back(code);
}

void CodeGenerator::printError(string error, int pos){
    cout<<error<<". At line "<<pos<<"."<<endl;
}

string CodeGenerator::calIndex(treeNode * node){
    string index;
    if(node->children[0]->content=="<variable>"){
        treeNode * ident = node->children[0]->children[0]->children[0];
        treeNode * id = node->children[0]->children[1];
        if(id->children[0]->content!="$"&&checkIsArray(ident)){     //数组下标不为空且该变量为数组
            treeNode * idex = id->children[1];          //idex为<因式>结点
            string subId = calIndex(idex);
            index = TEMP;
            createCode(ASGRA, index, ident->value, subId);
        }else if(id->children[0]->content=="$"&&!checkIsArray(ident)){  //数组下标为空且该变量不为数组
            index = ident->value;
        }else if(id->children[0]->content=="$"&&checkIsArray(ident)){   //数组下标为空而该变量为数组则默认下标为0
            index = TEMP;
            createCode(ASGRA, index, ident->value, "0");
        }else{       //数组下标不为空而该变量不为数组，报错
            printError("Variable can't be accessed by index", ident->line);
        }
    }else if(node->children[0]->content=="<number>"){
        index = node->children[0]->children[0]->value;
        if(index.find(".")!=string::npos||index.find("-")!=string::npos){  //判断数字是否不是非负整数
            printError("Invalid array index", node->children[0]->children[0]->line);
        }
    }else if(node->children[1]->content=="<expression>"){
        index = interpretExp(node->children[1]);
    }
    return index;
}

void CodeGenerator::parseValue(treeNode * ident, treeNode *node, string index){
    if(node->children[0]->content=="<constant>"){
        treeNode * constant = node->children[0];         //constant为<常量>
        treeNode * number = constant->children[0]->children[0];   //number为具体数字
        createCode(ASG, ident->value, index, number->value); //改成value
    }else if(node->children[0]->content=="<variable>"){
        treeNode * variable = node->children[0];       //variable为变量
        treeNode * asgIdent = variable->children[0]->children[0];
        checkSymbol(asgIdent);
        treeNode * asgIndex = variable->children[1];
        if(asgIndex->children[0]->content=="$"){                //用单一变量给数组元素赋值
            createCode(ASG, ident->value, index, asgIdent->value);
        }else{                                         //用数组元素给数组元素赋值，利用中间变量TEMP
            string asgId = calIndex(asgIndex);
            string temp = TEMP;
            createCode(ASGRA, temp, asgIdent->value, asgIndex->value);
            createCode(ASG, ident->value, index, temp);
        }
    }else if(node->children[0]->content=="<expression>"){
        treeNode * exp = node->children[0];
        string v = interpretExp(exp);
        createCode(ASG, ident->value, index, v);
    }
}

void CodeGenerator::parseVar(string op, treeNode * ident, treeNode * index, string value){
    if(index->children[0]->content!="$"&&checkIsArray(ident)){     //数组下标不为空且该变量为数组
        treeNode * idex = index->children[1];          //idex为<因式>结点
        string id = calIndex(idex);
        createCode(op, ident->value, id, value);
    }else if(index->children[0]->content=="$"&&!checkIsArray(ident)){  //数组下标为空且该变量不为数组
        createCode(op, ident->value, "", value);
    }else if(ident->children[0]->content=="$"&&checkIsArray(ident)){   //数组下标为空而该变量为数组则默认下标为0
        createCode(op, ident->value, "0", value);
    }else{       //数组下标不为空而该变量不为数组，报错
        printError("Variable can't be accessed by index", ident->line);
    }
}

void CodeGenerator::calVar(string op, treeNode * ident, treeNode * index, string value){
    if(index->children[0]->content!="$"&&checkIsArray(ident)){     //数组下标不为空且该变量为数组
        treeNode * idex = index->children[1];          //idex为<因式>结点
        string id = calIndex(idex);
        opArrayElm(op, ident->value, id, value);
    }else if(index->children[0]->content=="$"&&!checkIsArray(ident)){  //数组下标为空且该变量不为数组
        createCode(op, ident->value, value, ident->value);
    }else if(ident->children[0]->content=="$"&&checkIsArray(ident)){   //数组下标为空而该变量为数组则默认下标为0
        opArrayElm(op, ident->value, "0", value);
    }else{       //数组下标不为空而该变量不为数组，报错
        printError("Variable can't be accessed by index", ident->line);
    }
}

bool CodeGenerator::checkSymbol(treeNode * id){      //判断变量使用前是否已声明
    if(!checkTable->containsSymbol(id->value, layer)){
        printError("Variable "+id->value+" has not been declared", id->line);
        return false;
    }
    return true;
}

bool CodeGenerator::checkIsArray(treeNode * id){   //判断变量是否是数组变量
    return checkTable->getSymbol(id->value)->isArraySymbol();
}

void CodeGenerator::opArrayElm(string op, string ident, string index, string value){
    string temp1 = TEMP;
    string temp2 = TEMP;
    createCode(ASGRA, temp1, ident, index);    //将数组元素值赋给中间变量
    createCode(op, temp1, value, temp2);    //对中间变量进行操作
    createCode(ASG, ident, index, temp2);    //将结果值赋给数组元素
}

void CodeGenerator::printCode(){
    cout<<"InterCodes are as follow:"<<endl;
    for(int i=0;i<(signed)codeList.size();i++){
        codeList[i]->printCode();
    }
}

void CodeGenerator::clearCode(){
    for(int i=0;i<(signed)codeList.size();i++){
        delete codeList.at(i);
    }
}
