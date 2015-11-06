#include <iostream> 
#include <fstream> 
#include <string> 
#include "orderedLinkedList.h"

using namespace std; 

class dictionaryHash { 
private: 
	int length; 
	static const int HTSize = 100;

	struct item
	{ 
		string word; 
		item* next; 
	}; 

	item* HashTable[HTSize]; 
public: 
	dictionaryHash(); 
	int Hash(string key);
	int returnIndex(string key); 
	void addItem(string name);
	void addEdge(string name, int element); 
	int itemCountInIndex(int index);   
}; 

dictionaryHash::dictionaryHash()
{
	for(int i = 0; i < HTSize; i++) 
	{
		HashTable[i] = new item; 
		HashTable[i]->word = ""; 
		HashTable[i]->next = NULL; 
	}
}

int dictionaryHash::Hash(string key) 
{
	int hash = 0; 
	int index; 

	index = key.length(); 

	for(size_t i = 0; i < key.length(); i++)
	    hash = hash + (int)key[i];
	
	index = hash % HTSize; 
	return index; 
}

int dictionaryHash::returnIndex(string key) 
{
	int hash = 0; 
	int index; 

	index = key.length(); 

	for(size_t i = 0; i < key.length(); i++)
	    hash = hash + (int)key[i];
	
	index = hash % HTSize; 

	while(index != 100) 
	{
		if(HashTable[index]->word != key)
			index++; 
		else
			return index; 
	}

}

void dictionaryHash::addItem(string name)
{
	int index = Hash(name); 

	if(HashTable[index]->word == name) //if this element already exist 
		return; 

	while(index != 100)
	{
		if(HashTable[index]->word == "") //if this element is empty 
		{
			HashTable[index]->word = name; 
			break; 
		}
		else
		{
			index++; 
			if(index == 100)
				index = 0; 
		}
	}
}

void dictionaryHash::addEdge(string name, int element) 
{
	item* current = HashTable[element]; 
	while(current != NULL) 
	{
		if(current->word == name) //if this is already here 
			return; 
		current = current->next; 
	}
	
	current = NULL; 
	delete current; 

	item* ptr = HashTable[element]; 
	item* n = new item; 
	n->word = name; 
	n->next = NULL; 

	while(ptr->next != NULL) 
	{
		ptr = ptr->next; 
	}
	ptr->next = n; 
}


int dictionaryHash::itemCountInIndex(int index)
{
	int count = 0; 

	if(HashTable[index]->word == "") //nothing is there
	{
		return count; 
	}
	else
	{
		count++; 
		item* ptr = HashTable[index]; 
		while(ptr->next != NULL) 
		{
			count++; 
			ptr = ptr->next; 
		}
		return count; 
		ptr = NULL; 
		delete ptr; 
	} 
}

void deleteDuplicates(string arr[], int &size);

int main(int argc, char *argv[])
{
	string commands = ""; 
	int count = 0; 
	orderedLinkedList webpageList; 
	orderedLinkedList mostReferenced; 
	orderedLinkedList brokenLink; 
	orderedLinkedList sink; 
	dictionaryHash webHash; 

	if (argc != 2) //program should have two arguments 
	{
		system("pause"); 
		cout << "wrong number of arguments" << endl; 
		return -1;
	}

	char *filename = argv[1]; 
	ifstream read(filename); 

	if(read.fail()) //testing if the file opened successfully  
		exit(0); 

	while(read >> commands)
		webpageList.insert(commands); 

	nodeType *current = webpageList.getHead(); 

	while(current != NULL) //add items to the graph 
	{
		webHash.addItem(current->data); 
		current = current->next; 
	}

	current = webpageList.getHead(); 
	while(current != NULL) 
	{
		string webpages = ""; 
		ifstream readObj(current->data); 

		if(readObj.fail()) //testing if the file opened successfully  
			exit(0); 

		size_t found; 
		string html = ".html"; 

		while(readObj >> webpages) 
		{
			found = webpages.find(html); 
			if(found != std::string::npos)
			{
				int stringLength = webpages.length(); 

				for(int i = 0; i < stringLength && webpages[i] != '\0'; i++)
				{
					if(webpages[i] == 34 || webpages[i] == '>')
					{
						webpages.erase(i, 1); 
						stringLength--; 
						i--; 
					}
				}

				if(webpageList.search(webpages) == false)
				{
					brokenLink.insert(webpages); 
					continue; 
				}

				webHash.addEdge(webpages, webHash.returnIndex(current->data)); 
				mostReferenced.insert(webpages); 
				count++; 
			}
		}
		if(count == 0) 
		{
			sink.insert(current->data); 
			count = 0; 
			readObj.close(); 
		}
		if(!readObj.good())
		{
			current = current->next;
			count = 0; 
			readObj.close(); 
		}

	}//printing  
		nodeType *ptr = mostReferenced.getHead(); 
		nodeType *ptr2 = mostReferenced.getHead();
		int counter = 0; 
		int mostReferencedCount = 0; 
		string mostReferencedPage = ""; 

		while(ptr != NULL) 
		{
			if(ptr->data == ptr2->data) 
			{
				counter++; 
				if(counter > mostReferencedCount)
				{
					mostReferencedCount = counter; 
					mostReferencedPage = ptr->data; 
				}
			}
			ptr2 = ptr2->next; 
			if(ptr2 == NULL) 
			{
				ptr = ptr->next; 
				ptr2 = mostReferenced.getHead(); 
				counter = 0; 
			}
		}

		if(mostReferencedCount > 0) 
			cout << mostReferencedPage << endl << endl; 
		
		ptr = brokenLink.getHead(); 
		string *printArray1 = new string[brokenLink.length()]; 
		int arrayLength1 = 0; 
		while(ptr != NULL)
		{
			printArray1[arrayLength1] = ptr->data; 
			ptr = ptr->next;
			arrayLength1++; 
		}
		deleteDuplicates(printArray1, arrayLength1); 

		for(int i = 0; i < arrayLength1; i++)
		{
			if(printArray1[i] == "") 
				continue; 
			cout << printArray1[i] <<  " " << "Broken Link" << endl; 
		}

		cout << endl; 
		ptr = sink.getHead();
		string *printArray = new string[sink.length()]; 
		int arrayLength = 0; 
		while(ptr != NULL)
		{
			printArray[arrayLength] = ptr->data; 
			ptr = ptr->next;
			arrayLength++; 
		}
		deleteDuplicates(printArray, arrayLength); 

		for(int i = 0; i < arrayLength; i++)
		{
			if(printArray[i] == "") 
				continue; 
			cout << printArray[i] << " " << "Sink" << endl; 
		}

		ptr = NULL; 
		delete ptr; 
		ptr2 = NULL; 
		delete ptr2; 
		delete []printArray; 
		delete []printArray1; 
		read.close(); 
		mostReferenced.destroyList(); 
		webpageList.destroyList(); 
		brokenLink.destroyList(); 
		sink.destroyList(); 
	
		system("pause"); 
		return 0; 
}

void deleteDuplicates(string arr[], int &size)
{
	for(int i = 0; i < size; i++) 
	{
		for(int j = i+1; j < size; j++) 
		{
			if(arr[i] == arr[j]) 
			{
				for(int k = j; k < size-1; k++)
					arr[k] = arr[k+1]; 
				arr[size-1] = ""; 
				size--; 
			}
			else 
				continue; 
		}
	}
}
