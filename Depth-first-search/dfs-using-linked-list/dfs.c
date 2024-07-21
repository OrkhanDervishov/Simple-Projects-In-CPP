/*In this program I am trying to implement
* Depth Fist Search algorithm
*/

#include <stdio.h>
#include <malloc.h>
#include "linked_list.h"

#define nodes 15

int contains(int* arr, int value) {

	for (int i = 0; i < nodes; i++) {
		if (arr[i] == value) return 1;
		if (arr[i] == -1) return 0;
	}

	return 0;
}

void dfs(struct List** edges, int* visited, int at) {
	visited[at] = 1;
	printf("move %d\n", at);

	for (int i = 0; i < nodes; i++) {
		if (visited[i] == 0 && Contains(edges[at], i)) {
			dfs(edges, visited, i);
			printf("return %d\n", at);
		}
	}
}


int main() {

	int visited[nodes];

	for (int i = 0; i < nodes; i++) {
		visited[i] = 0;
	}


	struct List** edges = (struct List**)malloc(sizeof(struct List*) * nodes);

	for (int i = 0; i < nodes; i++) {
		edges[i] = CreateList();
	}
	int edges_copy[nodes][nodes + 1] =
		{
			{1, 11, -1},
			{0, 1, 2, 10, -1},
			{1, 3, 9, -1},
			{2, 4, 14, -1},
			{3, 5, 14, -1},
			{4, 6, 7, -1},
			{5, -1},
			{5, 8, -1},
			{7, 9, 10, 12, 13, -1},
			{2, 8, -1},
			{1, 8, 12, -1},
			{0, 12, -1},
			{8, 10, 11, -1},
			{8, 14, -1},
			{3, 4, 13, -1},
		};

	for (int i = 0; i < nodes; i++) {
		for (int j = 0; edges_copy[i][j] != -1; j++) {
			AddValue(edges[i], edges_copy[i][j]);
		}
	}

	dfs(edges, visited, 1);
	
	for (int i = 0; i < nodes; i++) {
		FreeList(edges[i]);
	}
	free(edges);
}