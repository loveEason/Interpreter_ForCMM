#include "optimize.h"

Optimize::Optimize()
{
    CodeGenerator cg = CodeGenerator();
    cg.interpretPrg(treeRoot);     //产生中间代码
    optmCodeList = cg.getCode();
}

void Optimize::optmOprt(){
    setIndex();
    int delCodeNum = 0; //记录被删除的中间代码条数
    int lastAddr = 0;
    for(int i=0;i<(signed)optmCodeList.size();i++){
        if(addrList.size()>0){    //修改有两个跳转地址的中间代码的第二个地址
            if(i+1==addrList.back().add2){
                int addr1 = addrList.back().add1;
                int addr2 = addrList.back().add2;
                lastAddr = addr2-delCodeNum;
                optmCodeList[addr1-1].setThirdElm(to_string(lastAddr));
                addrList.erase(addrList.end()-1);
            }
        }
        string op = optmCodeList.at(i).getInstructType();
        string number1 = optmCodeList.at(i).getSecondElm();
        string number2 = optmCodeList.at(i).getThirdElm();
        if(op=="RED"){
            continue;
        }
        else if(op=="JMP"&&number1!=""&&number2!=""){   //取两个地址均不为空的跳转语句，修改第一个跳转地址
            int addr1 = atoi(number1.c_str());
            int addr2 = atoi(number2.c_str());
            optmCodeList[i].setSecondElm(to_string(addr1-delCodeNum));
            addr a;
            a.add1 = addr1;
            a.add2 = addr2;
            a.delNum = delCodeNum;
            addrList.push_back(a);
            jmpDelNum j;
            j.index = i;
            j.delNum = delCodeNum;
            delNumList.push_back(j);
        }
        else if(op=="JMP"&&number1!=""&&number2==""){   //只有一个跳转地址的跳转语句，修改其跳转地址
            int addr1 = atoi(number1.c_str());
            int lastIndex = jmpBcLastIndex(i);
            int delNum = getCodeDelNum(lastIndex);
            optmCodeList[i].setSecondElm(to_string(addr1-delNum));
        }
        else if(op=="REM"){   //进行取余运算的只能是两个整数
            if(isIntNumber(number1)&&isIntNumber(number2)){
                int num1 = atoi(number1.c_str());
                int num2 = atoi(number2.c_str());
                string temp = optmCodeList.at(i).getFourthElm();
                tempMap.insert(pair<string, double>(temp, num1%num2));
                optmCodeList[i].setIsDelete(true);
                delCodeNum++;
            }else{
                cout<<"Invalid numbers for the operator '%'"<<endl;
            }
        }
        else if(isOperator(op)){
            if(isNumber(number1)&&isNumber(number2)){   //两个操作数都为数字
                if(isIntNumber(number1)&&isIntNumber(number2)){
                    int num1 = atoi(number1.c_str());
                    int num2 = atoi(number2.c_str());
                    string temp = optmCodeList[i].getFourthElm();
                    tempMap.insert(pair<string, int>(temp, doOperation(op, num1, num2)));
                }else{
                    double num1 = atof(number1.c_str());
                    double num2 = atof(number2.c_str());
                    string temp = optmCodeList.at(i).getFourthElm();
                    tempMap.insert(pair<string, double>(temp, doOperation(op, num1, num2)));
                }
                delCodeNum++;
                optmCodeList[i].setIsDelete(true);
            }else if(containsTemp(number1)&&isNumber(number2)){   //前一个为中间变量，后一个为数字
                double num1 = getTempValue(number1);
                double num2 = atof(number2.c_str());
                string temp = optmCodeList.at(i).getFourthElm();
                tempMap.insert(pair<string, double>(temp, doOperation(op, num1, num2)));
                delCodeNum++;
                optmCodeList[i].setIsDelete(true);
            }else if(containsTemp(number2)&&isNumber(number1)){   //前一个为数字，后一个为中间变量
                double num1 = atof(number1.c_str());
                double num2 = getTempValue(number2);
                string temp = optmCodeList.at(i).getFourthElm();
                tempMap.insert(pair<string, double>(temp, doOperation(op, num1, num2)));
                delCodeNum++;
                optmCodeList[i].setIsDelete(true);
            }else if(containsTemp(number1)&&containsTemp(number2)){  //两个操作数都为中间变量
                double num1 = getTempValue(number1);
                double num2 = getTempValue(number2);
                string temp = optmCodeList.at(i).getFourthElm();
                tempMap.insert(pair<string, double>(temp, doOperation(op, num1, num2)));
                delCodeNum++;
                optmCodeList[i].setIsDelete(true);
            }
        }else if(op=="ASG"&&containsTemp(optmCodeList[i].getFourthElm())){ //赋值语句用到中间变量
            double temp = getTempValue(optmCodeList[i].getFourthElm());
            optmCodeList[i].setFourthElm(to_string(temp));
        }else if(op=="WRT"&&containsTemp(optmCodeList[i].getSecondElm())){
            double temp = getTempValue(optmCodeList[i].getSecondElm());
            optmCodeList[i].setSecondElm(to_string(temp));
        }else if((op=="INT_DCL"||op=="REAL_DCL")&&containsTemp(optmCodeList[i].getFourthElm())){
            double temp = getTempValue(optmCodeList[i].getFourthElm());
            if(op=="INT_DCL"){
                int temp = getTempValue(optmCodeList[i].getFourthElm());
                optmCodeList[i].setFourthElm(to_string(temp));
            }else{
                optmCodeList[i].setFourthElm(to_string(temp));
            }
        }else if(isLogicOp(op)){  //若为逻辑运算符
            if(containsTemp(number1)&&containsTemp(number2)){
                double temp1 = getTempValue(optmCodeList[i].getSecondElm());
                double temp2 = getTempValue(optmCodeList[i].getThirdElm());
                optmCodeList[i].setSecondElm(to_string(temp1));
                optmCodeList[i].setThirdElm(to_string(temp2));
            }else if(containsTemp(number1)){
                double temp1 = getTempValue(optmCodeList[i].getSecondElm());
                optmCodeList[i].setSecondElm(to_string(temp1));
            }else if(containsTemp(number2)){
                double temp2 = getTempValue(optmCodeList[i].getThirdElm());
                optmCodeList[i].setThirdElm(to_string(temp2));
            }
        }
    }

    if(addrList.size()>0){
        for(int i=0;i<(signed)addrList.size();i++){
            int addr1 = addrList.at(i).add1;
            optmCodeList[addr1-1].setThirdElm(to_string(lastAddr));
        }
        addrList.clear();
    }
    deleteCode();
}

void Optimize::printCode(){
    for(int i=0;i<(signed)optmCodeList.size();i++){
        optmCodeList.at(i).printCode();
    }
}

bool Optimize::isNumber(string number){
    if(number==""){
        return false;
    }
    for(int i=0;i<(signed)number.size();i++){
        if((number.at(i)>'9'||number.at(i)<'0')){
            if(number.at(i)!='.'){
                return false;
            }
        }
    }
    return true;
}

bool Optimize::isIntNumber(string number){
    if(number==""){
        return false;
    }
    for(int i=0;i<(signed)number.size();i++){
        if(number.at(i)>'9'||number.at(i)<'0'||number.at(i)=='.'){
            return false;
        }
    }
    return true;
}

bool Optimize::containsTemp(string temp){
    map<string, double>::iterator it;
    for(it=tempMap.begin();it!=tempMap.end();it++){
       if(temp==it->first){
           return true;
       }
    }
    return false;
}

bool Optimize::isLogicOp(string op){
    if(op==">"||op=="<"||op==">="||op=="<="||op=="=="||op=="<>"){
        return true;
    }
    return false;
}

bool Optimize::isOperator(string op){
    if(op=="PLU"||op=="MINU"||op=="MULTIPLY"||op=="DIVIDE"){
        return true;
    }
    return false;
}

double Optimize::getTempValue(string temp){
    map<string, double>::iterator it;
    for(it=tempMap.begin();it!=tempMap.end();it++){
        if(temp==it->first){
            return it->second;
        }
    }
    return 0;
}

int Optimize::doOperation(string op, int num1, int num2){
    if(op=="PLU"){
        return num1+num2;
    }else if(op=="MINU"){
        return num1-num2;
    }else if(op=="MULTIPLY"){
        return num1*num2;
    }else{
        return num1/num2;
    }
}

double Optimize::doOperation(string op, double num1, double num2){
    if(isIntNumber(to_string(num1))&&isIntNumber(to_string(num2))){
        int intNum1 = (int)num1;
        int intNum2 = (int)num2;
        if(op=="PLU"){
            return intNum1+intNum2;
        }else if(op=="MINU"){
            return intNum1-intNum2;
        }else if(op=="MULTIPLY"){
            return intNum1*intNum2;
        }else{
            return intNum1/intNum2;
        }
    }
    if(op=="PLU"){
        return num1+num2;
    }else if(op=="MINU"){
        return num1-num2;
    }else if(op=="MULTIPLY"){
        return num1*num2;
    }else{
        return num1/num2;
    }
}

vector<InterCode> Optimize::getCode(){
    return optmCodeList;
}

bool Optimize::realIsInt(double number){
    string num = to_string(number);
    int pointIndex = 0;
    for(int i=0;i<num.size();i++){
        if(num.at(i)=='.'){
            pointIndex = i;
            break;
        }
    }
    for(int i=pointIndex+1;i<num.size();i++){
        if(num.at(i)!='0'){
            return false;
        }
    }
    return true;
}

void Optimize::deleteCode(){
    for(int i=0;i<(signed)optmCodeList.size();i++){
        if(optmCodeList[i].getIsDelete()){
            optmCodeList.erase(optmCodeList.begin()+i);
            i--;
        }
    }
}
void Optimize::setIndex(){
    for(int i=0;i<(signed)optmCodeList.size();i++){
        InterCode ic = optmCodeList[i];
        if(ic.getInstructType()=="JMP"&&ic.getThirdElm()!=""){
            int addr2 = atoi(ic.getThirdElm().c_str());
            if(optmCodeList[addr2-1].getInstructType()=="JMP"){
                if(jmpBcLastIndex(addr2-1)<i){
                    delJmpIndex(addr2-1);
                }
                jmpAddr j;
                j.seq = addr2-1;
                j.lastIndex = i;
                jmpList.push_back(j);
            }
        }
    }
}

int Optimize::jmpBcLastIndex(int seq){
    for(int i=0;i<(signed)jmpList.size();i++){
        jmpAddr j = jmpList[i];
        if(j.seq==seq){
            return j.lastIndex;
        }
    }
    return 0;
}

void Optimize::delJmpIndex(int seq){
    for(int i=0;i<(signed)jmpList.size();i++){
        if(jmpList[i].seq=seq){
            jmpList.erase(jmpList.begin()+i);
            return;
        }
    }
}

void Optimize::printIndex(){
    for(int i=0;i<(signed)jmpList.size();i++){
        cout<<"Jump back sequence:"<<jmpList[i].seq<<"Last index:"<<jmpList[i].lastIndex<<endl;
    }
}

int Optimize::getCodeDelNum(int index){
    for(int i=0;i<(signed)delNumList.size();i++){
        if(delNumList[i].index==index){
            return delNumList[i].delNum;
        }
    }
    return 0;
}
