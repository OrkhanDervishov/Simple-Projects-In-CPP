/* I try to recreate binary tree data structure
*  int C which will store integers.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include "binary_tree.h"



// Main functions
struct Node* CreateNode(int newValue) {

	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	node->value = newValue;
	node->rightNode = NULL;
	node->leftNode = NULL;
	return node;
}


void AddValue(int value, struct Node* parent) {

	if (value >= parent->value) {

		if (parent->rightNode == NULL) {
			parent->rightNode = CreateNode(value);
			return;
		}

		AddValue(value, parent->rightNode);
		return;
	}

	else {

		if (parent->leftNode == NULL) {
			parent->leftNode = CreateNode(value);
			return;
		}

		AddValue(value, parent->leftNode);
		return;
	}
}




// Other functionalities
int Contains(struct Node* node, int value) {

	if (node->value == value) return 1;
	if (node->value > value && node->leftNode == NULL) return 0;
	if (node->value <= value && node->rightNode == NULL) return 0;

	if (node->value > value) return Contains(node->leftNode, value);
	if (node->value <= value) return Contains(node->rightNode, value);
}