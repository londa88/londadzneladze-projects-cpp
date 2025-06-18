/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <cmath>
#include "gwindow.h"
#include "simpio.h"
using namespace std;
void drawSierpinski(float length, int num, GWindow gw, GPoint pt){
	if(num==0){
	    GPoint pt1=gw.drawPolarLine(pt, length, 0);
		GPoint pt2=gw.drawPolarLine(pt1, length, 120);
		GPoint pt3=gw.drawPolarLine(pt2,length,-120);
		return;
	}
	GPoint pt1(pt.getX()+length/4, pt.getY()-length*sqrt(3.0)/4);
	GPoint pt2(pt.getX()+length/2, pt.getY());
	drawSierpinski(length/2, num-1, gw, pt);
	drawSierpinski(length/2, num-1, gw, pt1);
	drawSierpinski(length/2, num-1, gw, pt2);

}
int main() {
	GWindow gw(400,400);
	float triangleLength=getReal("enter triangle length");
	int N=getInteger("enter N:");
	GPoint pt(200-(triangleLength/2),  200+(triangleLength*sqrt(3.0)/6));
	drawSierpinski(triangleLength, N, gw, pt);
  
    return 0; 
}
