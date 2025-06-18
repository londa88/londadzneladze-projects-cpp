/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */


#include <iostream>
#include "console.h"
#include "simpio.h"
#include "lexicon.h"
#include "set.h"
#include "vector.h"
#include "queue.h"
using namespace std;
Vector <char> makeCharList(){
    string s="abcdefghijklmnopqrstuvwxyz";
	Vector <char> charList;
	for(int i=0; i<s.length();i++){
		charList.add(s[i]);
	}
	return charList; 
}
Vector<string> listOfOneCharDifference(string str, Vector<char> charList){
    Vector<string> res;
	string resWord=str;
	for(int i=0; i<str.length();i++){
		for(int j=0; j<charList.size();j++){
			if(str[i]!=charList[j]){
               resWord[i]=charList[j];
			   res.add(resWord);
			}
		}
		resWord=str;
	}
	return res;
}
Set<string> findAllMatches(Lexicon lex, string str){
	Vector<char> charList=makeCharList();
	Vector<string> oneCharDifference=listOfOneCharDifference(str, charList);
	Set<string> setOfMatches;
	for(int i=0;i<oneCharDifference.size();i++){
		if(lex.contains(oneCharDifference[i])){
			setOfMatches.add(oneCharDifference[i]);

		}
		
	}
	return setOfMatches;
}
void showTheLadder(Vector<string> &v){
	string s=v[0];
	for(int i=1;i<v.size();i++){
		s+=" -> "+v[i];
		
	}
	cout<<"Found ladder:"<<s<<endl;

}
bool findTheLadder(Lexicon lex, string startWord,string endWord){
	Vector<string> ladderWords;
	ladderWords.add(startWord);
	Set<string> alreadyUsed;
	alreadyUsed.add(startWord);

	Queue< Vector<string> > ladders;
	ladders.enqueue(ladderWords);
	while(!ladders.isEmpty()){
		Vector<string> newLad=ladders.dequeue();
		if(newLad[newLad.size()-1]==endWord){
			showTheLadder(newLad);
			return true;
		}
		Set<string> allMatches=findAllMatches(lex, newLad[newLad.size()-1]);
		foreach(string newWord in allMatches){
			if(!alreadyUsed.contains(newWord)){
				alreadyUsed.add(newWord);
                Vector<string> newLadder=newLad;
				newLadder.add(newWord);
				ladders.enqueue(newLadder);


			}
		}

		
	}
	return false;
}

int main() {
	Lexicon lex;
	lex.addWordsFromFile("EnglishWords.dat");
	while(true){
		string startWord=getLine("Enter the starting word(or nothing to quit): ");
	if(startWord==""){
		cout<<"Goodbye!"<<endl;
		break;
	}
	string endWord=getLine("Enter the ending word: ");
	cout<<"Searching..."<<endl;
	if(!findTheLadder(lex, startWord, endWord)){
		cout<<"No ladder found"<<endl;
	}
	}
		return 0;
} 