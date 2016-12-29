#include "InterCode.h"


InterCode::InterCode(string instructType, string secondElm, string thirdElm, string fourthElm)
{
	this->instructType = instructType;
	this->secondElm = secondElm;
	this->thirdElm = thirdElm;
	this->fourthElm = fourthElm;
    this->isDelete = false;
    this->isModified = false;
}

InterCode::InterCode(string instructType, string secondElm, string thirdElm, string fourthElm, int line){
    this->instructType = instructType;
    this->secondElm = secondElm;
    this->thirdElm = thirdElm;
    this->fourthElm = fourthElm;
    this->line = line;
    this->isDelete = false;
    this->isModified = false;
}

InterCode::~InterCode()
{
}

string InterCode::getInstructType() {
	return this->instructType;
}

string InterCode::getSecondElm() {
	return this->secondElm;
}

string InterCode::getThirdElm() {
	return this->thirdElm;
}

string InterCode::getFourthElm() {
	return this->fourthElm;
}

int InterCode::getLine(){
    return this->line;
}

bool InterCode::getIsDelete(){
    return this->isDelete;
}

bool InterCode::getIsModified(){
    return this->isModified;
}

void InterCode::setLine(int line){
    this->line = line;
}

void InterCode::setSecondElm(string secondElm) {
	this->secondElm = secondElm;
}

void InterCode::setThirdElm(string thirdElm) {
	this->thirdElm = thirdElm;
}

void InterCode::setFourthElm(string fourthElm) {
	this->fourthElm = fourthElm;
}

void InterCode::setIsDelete(bool isDelete){
    this->isDelete = isDelete;
}

void InterCode::setIsModified(bool isModified){
    this->isModified = isModified;
}

void InterCode::printCode() {
    cout << "(  " << instructType << "  ,  " << secondElm << "  ,  " << thirdElm << "  ,  " << fourthElm << "  )";
    cout<<" Line "<<line<<endl;
}