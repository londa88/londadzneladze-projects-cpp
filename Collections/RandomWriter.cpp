/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
*/
 
#include <iostream>
#include "console.h"
#include<fstream>
#include "vector.h"
#include "map.h"
#include "simpio.h"
#include "filelib.h"
#include <string>
#include "random.h"


using namespace std;

	

void createMarkovModel(ifstream &input, int markovNum, Map<string, Vector<char> > &ans){
	char ch;
	string initialText = "";
	for(int i = 0; i < markovNum; i++){
		input.get(ch);
		initialText += ch;
	}
	while(input.get(ch)){
		if(!ans.containsKey(initialText)){
			Vector<char> vect;
			vect.add(ch);
			ans.put(initialText, vect);	
		}else{
			ans[initialText].add(ch);
		}
		initialText=initialText.substr(1);
		initialText+=ch;
	}
	input.close();
}
void findMostFrequentText(Map<string, Vector<char> > &markovModel, string &res){
	int mostFreq=0;
    foreach (string key in markovModel) {
        if (mostFreq < markovModel[key].size()) {
            mostFreq = markovModel[key].size();
            res = key;
        }
    }

}

void generateTheText(Map<string, Vector<char> > &markovModel, string freqT){
	string finalText;
	finalText=freqT;
	int charCount=freqT.length();
	while(charCount<2000){
	   	if(markovModel.containsKey(freqT)){
		int index=randomInteger(0,markovModel[freqT].size()-1);
		char ch=markovModel[freqT].get(index);
		finalText+=ch;
		freqT=freqT.substr(1)+ch;
		charCount++;
		}
	}
     cout<<finalText<<endl;	 
}
void interactWithUser(ifstream& input, int& markovNum){
	string fileName=getLine("Enter the source text:");
	while(!fileExists(fileName.c_str())){
		cout<<"file does not exist, enter valid name" <<endl;
		fileName=getLine();
	}
	input.open(fileName.c_str());
	markovNum=getInteger("Enter the Markov order [1-10]: ");
	while(markovNum>10||markovNum<1){
		cout<<"That value is out of range."<<endl;
		markovNum=getInteger("Enter the Markov order [1-10]: ");
    }
	cout << "Processing File..." << endl;
}
int main() {
	ifstream input;
	int markovNum;
	string mostFreqText;
	Map<string, Vector<char> > markovModel;
	interactWithUser(input, markovNum);
	createMarkovModel(input, markovNum, markovModel);
    findMostFrequentText(markovModel, mostFreqText);
	generateTheText(markovModel,mostFreqText);
	return 0;
}