/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

int calculate(int n, int k){
	if(n==0||k==0||k==n){
		return 1;
	}
	return calculate(n-1,k-1)+calculate(n-1,k);

}

int main(){
   cout<< "enter n: " <<endl;
   int n=getInteger();
   cout<< "enter k: " <<endl;
   int k=getInteger();
   while(k>n){
	  cout<< "k should be less than n" <<endl;
      k=getInteger();
   }
   int res=calculate(n,k);
   cout << res << endl;

    return 0;

}
