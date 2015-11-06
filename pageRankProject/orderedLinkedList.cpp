#include "orderedLinkedList.h"
#include <iostream>
#include <string>

orderedLinkedList::orderedLinkedList(){
	count = 0; 
	head = NULL; 
	tail = NULL; 
}

int orderedLinkedList::length(){ 
	return count; 
}

nodeType* orderedLinkedList::getHead() 
{
	return head; 
}

bool orderedLinkedList::search(std::string searchItem)
{ 
	bool found = false; 
	nodeType *current; //pointer to travel through the list 

	current = head; //start at the first node 

	while(current != NULL && !found) 
		if(current->data == searchItem) 
			found = true; 
		else 
			current = current->next; 
	if (found) 
		found = (current->data == searchItem); //additional test for equality 

	return found; 
}

void orderedLinkedList::insert(std::string newItem) 
{
	nodeType *current; //node to compare newItem with the current nodes 
	nodeType *trailCurrent = NULL; //follows behind the current node 
	nodeType *newNode; //pointer to create a node 

	bool found; 

	newNode = new nodeType; //creates a new node 
	newNode->data = newItem; //stores new item 
	newNode->next = NULL; //set the next field of the node to NULL 

	if(head == NULL) //first node to be created 
	{
		head = newNode; 
		tail = newNode; 
		count++;    //increment to add a node to count 
	}

	else 
	{
		current = head; 
		found = false; 

		while(current != NULL && !found) //searching list 
			if(current->data >= newItem)
				found = true; 
			else 
			{
				trailCurrent = current; 
				current = current->next; 
			}

		if(current == head) 
		{
			newNode->next = head; 
			head = newNode; 
			count++; 
		}
		else
		{
			trailCurrent->next = newNode; 
			newNode->next = current; 

			if(current == NULL) 
				tail = newNode; 

			count++; 
			tail->next = NULL; 
		} 
	}
}

void orderedLinkedList::insertFirst(std::string newItem) 
{
	insert(newItem); 
}

void orderedLinkedList::insertLast(std::string newItem) 
{
	insert(newItem); 
} 

void orderedLinkedList::deleteItem(std::string deleteItem)
{
	nodeType* current; 
	nodeType* trailCurrent = NULL; 
	bool found; 

	if(head == NULL) 
		return; 
	else
	{
		current = head; 
		found = false; 

		while (current != NULL && !found) 
			if(current->data == deleteItem) 
				found = true; 
			else 
			{
				trailCurrent = current; 
				current = current->next; 
			} 

		if (current == NULL) 
			return; 
		else 
			if(current->data == deleteItem) 
			{
				if(head == current) 
				{
					head = head->next; 

					if(head == NULL)
						tail = NULL; 

					delete current; 
				}
				else
				{
					trailCurrent->next = current->next; 

					if(current == tail)
						tail = trailCurrent;

					delete current; 
				}
				count--; 
			}
			else
				return; 
	}
}

void orderedLinkedList::copyList(std::string newArr[], int sizeOfArray)
{
	nodeType* current; 
	current = head; 
	int i = 0; 
	while(current != NULL && i != sizeOfArray) 
	{
		newArr[i] = current->data; 
		current = current->next; 
		i++; 
	}

}

void orderedLinkedList::destroyList()
{
	nodeType *temp; 

	while(head != NULL) 
	{
		temp = head;		//delete head until head = tail, then delete tail
		head = head->next; 
		delete temp; 
	}

	tail = NULL; 
	count = 0; 
}

void orderedLinkedList::print()
{
	nodeType *current = head; 
	while(current != NULL) 
	{
		std::cout << current->data << std::endl; 
		current = current->next; 
	}
	current = NULL; 
	delete current; 
}