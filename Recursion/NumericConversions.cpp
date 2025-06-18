/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function prototypes */

string intToString(int n){
	string s="";
	if(n==0){
		return s+'0';
	}
	if(n<10&&n>0){
		return s+char(n+'0');
	}
	if(n==-2147483648){
		return "-2147483648";
	}
	if(n<0){
		return "-"+intToString(n*(-1));
	}
	return intToString(n/10)+(char(n%10+'0'));
}
int stringToInt(string str){
	if(str.length()==0){
		return 0;
	}
	if(str[0]=='-'){
		return (-1)*stringToInt(str.substr(1));
	}
	return stringToInt(str.substr(0, str.length()-1))*10+(str[str.length()-1]-'0');
}


int main() {
	int n=getInteger("enter n:");
	cout << "Integer to string:" << intToString(n) << endl;
	string s=getLine("enter string");
	cout<< "string to integer: " <<stringToInt(s) <<endl;
    return 0;
}
