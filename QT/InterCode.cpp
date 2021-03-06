#include "InterCode.h"


InterCode::InterCode(string instructType, string secondElm, string thirdElm, string fourthElm)
{
	this->instructType = instructType;
	this->secondElm = secondElm;
	this->thirdElm = thirdElm;
	this->fourthElm = fourthElm;
}

InterCode::InterCode(string instructType, string secondElm, string thirdElm, string fourthElm, int line){
    this->instructType = instructType;
    this->secondElm = secondElm;
    this->thirdElm = thirdElm;
    this->fourthElm = fourthElm;
    this->line = line;
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

void InterCode::printCode() {
    string second = secondElm==""?"NULL":secondElm;
    string third = thirdElm==""?"NULL":thirdElm;
    string fourth = fourthElm==""?"NULL":fourthElm;
    cout << "(  " << instructType << "  ,  " << secondElm << "  ,  " << third << "  ,  " << fourth << "  )";
    cout<<" Line "<<line<<endl;
}
