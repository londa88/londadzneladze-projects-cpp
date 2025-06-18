/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"
#include <string>

VectorPriorityQueue::VectorPriorityQueue() {
		
}

VectorPriorityQueue::~VectorPriorityQueue() {

}

int VectorPriorityQueue::size() {
	return pqueue.size();
}

bool VectorPriorityQueue::isEmpty() {
	if(pqueue.size()==0){
		return true;
	}
	return false;
}

void VectorPriorityQueue::enqueue(string value) {
	pqueue.add(value);
}

string VectorPriorityQueue::peek() {
	if(pqueue.size()==0){
		error("queue is empty");  	
	}
	
		string maxVal="";
		for(int i=0; i<pqueue.size(); i++){
			if(maxVal<pqueue[i]){
				maxVal=pqueue[i];
			}
		}
		string minVal=maxVal;
		for(int i=0; i<pqueue.size(); i++){
			if(minVal>pqueue[i]){
                minVal=pqueue[i];
			}
		}
		return minVal;
	
	
}

string VectorPriorityQueue::dequeueMin() {
		if(pqueue.size()==0){
		error("queue is empty");  	
	}
	
		string maxVal="";
		for(int i=0; i<pqueue.size(); i++){
			if(maxVal<pqueue[i]){
				maxVal=pqueue[i];
			}
		}
		string minVal=maxVal;
		int index=0;
		for(int i=0; i<pqueue.size(); i++){
			if(minVal>pqueue[i]){
                minVal=pqueue[i];
				index=i;
			}
		}
		pqueue.remove(index);
		return minVal;
	
	
}