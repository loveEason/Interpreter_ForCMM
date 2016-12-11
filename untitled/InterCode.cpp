#include "InterCode.h"


InterCode::InterCode(string instructType, string secondElm, string thirdElm, string fourthElm)
{
	this->instructType = instructType;
	this->secondElm = secondElm;
	this->thirdElm = thirdElm;
	this->fourthElm = fourthElm;
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
    string third = thirdElm==""?"NULL":thirdElm;
    string fourth = fourthElm==""?"NULL":fourthElm;
    cout << "(  " << instructType << "  ,  " << secondElm << "  ,  " << third << "  ,  " << fourth << "  )" << endl;
}
