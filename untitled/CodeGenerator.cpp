#include "CodeGenerator.h"



CodeGenerator::CodeGenerator(){}


CodeGenerator::~CodeGenerator(){}

void CodeGenerator::interpretPrg(treeNode * node) {
    if(node->content=="<程序>"){
        if(node->children[0]->content=="$"){
            return;
        }
        node = node->children[0];   //<程序> -> <程序块>
    }

    if(node->children[0]->children[0]->content!="$"){
        interpretDcl(node->children[0]);     //传入<声明语句闭包>结点
    }

    if(node->children[1]->children[0]->content!="$"){
        node = node->children[1];  //<程序块> -> <声明语句闭包> <程序块闭包>
        if(node->children[0]->content=="$"){     //判断<程序块闭包>是否为空
            return;
        }else{
            treeNode *node1 = node->children[0];
            treeNode *node2 = node->children[1];
            if(node1->content=="<条件语句>"){
                interpretIf(node1);
            }else if(node1->content=="<while循环>"){
                interpretLoop(node1);
            }
            interpretPrg(node2);
        }
    }
}

void CodeGenerator::interpretDcl(treeNode * node) {
    //<声明语句闭包> -> <声明语句> <声明语句闭包>
    treeNode * node1 = node->children[0]->children[0];  //node1为<声明>
    treeNode * type = node1->children[0];
    treeNode * var = node1->children[1];

    if(node1->children[2]->children[0]->content!="$"){
        treeNode * value = node1->children[2];
    }
    treeNode * node2 = node->children[1];    //node2为<声明语句闭包>
    if(node2->children[0]->content!="$"){
        interpretDcl(node2);
    }

}

void CodeGenerator::interpretAsg(treeNode * node) {
    cout<<"do nothing";
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
