#include "CodeGenerator.h"



CodeGenerator::CodeGenerator(){}


CodeGenerator::~CodeGenerator(){}

void CodeGenerator::interpretPrg(treeNode * node) {
    if(node->content=="<程序>"){
        if(node->children[0]->content=="$"){
            return;
        }
        node = node->children[0];   //node为<程序块>
    }
    if(node->children[0]->content==";"){
        return;
    }

    if(node->children[0]->children[0]->content!="$"){
        interpretDcl(node->children[0]);     //传入<声明语句闭包>结点
    }

    if(node->children[1]->children[0]->content!="$"){
        node = node->children[1];  //node为<程序块闭包>

        treeNode *node1 = node->children[0];  //node1为各类语句节点
        treeNode *node2 = node->children[1];  //node2为程序块
        if(node1->content=="<条件语句>"){
            interpretIf(node1);
        }else if(node1->content=="<while循环>"){
            interpretLoop(node1);
        }else if(node1->content=="<for循环>"){
            interpretLoop(node1);
        }else if(node->content=="<赋值语句>"){
            interpretAsg(node1);
        }else if(node1->content=="<特殊函数>"){
            treeNode *temp = node1->children[0]->children[0]->children[0];    //temp为read或write结点
            if(temp->content=="read"){
                interpretRed(temp);
            }else{
                interpretWrt(temp);
            }
        }
        interpretPrg(node2);
    }
}

void CodeGenerator::interpretDcl(treeNode * node) {
    //<声明语句闭包> -> <声明语句> <声明语句闭包>
    treeNode * node1 = node->children[0]->children[0];  //node1为<声明>
    treeNode * type = node1->children[0];
    treeNode * var = node1->children[1];
    treeNode * ident = var->children[0]->children[0];

    SimpleSymbol *s = new SimpleSymbol(ident->content, type->children[0]->type, layer, ident->line);
    checkTable->addSymbol(s);

    if(node1->children[2]->children[0]->content!="$"){
        treeNode * value = node1->children[2]->children[1];    //value为<右值>
        if(value->children[0]->content=="<表达式>"){
            string v = interpretExp(value->children[0]);
        }else if(value->children[0]->content=="{"){           //value为多个值（数组声明时赋值）

        }
    }
    treeNode * node2 = node->children[1];    //node2为<声明语句闭包>
    if(node2->children[0]->content!="$"){
        interpretDcl(node2);
    }

}

void CodeGenerator::interpretAsg(treeNode * node) {
    if(node->children[0]->content=="<自增减运算符>"){
        treeNode * ident = node->children[1]->children[0]->children[0];
        //InterCode * code = InterCode(PLU, ident->content, "1", ident->content);

    }
}

void CodeGenerator::interpretRed(treeNode * node) {
    cout<<"do nothing";
}

void CodeGenerator::interpretWrt(treeNode * node) {
    cout<<"do nothing";
}

void CodeGenerator::interpretIf(treeNode * node) {
    cout<<"do nothing";
}

void CodeGenerator::interpretLoop(treeNode * node) {
    cout<<"do nothing";
}

string CodeGenerator::interpretExp(treeNode * node) {
    return "do nothing";
}

string CodeGenerator::interpretTerm(treeNode * node) {
    return "do nothing";
}

string CodeGenerator::interpretFactor(treeNode * node) {
    return "do nothing";
}
