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
	for (v = 0; v < n; v++) { // ������ ������ ��� ���� �迭���� �ʱ�ȭ
		st[v] = -1;			// start, �� �ҽ��� �ǹ�
		fr[v] = v;			// for, �� �������� �ǹ�
		wt[v] = maxWT;		// cost�� 1000���� �ʱ�ȭ
	}
	wt[n] = maxWT;
	for (min = 0; min != n; ) {
		v = min;			// ���� ������ 0����. ���� �ܰ���ʹ� ���� �߰� ������ �ǹ�
		st[min] = fr[min];	// �� �ܰ��� MST���� ������ ������ �� �ּ� ������ ����
							// �� �����Ͽ� Ʈ���� Ȯ���Ѵ�.(�ҽ� �迭 Ȯ��)
		for (w = 0, min = n; w < n; w++) // v�� ������ �������� ���� costȮ��
			if (st[w] == -1) { // ���� ����� �� ���� �����϶�(����Ŭ ����)
				if (G->adj[v][w] < wt[w]) {	// ������ �߷��� wt�� ������Ʈ�Ϸ��� ��
					wt[w] = G->adj[v][w]; // �߷��� wt�迭�� ������Ʈ
					fr[w] = v;			  // (v, w)�̹Ƿ� w�� for�� v��.
				}						// �߷��� ����Ű�� ����. ���� �ܰ��.
				if (wt[w] < wt[min]) // wt[n]�ʱ���´� 1000�̹Ƿ� min�� �ڵ�������.
					min = w;		// �ּ� ������ dest�� min�� ����Ų��.(�߰�)
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