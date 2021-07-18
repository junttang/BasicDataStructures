#include <stdio.h>
#include <stdlib.h>
// Singly Linked List
typedef struct listNode {
	int data;
	struct listNode * link;
}Node;

typedef struct {
	Node* first;
	int numOfData;
}LinkedList;

typedef LinkedList List;

void InitList(List* pList) {
	pList->first = NULL;
	pList->numOfData = 0;
}

int LIsEmpty(List *pList) {
	if (pList->numOfData == 0)
		return 1;
	return 0;
}

void LInsert(List* pList, int insert) {
	Node* currNode = pList->first;
	Node* prevNode = NULL;
	Node* newNode;

	while (currNode) {
		if (currNode->data > insert)
			break;
		prevNode = currNode;
		currNode = currNode->link;
	}

	newNode = (Node*)malloc(sizeof(Node));
	newNode->data = insert;
	newNode->link = currNode;
	if (pList->first == NULL || prevNode == NULL)
		pList->first = newNode;
	else
		prevNode->link = newNode;

	(pList->numOfData)++;
}

Node LRemove(List* pList) {
	Node* delNode = pList->first;

	if (LIsEmpty(pList)) {
		printf("The List is Empty!\n");
		return;
	}

	pList->first = pList->first->link;
	free(delNode);
	
	(pList->numOfData)--;
}

void PrintList(List*pList) {
	Node*currNode = pList->first;

	while (currNode) {
		printf("%d ", currNode->data);
		currNode = currNode->link;
	}
	printf("\n");
}

int main(void) {
	List list;

	InitList(&list);

	while (1) {
		int opt;
		printf("Option: "); scanf("%d", &opt);
		if (opt == 1) {
			int n;
			printf("Insert the data: "); scanf("%d", &n);
			LInsert(&list, n);
		}
		else
			LRemove(&list);
		PrintList(&list);
	}
	return 0;
}