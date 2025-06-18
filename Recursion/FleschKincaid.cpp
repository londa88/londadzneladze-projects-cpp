/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */


#include <fstream>
#include <iostream>
#include "console.h"
#include "tokenscanner.h"
#include "filelib.h"
#include "simpio.h"
using namespace std;
const double C0 =-15.59;
const double C1 = 0.39;
const double C2 = 11.8;
int countSyllable(string nextToken){
	string word=toLowerCase(nextToken);
	int syllableCount=0;
	for(int i=0; i<(word.length()-1); i++){
		if((word[i]=='a'||word[i]=='e'||word[i]=='i'||word[i]=='o'||word[i]=='u'||word[i]=='y')&&(word[i+1]!='a'&&word[i+1]!='e'&&word[i+1]!='i'&&word[i+1]!='o'&&word[i+1]!='u'&&word[i+1]!='y')){
			syllableCount++;
		}
	}
	if(word.length()>=2){
	if(word[word.length()-2]=='a'||word[word.length()-2]=='e'||word[word.length()-2]=='i'||word[word.length()-2]=='o'||word[word.length()-2]=='u'||word[word.length()-2]=='y'){
		if(word[word.length()-1]=='e'){
			syllableCount++;
		}
	}
	}
	if(word[word.length()-1]=='a'||word[word.length()-1]=='i'||word[word.length()-1]=='o'||word[word.length()-1]=='u'||word[word.length()-1]=='y'){
		syllableCount++;
	}
	if(syllableCount==0){
		syllableCount=1;
	}
	return syllableCount;
}
bool isWord(string nextTok){
	if(isalpha(nextTok[0])){
		return true;
	}
	return false;
}
bool isSentence(string nextTok){
	if(nextTok=="."||nextTok=="!"||nextTok=="?"){
		return true;
	}
	return false;
}

int main() {
	ifstream input;
	string fileName=getLine("write file name: ");
	while(!fileExists(fileName.c_str())){
		cout<<"file does not exist, enter valid name" <<endl;
		fileName=getLine();

	}
	input.open(fileName.c_str());
	TokenScanner tok(input);
	tok.ignoreWhitespace();
	tok.addWordCharacters("'");
	int wordCount=0;
	int sentenceCount=0;
	int syllableCount=0;
	while(tok.hasMoreTokens()){
		string nextTok=tok.nextToken();
		if(isWord(nextTok)){
			int syllableInTok=countSyllable(nextTok);
			wordCount++;
			syllableCount+=syllableInTok;
		}
		if(isSentence(nextTok)){
			sentenceCount++;
		}

	}
	if(wordCount==0){
		wordCount=1;
	}
	if(sentenceCount==0){
		sentenceCount=1;
	}
	double Grade=C0+C1*((double)wordCount/sentenceCount)+C2*((double)syllableCount/wordCount);
	cout<<"Words: "<<wordCount<<endl;
	cout<<"sentences: "<<sentenceCount<<endl;
	cout<<"syllables: "<<syllableCount<<endl;
    
	cout<< Grade << endl;
    return 0;
}

