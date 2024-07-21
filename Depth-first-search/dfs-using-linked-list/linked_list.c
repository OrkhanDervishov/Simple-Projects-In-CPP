#include <stdio.h>
#include <malloc.h>
#include "linked_list.h"


// Main list functions
List* CreateList() {

	List* list = (List*)malloc(sizeof(List));
	list->len = 0;
	list->head = NULL;
	list->tail = NULL;

	return list;
}

static struct Node* CreateNode(int value) {

	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	node->value = value;
	node->next = NULL;

	return node;
}


void AddValue(List* list, int value) {

	if (list->len == 0) {
		struct Node* node = CreateNode(value);
		list->head = node;
		list->tail = node;
	}

	else {
		list->tail->next = CreateNode(value);
		list->tail = list->tail->next;
	}

	list->len++;
}


// Free the list
void FreeListOper(struct Node* node) {

	if (node->next == NULL) {
		free(node);
		return;
	}
	struct Node* temp = node->next;
	free(node);
	FreeListOper(temp);
}

void FreeList(List* list) {

	FreeListOper(list->head);
	free(list);
}



// Get node by index
struct Node* GetNodeOper(struct Node* node, int index) {

	switch (index)
	{
	case 0:
		return node;
	}

	return GetNodeOper(node->next, --index);
}

struct Node* GetNode(List* list, int index) {

	return GetNodeOper(list->head, index);
}



// Remove by value
int RemoveNodeByValue(struct Node* node, int value) {

	if (node->next->value == value) {
		struct Node* temp = node->next;
		node->next = node->next->next;
		free(temp);
		return 1;
	}
	if (node->next == NULL) {
		printf("\nNo such element in the list\n");
		return 0;
	}

	return RemoveNodeByValue(node->next, value);
}

void RemoveValue(List* list, int value) {

	if (list->head->value == value) {

		switch (list->len)
		{
		case 0:
			printf("\nThere is no element in the list");
			return;
		case 1:
			free(list->head);
			--list->len;
			return;
		default:
		{
			struct Node* temp = list->head;
			list->head = list->head->next;
			free(temp);
			--list->len;
			return;
		}
		}
	}
	else if (list->tail->value == value) {
		struct Node* node = GetNode(list, list->len - 2);
		free(list->tail);
		list->tail = node;
		node->next = NULL;

		--list->len;
		return;
	}

	if (RemoveNodeByValue(list->head, value)) --list->len;
}



// Remove by index
int RemoveByIndexOper(struct Node* node, int index) {

	if (index == 1) {
		struct Node* temp = node->next;
		node->next = node->next->next;
		free(temp);
		return 1;
	}
	if (node->next->next == NULL) {
		printf("\nNo such element in the list\n");
		return 0;
	}

	return RemoveByIndexOper(node->next, --index);
}

void RemoveByIndex(List* list, int index) {

	if (index == 0) {

		switch (list->len)
		{
		case 0:
			printf("\nThere is no element in the list");
			return;
		case 1:
			free(list->head);
			--list->len;
			return;
		default:
		{
			struct Node* temp = list->head;
			list->head = list->head->next;
			free(temp);
			--list->len;
			return;
		}
		}
	}
	else if (index == list->len - 1) {
		struct Node* node = GetNode(list, index - 1);
		free(list->tail);
		list->tail = node;
		node->next = NULL;

		--list->len;
		return;
	}

	if (RemoveByIndexOper(list->head, index)) --list->len;
}







// Operating functions
void ReadListOper(struct Node* node) {
	printf("%d, ", node->value);
	if (node->next == NULL) return;
	ReadListOper(node->next);
}

int ContainsOper(struct Node* node, int value) {

	if (node->value == value) return 1;
	if (node->next == NULL) return 0;

	return ContainsOper(node->next, value);
}

int GetValueByIndexOper(struct Node* node, int index) {

	if (index == 0) return node->value;
	if (node->next == NULL) {
		printf("\nNo such element in the list\n");
		return 0;
	}

	return GetValueByIndexOper(node->next, --index);
}



// Call functons
void PrintAllValues(List* list) {

	printf("\n");
	ReadListOper(list->head);
}

int Contains(List* list, int value) {

	return ContainsOper(list->head, value);
}

int GetValueByIndex(List* list, int index) {

	return GetValueByIndexOper(list->head, index);
}