#include <stdio.h>
#include <stdlib.h>
// Chapter06. Elementary Graph Operations : DFS, BFS
#define MAX_ELEMENT	1000
#define TRUE		1
#define FALSE		0

struct node {
	int vertex;
	struct node * link;
};
typedef struct node * nodePointer;

nodePointer graph[MAX_ELEMENT];
int visited[MAX_ELEMENT];
nodePointer front, rear;

int queue[MAX_ELEMENT];
int Hfront, Hrear;

int edges[8][8] = {
		0, 1, 1, 0, 0, 0, 0, 0,
		1, 0, 0, 1, 1, 0, 0, 0,
		1, 0, 0, 0, 0, 1, 1, 0,
		0, 1, 0, 0, 0, 0, 0, 1,
		0, 1, 0, 0, 0, 0, 0, 1,
		0, 0, 1, 0, 0, 0, 0, 1,
		0, 0, 1, 0, 0, 0, 0, 1,
		0, 0, 0, 1, 1, 1, 1, 0
};

void addq(int v) {
	nodePointer newNode = (nodePointer)malloc(sizeof(struct node));
	newNode->vertex = v;
	newNode->link = NULL;
	if (!front) {
		newNode->link = front;
		front = newNode;
		rear = newNode;
	}
	else {
		newNode->link = rear->link;
		rear->link = newNode;
		rear = newNode;
	}
}

int deleteq(void) {
	int returnvalue;
	nodePointer delNode = front;

	front = front->link;
	returnvalue = delNode->vertex;
	free(delNode);
	return returnvalue;
}

void Haddq(int v) {
	queue[Hrear++] = v;
}

int Hdeleteq(void) {
	return queue[Hfront++];
}

void dfs(int v) {
	nodePointer w;
	visited[v] = TRUE;		// visited[] is a global variable
	printf("%5d", v);		// ��� ����
	for (w = graph[v]; w; w = w->link) {
		if (!visited[w->vertex])
			dfs(w->vertex);
	}
}

void Hdfs(int v) {
	int i;

	visited[v] = TRUE;
	printf("%5d", v);
	for (i = 0; i < 8;i++) {
		if (edges[v][i] && !visited[i]) {
			Hdfs(i);
		}
	}
}

void bfs(int v) {
	nodePointer w;
	front = rear = NULL; 	/* initialize queue */
	printf("%5d", v);
	visited[v] = TRUE;
	addq(v);
	while (front) {			// ť�� �� ������ ������ ���ٴ� �ǹ�
		v = deleteq();	// ť�� �Ӹ��� �ִ� ������ Dequeue���ְ�,
		for (w = graph[v]; w; w = w->link) {	// �ش� ������ �̿� �������� ��ȸ�ϴµ�,
			if (!visited[w->vertex]) {	// �� �� Unvisited�� ��������
				printf("%5d", w->vertex);	// ���ÿ� ��ȸ�ϰ�,
				addq(w->vertex);		// ��ȸ�� �̷������ ť�� ����
				visited[w->vertex] = TRUE;	// Visit������ ǥ��
			}
		}
	}
}

void Hbfs(int v) {
	int i;

	printf("%5d", v);
	visited[v] = TRUE;
	Haddq(v);
	while (Hfront != Hrear) {
		v = Hdeleteq();
		for (i = 0; i < 8; i++) {
			if (edges[v][i] && !visited[i]) {
				printf("%5d", i);
				Haddq(i);
				visited[i] = TRUE;
			}
		}
	}
}

void InsertLinked(nodePointer *graph, int v) {
	nodePointer newNode = (nodePointer)malloc(sizeof(struct node));
	newNode->vertex = v;
	newNode->link = *graph;
	*graph = newNode;
}

int main(void) {
	InsertLinked(&graph[0], 2); InsertLinked(&graph[0], 1);
	InsertLinked(&graph[1], 4); InsertLinked(&graph[1], 3); 
	InsertLinked(&graph[1], 0);
	InsertLinked(&graph[2], 6); InsertLinked(&graph[2], 5); 
	InsertLinked(&graph[2], 0);
	InsertLinked(&graph[3], 7); InsertLinked(&graph[3], 1);
	InsertLinked(&graph[4], 7); InsertLinked(&graph[4], 1);
	InsertLinked(&graph[5], 7); InsertLinked(&graph[5], 2);
	InsertLinked(&graph[6], 7); InsertLinked(&graph[6], 2);
	InsertLinked(&graph[7], 6); InsertLinked(&graph[7], 5);
	InsertLinked(&graph[7], 4); InsertLinked(&graph[7], 3);

	dfs(0); 
	printf("\n");
	for (int i = 0; i < 8; i++)
		visited[i] = FALSE;
	bfs(0);							// ��������Ʈ

	/*
	Hdfs(0);
	printf("\n");
	for (int i = 0; i < 8; i++)
		visited[i] = FALSE;
	Hbfs(0);*/						// �������

	return 0;
}