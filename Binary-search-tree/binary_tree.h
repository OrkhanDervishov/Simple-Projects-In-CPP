/* I tried to recreate binary tree data structure
*  in C which stores integers.
*/

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

struct Node {
	int				value;
	struct Node*	rightNode;
	struct Node*	leftNode;
};


struct Node* CreateNode(int newValue);

void AddValue(int value, struct Node* parent);

int Contains(struct Node* node, int value);

#endif