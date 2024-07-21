/* I will try to write an implementation
*  of linked list in C
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>



struct Node {
	int		value;
	struct Node* next;
};

typedef struct {
	int		len;
	struct Node* head;
	struct Node* tail;
} List;



// Main list functions
/*Function for initializing the list.
* It simply assigns NULL value both to head and tail.
*/
List* CreateList();

/*Function for creating a new Node and assingning 
* value to it. (This )
*/
//static struct Node* CreateNode(int value);


void AddValue(List* list, int value);



// Free the list
void FreeListOper(struct Node* node);

void FreeList(List* list);



// Get node by index
struct Node* GetNodeOper(struct Node* node, int index);

struct Node* GetNode(List* list, int index);



// Remove by value
int RemoveNodeByValue(struct Node* node, int value);

void RemoveValue(List* list, int value);



// Remove by index
int RemoveByIndexOper(struct Node* node, int index);

void RemoveByIndex(List* list, int index);



// Operating functions
void ReadListOper(struct Node* node);

int ContainsOper(struct Node* node, int value);

int GetValueByIndexOper(struct Node* node, int index);



// Call functons
void PrintAllValues(List* list);

int Contains(List* list, int value);

int GetValueByIndex(List* list, int index);

#endif