#include<stdio.h>
#include<stdlib.h>
// Chapter06. Minimum Spanning Trees - Prim's Algorithm
static double maxWT = 1000.00;
static int* fr, *st;
static double *wt;

struct graph { 
	int V, E; 
	double **adj; 
};
typedef struct graph * Graph;

struct edge { 
	int v, w; 
	double wt; 
};
struct edge EDGE(int v, int w, double wt) {
	struct edge e; 
	e.v = v; 
	e.w = w; 
	e.wt = wt;

	return e;
}

double **MARTXint(int r, int c, double wt) {
	int i, j;
	double **t = (double**)malloc(r * sizeof(double*));

	for (i = 0; i < r; i++)
		t[i] = (double*)malloc(c * sizeof(double));
	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++)
			t[i][j] = wt;
	}

	return t;
}

Graph graphinit(int V) {
	Graph g = (Graph)malloc(sizeof(struct graph));

	g->V = V;
	g->E = 0;
	g->adj = MARTXint(V, V, maxWT);

	return g;
}

void graphinsert(Graph g, struct edge e) {
	int v = e.v, w = e.w;

	if (g->adj[v][w] == maxWT) 
		g->E++;

	g->adj[v][w] = g->adj[w][v] = e.wt;
}

void graphshow(Graph g) {
	int i, j;

	for (i = 0; i < g->V; i++) {
		printf("%2d :", i);

		for (j = 0; j < g->V; j++) {
			if (g->adj[i][j] == maxWT)
				printf("*  ");
			else
				("%.2lf ", g->adj[i][j]);
		}
		printf("\n");
	}
}

void GRAPHmstV(Graph G, int st[], double wt[]) {
	int v, w, min, n = G->V;
	for (v = 0; v < n; v++) { // 간선의 정보를 담기 위한 배열들을 초기화
		st[v] = -1;			// start, 즉 소스를 의미
		fr[v] = v;			// for, 즉 목적지를 의미
		wt[v] = maxWT;		// cost를 1000으로 초기화
	}
	wt[n] = maxWT;
	for (min = 0; min != n; ) {
		v = min;			// 시작 정점은 0부터. 다음 단계부터는 이전 추가 정점을 의미
		st[min] = fr[min];	// 앞 단계의 MST에서 인접한 정점들 중 최소 간선의 정점
							// 을 선택하여 트리를 확장한다.(소스 배열 확장)
		for (w = 0, min = n; w < n; w++) // v의 인접한 정점들의 간선 cost확인
			if (st[w] == -1) { // 아직 사용한 적 없는 정점일때(싸이클 방지)
				if (G->adj[v][w] < wt[w]) {	// 간선의 중량을 wt에 업데이트하려는 것
					wt[w] = G->adj[v][w]; // 중량을 wt배열에 업데이트
					fr[w] = v;			  // (v, w)이므로 w의 for은 v임.
				}						// 중량을 기억시키는 것임. 다음 단계로.
				if (wt[w] < wt[min]) // wt[n]초기상태는 1000이므로 min이 자동결정됨.
					min = w;		// 최소 간선인 dest를 min에 기억시킨다.(추가)
			}
	}
}
	/*
	7
	0 1 28
	0 5 10
	1 2 16	
	1 6 14
	2 3 12
	3 4 22
	3 6 18
	4 5 25
	4 6 24
	-1 -1 -1
	*/
int main(void) {
	int v, i, j;
	double Wt;

	scanf("%d", &v);
	Graph G = graphinit(v);
	st = (int *)malloc(G->V * sizeof(int));
	fr = (int *)malloc(G->V * sizeof(int));
	wt = (double *)malloc((G->V + 1) * sizeof(double));

	while (scanf("%d%d%lf", &i, &j, &Wt) && i != -1 && j != -1)
		graphinsert(G, EDGE(i, j, Wt));

	graphshow(G);

	GRAPHmstV(G, st, wt);
	printf("  ");

	for (i = 0; i < G->V; i++)
		printf("%2d ", i);
	printf("\n");
	printf("st");
	for (i = 0; i < G->V; i++)
		printf("%2d ", st[i]);
	printf("\n");

	return 0;
}