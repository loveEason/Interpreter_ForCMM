//
// Created by huxijie on 16-10-18.
// 词法分析源文件


#include "LexAnalysis.h"
#include <string.h>
#include <iomanip>


using namespace std;


LexAnalysis::LexAnalysis() {
    lineNo = 0;
    bufSize = 0;         //目前行的长度
    linepos = 0;         //目前行中的字符当前位置
    EOF_flag = FALSE;
    normalHead = NULL;
    idenHead = NULL;
    errorHead = NULL;
    iden_addr = 0;                      //标识符的入口地址起点
    hasError = false;

    initKeyMap();
    initSpecialMap();
    initNode();
}

LexAnalysis::~LexAnalysis() {
    delete normalHead;
    delete idenHead;
    delete errorHead;
}

//词法分析是否出错，给外部调用
bool LexAnalysis::ifHasError(){
    return hasError;
}

normalNode* LexAnalysis::getNormalHead(){
    return normalHead;
}

identifierNode* LexAnalysis::getIdenHead(){
    return idenHead;
}

errorNode* LexAnalysis::getErrorHead(){
    return errorHead;
}


//初始化keyMap
void LexAnalysis::initKeyMap() {
    keyMap.insert(make_pair("if", IF));
    keyMap.insert(make_pair("else", ELSE));
    keyMap.insert(make_pair("while", WHILE));
    keyMap.insert(make_pair("for", FOR));
    keyMap.insert(make_pair("read", READ));
    keyMap.insert(make_pair("write", WRITE));
    keyMap.insert(make_pair("int", INT));
    keyMap.insert(make_pair("real", REAL));
    keyMap.insert(make_pair("break", BREAK));
    keyMap.insert(make_pair("switch", SWITCH));
    keyMap.insert(make_pair("case", CASE));
    keyMap.insert(make_pair("return", RETURN));
}



//初始化specialMap
void LexAnalysis::initSpecialMap() {
    specialMap.insert(make_pair("++", PLUS_PLUS));
    specialMap.insert(make_pair("+=", PLUS_EQL));
    specialMap.insert(make_pair("--", MINUS_MINUS));
    specialMap.insert(make_pair("-=", MINUS_EQL));
    specialMap.insert(make_pair("*=", MUL_EQL));
    specialMap.insert(make_pair("/=", DIV_EQL));
    specialMap.insert(make_pair("%=", MOD_EQL));
    specialMap.insert(make_pair("<=", LES_EQL));
    specialMap.insert(make_pair(">=", GRT_EQL));
    specialMap.insert(make_pair("==", EQL));
    specialMap.insert(make_pair("<>", NOT_EQL));
}

//初始化节点，链表都是由空的头节点组织成的
void LexAnalysis::initNode() {
    normalHead = new normalNode();
    normalHead->content = "";
    normalHead->type= -1;
    normalHead->addr = -1;
    normalHead->line = -1;
    normalHead->next = NULL;

    idenHead = new identifierNode();
    idenHead->content = "";
    idenHead->addr = -1;
    idenHead->line = -1;
    idenHead->next = NULL;

    errorHead = new errorNode();
    errorHead->content = "";
    errorHead->line = -1;
    errorHead->next = NULL;
}

//从lineBuf中获取下个字符
char LexAnalysis::getNextChar(istream &source_file,ostream &lex_file,int flag) {
    if (!(linepos < bufSize)) { //说明此行已经读完了
        lineNo++;
        if (!source_file.eof()) {  //再读取一行
            source_file.getline(lineBuf,BUFLEN);
            if (flag == 0 && lineBuf[0] == '#') {   //flag为0表示是控制台输入,设定#是程序结束标志
                EOF_flag = TRUE;
                return EOF;
            }
            lex_file<<setw(4)<<lineNo<<": "<<lineBuf<<endl;       //同时将此行内容写入词法分析结果文件
            linepos = 0;
            bufSize = strlen(lineBuf);
            return lineBuf[linepos++];
        } else {
            if (flag == 1) {                //flag为1表示是文件输入,设定到达文件结尾表示程序结束标志
                EOF_flag = TRUE;
                return EOF;
            }
        }
    } else {
        return lineBuf[linepos++];
    }
}

//取消获取下一个字符，也就是撤消上一次的取字符操作
void LexAnalysis::unGetNextChar() {
    if (!EOF_flag) linepos--;
}


//判断字符是否为空白
bool LexAnalysis::isBlank(char c) {
    if ((c == ' ') || (c == '\t') || c == '\n' || c == '\0') {
        return true;
    }
    else return false;
}


//判断字符是否为运算符、限界符、注释的第一个字符
bool LexAnalysis::isFirst(char c) {
    int n = sizeof(check)/ sizeof(check[0]);
    for (int i = 0; i < n; ++i) {
        if (c == check[i]) return true;
    }
    return false;
}

//生成新normalNode
void LexAnalysis::createNewNode(string content,int type,string tokenStr,int addr, int line) {
    normalNode *p = normalHead;
    normalNode *tmp = new normalNode();

    while (p->next != NULL) {
        p = p->next;
    }

    tmp->content = content;
    tmp->type = type;
    tmp->tokenStr = tokenStr;
    tmp->addr = addr;
    tmp->line = line;
    tmp->next = NULL;

    p->next = tmp;
}

//生成新identifierNode,返回值是标志符第一次出现时的入口地址
int LexAnalysis::createNewIden(string content,int addr, int line) {
    identifierNode *p = idenHead;
    identifierNode *tmp = new identifierNode();
    int flag = 0;
    int addr_tmp = -2;

    while (p->next != NULL) {
        if (content == p->next->content) {
            flag = 1;
            addr_tmp = p->next->addr;
        }
        p = p->next;
    }
    if (flag == 0) {    //表示此标识符是第一次出现
        addr_tmp = ++iden_addr;     //将此地址作为该标识符的入口地址
    }

    tmp->content = content;
    tmp->addr = addr_tmp;
    tmp->line = line;
    tmp->next = NULL;

    p->next = tmp;
    return addr_tmp;
}

//生成新errorNode
void LexAnalysis::createNewError(string content, int line) {
    errorNode *p = errorHead;
    errorNode *tmp = new errorNode();

    while (p->next != NULL) {
        p = p->next;
    }

    tmp->content = content;
    tmp->line = line;
    tmp->next = NULL;

    p->next = tmp;
}


void LexAnalysis::printToken(istream &source_file,ostream &lex_file,TokenType token, const string tokenString) {
    switch (token) {
        case IDENTIFIER:
            lex_file<<"Identifier:  "<<tokenString<<endl;
            break;
        case INT_VAL:
            lex_file<<"Int value:  "<<tokenString<<endl;
            break;
        case FLOAT_VAL:
            lex_file<<"Real value:  "<<tokenString<<endl;
            break;
        case IF:
        case ELSE:
        case WHILE:
        case READ:
        case WRITE:
        case FOR:
        case INT:
        case REAL:
        case BREAK:
        case SWITCH:
        case CASE:
        case RETURN:
            lex_file<<"Key word: "<<tokenString<<endl;
            break;
        case PLUS:
        case PLUS_PLUS:
        case PLUS_EQL:
        case MINUS:
        case MINUS_MINUS:
        case MINUS_EQL:
        case MUL:
        case MUL_EQL:
        case DIV:
        case DIV_EQL:
        case MOD:
        case MOD_EQL:
        case ASSIGN:
        case LES:
        case LES_EQL:
        case GRT:
        case GRT_EQL:
        case EQL:
        case NOT_EQL:
            lex_file<<"Operator: "<<tokenString<<endl;
            break;
        case LEFT_BRA:
        case RIGHT_BRA:
        case LEFT_INDEX:
        case RIGHT_INDEX:
        case LEFT_BOUNDER:
        case RIGHT_BOUNDER:
        case POINTER:
        case COMMA:
        case SEMI:
        case SIN_QUE:
        case DOU_QUE:
            lex_file<<"Limitor: "<<tokenString<<endl;
            break;
        case ERROR:
            lex_file<<"Error, invalid token: "<<tokenString<<endl;
            break;
    }
}


//用来从源文件中解析出下个token
TokenType LexAnalysis::getToken(istream &source_file,ostream &lex_file,int flag) {
    TokenType currentToken;
    StateType stateType = START;    //DFA的开始
    int isSave;                     //用于判断是否将字符存进当前tokenString
    while (stateType != DONE) {
        char c = getNextChar(source_file,lex_file,flag);
        if (EOF_flag && flag == 0) {  //在控制台输入情况下经过取字符发现已经到达文件尾,即读到了#,则先将c置为#,先处理上一个还没保存的token,再退出分析
            c = '#';
        } else if (EOF_flag && flag == 1) {
            return ENDFILE;
        }
        isSave = TRUE;
        switch (stateType) {
            case START:
                if (isBlank(c)) {   //是空白的则跳过
                    isSave = FALSE;
                } else if (isdigit(c)) {
                    stateType = INNUM;
                } else if (isalpha(c)) {
                    stateType = INID;
                } else if (c == '+') {
                    stateType = INPLUS;
                } else if (c == '-') {
                    stateType = INMIN;
                } else if (c == '*') {
                    stateType = INMUL;
                } else if (c == '/') {
                    stateType = INDIV;
                } else if (c == '%') {
                    stateType = INMOD;
                } else if (c == '=') {
                    stateType = INASSIGN;
                } else if (c == '<') {
                    stateType = INLES;
                } else if (c == '>') {
                    stateType = INGRT;
                } else if (c == '(') {
                    currentToken = LEFT_BRA;
                    stateType = DONE;
                } else if (c == ')') {
                    currentToken = RIGHT_BRA;
                    stateType = DONE;
                } else if (c == '[') {
                    currentToken = LEFT_INDEX;
                    stateType = DONE;
                } else if (c == ']') {
                    currentToken = RIGHT_INDEX;
                    stateType = DONE;
                } else if (c == '{') {
                    currentToken = LEFT_BOUNDER;
                    stateType = DONE;
                } else if (c == '}') {
                    currentToken = RIGHT_BOUNDER;
                    stateType = DONE;
                } else if (c == '.') {
                    currentToken = POINTER;
                    stateType = DONE;
                } else if (c == ',') {
                    currentToken = COMMA;
                    stateType = DONE;
                } else if (c == ';') {
                    currentToken = SEMI;
                    stateType = DONE;
                } else if (c == '\'') {
                    currentToken = SIN_QUE;
                    stateType = DONE;
                } else if (c == '\"') {
                    currentToken = DOU_QUE;
                    stateType = DONE;
                } else if (c == '#') {
                    stateType = DONE;
                    currentToken = ENDFILE;
                    isSave = FALSE;
                } else {
                    currentToken = ERROR;
                    stateType = DONE;
                }
                break;
            case INNUM:
                if (isdigit(c)) {
                    stateType = INNUM;
                }else if (c == '.') {
                    stateType = INREAL0;
                } else if (isBlank(c) || isFirst(c) || c == '#') { //本编译器设定如果是控制台输入源程序的话需要以#结尾,此判断条件是为了防止上个token还没保存就退出分析了
                    isSave = FALSE;     //当前字符不能存入tokenString中，因为已经识别出是个token了
                    unGetNextChar();
                    stateType = DONE;
                    currentToken = INT_VAL;
                } else {
                    currentToken = ERROR;
                    stateType = DONE;
                }
                break;
            case INREAL0:
                if (isdigit(c)) {
                    stateType = INREAL;
                } else {
                    currentToken = ERROR;
                    stateType = DONE;
                }
                break;
            case INREAL:
                if (isdigit(c)) {
                    stateType = INREAL;
                }else if (isBlank(c) || isFirst(c) || c == '#') {
                    isSave = FALSE;
                    unGetNextChar();
                    stateType = DONE;
                    currentToken = FLOAT_VAL;
                }else {
                    currentToken = ERROR;
                    stateType = DONE;
                }
                break;
            case INID:
                if (isalpha(c) || isdigit(c) || c == '_') {
                    stateType = INID;
                } else if (isBlank(c) || isFirst(c) || c == '#') {
                    isSave = FALSE;
                    unGetNextChar();
                    stateType = DONE;
                    currentToken = IDENTIFIER;
                } else {
                    currentToken = ERROR;
                    stateType = DONE;
                }
                break;
            case INPLUS:
                if (c == '+' || c == '=') {
                    stateType = INSPECIAL;
                } else {
                    isSave = FALSE;
                    unGetNextChar();
                    stateType = DONE;
                    currentToken = PLUS;
                }
                break;
            case INMIN:
                if (c == '-' || c == '=') {
                    stateType = INSPECIAL;
                } else {
                    isSave = FALSE;
                    unGetNextChar();
                    stateType = DONE;
                    currentToken = MINUS;
                }
                break;
            case INMUL:
                if (c == '=') {
                    stateType = INSPECIAL;
                } else {
                    isSave = FALSE;
                    unGetNextChar();
                    stateType = DONE;
                    currentToken = MUL;
                }
                break;
            case INDIV:
                if ( c == '=') {
                    stateType = INSPECIAL;
                } else if (c == '/') {
                    isSave = FALSE;
                    stateType = INLINECOMMENT;
                } else if (c == '*') {
                    isSave = FALSE;
                    stateType = INMULCOMMENT1;
                } else {
                    isSave = FALSE;
                    unGetNextChar();
                    stateType = DONE;
                    currentToken = DIV;
                }
                break;
            case INLINECOMMENT:
                isSave = FALSE;
                stateType = INLINECOMMENT;
                if (linepos>=bufSize) {
                    currentToken = LINE_NOTE;
                    stateType = DONE;
                }
                break;
            case INMULCOMMENT1:
                isSave = FALSE;
                if (c == '*') {
                    stateType = INMULCOMMENT2;
                }
                break;
            case INMULCOMMENT2:
                isSave = FALSE;
                if (c == '*') {
                    stateType = INMULCOMMENT2;
                } else if (c == '/') {
                    currentToken = MUL_NOTE;
                    stateType = DONE;
                } else {
                    stateType = INMULCOMMENT1;
                }
                break;
            case INMOD:
                if (c == '=') {
                    stateType = INSPECIAL;
                } else {
                    isSave = FALSE;
                    unGetNextChar();
                    stateType = DONE;
                    currentToken = MOD;
                }
                break;
            case INASSIGN:
                if (c == '=') {
                    stateType = INSPECIAL;
                } else {
                    isSave = FALSE;
                    unGetNextChar();
                    stateType = DONE;
                    currentToken = ASSIGN;
                }
                break;
            case INLES:
                if (c == '=' || c == '>') {
                    stateType = INSPECIAL;
                } else {
                    isSave = FALSE;
                    unGetNextChar();
                    stateType = DONE;
                    currentToken = LES;
                }
                break;
            case INGRT:
                if (c == '=' ) {
                    stateType = INSPECIAL;
                } else {
                    isSave = FALSE;
                    unGetNextChar();
                    stateType = DONE;
                    currentToken = GRT;
                }
                break;
            case INSPECIAL:     //对于特殊的token进行分析处理,在此状态下不进行存储新字符
                isSave = FALSE;
                unGetNextChar();
                stateType = DONE;
                currentToken = (TokenType)(specialMap.find(tokenString)->second);
                break;
        }
        if (isSave) {
            tokenString.append(1,c);
        }
        if (stateType == DONE) {
            if (currentToken == IDENTIFIER) {       //在标识符中进一步分析，看看是不是保留字
                if ((iter = keyMap.find(tokenString)) != keyMap.end()) {
                    currentToken = (TokenType) iter->second;
                }
            } else if (currentToken == LINE_NOTE || currentToken == MUL_NOTE) {
                tokenString.erase(0,tokenString.length());  //将tokenString中的元素都擦除
                return currentToken;
            }
        }
    }
    //保存到普通节点中
    //依次判断是否是标识符、错误
    if (currentToken == IDENTIFIER) {
        int addr_tmp = createNewIden(tokenString, -1, lineNo);
        createNewNode(tokenString, IDENTIFIER,"ID", addr_tmp, lineNo);
    } else if (currentToken == INT_VAL) {
        createNewNode(tokenString, INT_VAL, "INT_VALUE", -1, lineNo);
    } else if (currentToken == FLOAT_VAL) {
        createNewNode(tokenString, FLOAT_VAL, "FLOAT_VALUE", -1, lineNo);
    } else if (currentToken == ERROR) {
        hasError = true;
        createNewError(tokenString, lineNo);
    } else if (currentToken == ENDFILE) {   //对应控制台输入的情况,之前因为读到了#,所以将token置为ENDFILE,表示可以退出分析
        return ENDFILE;
    } else {
        createNewNode(tokenString, currentToken, tokenString, -1, lineNo);
    }
    //输出到文件中
    lex_file<<setw(8)<<lineNo<<":";
    printToken(source_file,lex_file,currentToken, tokenString);
    tokenString.erase(0,tokenString.length());  //将tokenString中的元素都擦除
    return currentToken;

}

//源代码从控制台输入
void LexAnalysis::lexAnalyse(){
    lex_file.open("./console.lex",ios::out);
    cout << "Please enter your code and end entering with #" << endl;
    lex_file << "Lexical result is as follow:" << endl;
    while (getToken(cin,lex_file,0) != ENDFILE) ;
    lex_file.close();
    lex_file.open("./console.lex", ios::in);
    char readStr[BUFLEN];
    while (!lex_file.eof()) {
        lex_file.getline(readStr, BUFLEN);
        cout << readStr << endl;
    }
    lex_file.close();
}

//源代码从文件输入
void LexAnalysis::lexAnalyse(int isFile,string source_name){
    string suffix = ".cmm"; //后缀名
    string lex_name;
    int pos = source_name.find(suffix);
    if (pos == string::npos) {     //加上后缀名
        source_name.append(suffix);
    }
    source_file.open(source_name, ios::in);
    if (!source_file.is_open()) {
        cout << "Failed to open the file. " << source_name << endl;
        exit(-1);
    }
    lex_name.append(source_name);
    if (pos == string::npos) {
        lex_name.append(".lex");
    } else {
        lex_name.replace(pos, 4, ".lex");
    }
    lex_file.open(lex_name, ios::out);
    lex_file << "Lexical result is as follow：" << endl;
    while (getToken(source_file,lex_file,1) != ENDFILE);         //一直分析token,直到源代码已经分析结束

    lex_file.close();
    source_file.close();
}

//源代码从字符串中读入
void LexAnalysis::lexAnalyse(string sourceCode) {
    lex_file.open("./sourcecodeLex.lex",ios::out);
    lex_file << "Lexical result is as follow:" << endl;

    source_code.str(sourceCode);
    while (getToken(source_code,lex_file,1) != ENDFILE) ;
    lex_file.close();

}


