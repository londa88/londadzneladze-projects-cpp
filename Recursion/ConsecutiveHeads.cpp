/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "random.h"
using namespace std;

int main() {
	int consecutive=0;
	int numOfCounts=0;
	while(true){
		bool isHead=randomChance(0.5);
		numOfCounts++;
		if(isHead){
			cout<< "head" << endl;
			consecutive++;
			if(consecutive==3){
				break;
			}
		}
		else{
			cout<< "tail" <<endl;
			consecutive=0;
		}
	}
	cout<< "it took " << numOfCounts << " flips to get 3 consecutive heads" << endl;


    return 0;
}
