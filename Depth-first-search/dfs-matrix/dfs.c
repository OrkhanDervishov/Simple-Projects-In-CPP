/*In this program I am trying to implement
* Depth Fist Search algorithm in C
*/

#include <stdio.h>
#include <malloc.h>

#define nodes 8


void dfs(int** edges, int* visited, int at) {
	visited[at] = 1;
	printf("move %d\n", at);

	for (int i = 0; i < nodes; i++) {
		if (visited[i] == 0 && edges[at][i] == 1) {
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


	int** edges = (int**)malloc(sizeof(int*) * nodes);

	for (int i = 0; i < nodes; i++) {
		edges[i] = (int*)malloc(sizeof(int) * nodes);
	}

	int edges_copy[nodes][nodes] =
	{
		{0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 1, 0, 0, 0, 0, 1},
		{0, 1, 0, 1, 0, 0, 0, 1},
		{0, 0, 1, 0, 1, 0, 0, 0},
		{0, 0, 0, 1, 0, 1, 0, 1},
		{0, 0, 0, 0, 1, 0, 1, 1},
		{1, 0, 0, 0, 0, 1, 0, 1},
		{1, 1, 1, 0, 1, 1, 1, 1},
	};

	for (int i = 0; i < nodes; i++) {
		for (int j = 0; j < nodes; j++) {
			edges[i][j] = edges_copy[i][j];
		}
	}

	dfs(edges, visited, 1);

	for (int i = 0; i < nodes; i++) {
		free(edges[i]);
	}
	free(edges);
}