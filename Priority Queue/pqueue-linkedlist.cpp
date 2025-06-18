/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	linkPQ=new Cell;
	linkPQ->next=NULL;
	sizeOfPQ=0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	Cell* temp;
	while(linkPQ!=NULL){
		temp=linkPQ;
		linkPQ=linkPQ->next;
		delete temp;
	}	
}

int LinkedListPriorityQueue::size() {
	return sizeOfPQ;
	
}

bool LinkedListPriorityQueue::isEmpty() {
	if(sizeOfPQ==0){
		return true;
	}
	return false;
}

void LinkedListPriorityQueue::enqueue(string value) {
	sizeOfPQ++;
	if(linkPQ==NULL){
		Cell* newCell=new Cell;
		newCell->value=value;
		newCell->next=NULL;
		linkPQ=newCell;
		return;
	}
	
	Cell* temp=linkPQ;
	while(temp->next!=NULL){
		if(temp->next->value>value){
			Cell* newCell= new Cell;
	        newCell->value=value;
	        newCell->next=temp->next;
			temp->next=newCell;
			return;
		}		
			temp=temp->next;		
	}
	Cell* newCell = new Cell;
    newCell->value = value;
    newCell->next = NULL;
    temp->next = newCell;

}

string LinkedListPriorityQueue::peek() {
	if(sizeOfPQ==0){
		error("queue is empty");
	}
	return linkPQ->next->value;
	
}

string LinkedListPriorityQueue::dequeueMin() {
		if(sizeOfPQ==0){
		error("queue is empty");
	}
     
	 Cell* newCell=linkPQ->next;
	 linkPQ->next=newCell->next;
	 string  res=newCell->value;
	 delete newCell;
	 sizeOfPQ--;
	 return res;	
}