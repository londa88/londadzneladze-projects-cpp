/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	head = new Cell;
    tail = new Cell;
    head -> next = tail;
    head -> prev = NULL;
    tail -> prev = head;
    tail -> next = NULL;
	sizeOfPQ=0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	Cell* curr = head;
      while (curr != NULL) {
      Cell* tmp = curr;
      curr = curr -> next;
      delete tmp;
}
	
}

int DoublyLinkedListPriorityQueue::size() {
	
	return sizeOfPQ;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	if(sizeOfPQ==0){
		return true;
	}
	
	return false;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	
		Cell* newCell = new Cell;
        newCell -> val = value;
        newCell -> next = tail;
        newCell -> prev = tail -> prev;
        tail -> prev = newCell;
        newCell -> prev -> next = newCell;
        sizeOfPQ++;
	
}

string DoublyLinkedListPriorityQueue::peek() {
	if(isEmpty()){
		error("queue is not  empty");
	}
	
		string maxVal="";
		Cell* temp=head;
		while(temp!=NULL){
			if(temp->val>maxVal){
				maxVal=temp->val;
			}
			temp=temp->next;
		}
	  string minVal=maxVal;
	  Cell* newTemp=head;
	  while(newTemp!=NULL){
			if(newTemp->val<minVal){
				minVal=newTemp->val;
			}
			newTemp=newTemp->next;
		}
	  return minVal;
	
	
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if(isEmpty()){
		error("queue is not empty");
	}
      string minVal=peek();
	  Cell* temp=head;
	  while(temp->val!=minVal){
		  temp=temp->next;

	  }
	  temp=head->next;
      head -> next = temp -> next;
      temp -> next -> prev = head;
      
         delete temp;

	  sizeOfPQ--;
	  return minVal;	
	
}

