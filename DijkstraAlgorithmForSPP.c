#include <stdio.h>
#include <stdlib.h>
// Chapter06. Shortest Paths - Dijkstra's Algorithm
#define MAX_VERTICES		1000
#define TRUE				1
#define FALSE				0
#define INF					1000

void shortestPath(int v, int cost[][6], int distance[], int n, short int found[]) {
	int i, u, w;
	for (i = 0; i < n; i++) {
		found[i] = FALSE;		
		distance[i] = cost[v][i];	
	}
	found[v] = TRUE;
	distance[v] = 0;	
	for (i = 0; i < n - 2; i++) {	
		u = choose(distance, n, found); 
		found[u] = TRUE;		
		for (w = 0; w < n; w++) {	
			if (!found[w]) {
				if (distance[u] + cost[u][w] < distance[w])
					distance[w] = distance[u] + cost[u][w];
			}
		}
	}
}



int choose(int distance[], int n, short int found[]) {
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++) {
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}

int main(void) {
	int cost[6][6] = {
		0,2,4,INF,INF,INF,
		INF,0,1,7,INF,INF,
		INF,INF,0,INF,3,INF,
		INF,INF,INF,0,INF,1,
		INF,INF,INF,2,0,5,
		INF,INF,INF,INF,INF,0
	};
	int distance[6] = { INF,INF,INF,INF,INF,INF };
	short int found[6];

	shortestPath(0, cost, distance, 6, found);

	for (int i = 0; i < 6; i++)
		printf("[%d]:%d   ", i, distance[i]);

	return 0;
}