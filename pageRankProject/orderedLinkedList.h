#pragma once
#include <string> 
struct nodeType { 
	std::string data; 
	nodeType* next; 
}; 

class orderedLinkedList {
public: 
	orderedLinkedList(); 
	void print(); 
	int length(); 
	nodeType* getHead(); 
	bool search(std::string searchItem); 
	void insert(std::string newItem); 
	void insertFirst(std::string newItem); 
	void insertLast(std::string newItem); 
	void deleteItem(std::string deleteItem); 
	void copyList(std::string arr[], int); 
	void destroyList(); 
protected:
	int count; 
	nodeType* head; 
	nodeType* tail; 
}; 

