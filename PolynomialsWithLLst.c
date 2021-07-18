#include <stdio.h>
#include <stdlib.h>
// Summing Polynomials with LinkedList!
typedef float FLOAT;	// just for good looking
typedef struct poly_node {
	int coef;
	int expon;
	struct poly_node * link;
}Node;

typedef struct poly_node * poly_pointer;

poly_pointer a, b, d;

void Attach(int coef, int expon, poly_pointer * ptr) {
	poly_pointer newNode;

	newNode = (poly_pointer)malloc(sizeof(Node));
	newNode->coef = coef;
	newNode->expon = expon;

	newNode->link = NULL;

	(*ptr)->link = newNode;
	*ptr = newNode;
}

int Compare(int a, int b) {
	return (a > b) ? -1 : ((a == b) ? 0 : 1);
}

poly_pointer padd(poly_pointer a, poly_pointer b) {
	poly_pointer front, delDumNode;
	poly_pointer rear = (poly_pointer)malloc(sizeof(Node));

	front = rear;

	while (a && b) {
		switch (Compare(a->expon,b->expon)) {
		case -1:
			Attach(a->coef, a->expon, &rear);
			a = a->link;
			break;
		case 0:
			Attach(a->coef + b->coef, a->expon, &rear);
			a = a->link;
			b = b->link;
			break;
		case 1:
			Attach(b->coef, b->expon, &rear);
			b = b->link;
			break;
		}
	}

	while (a) {
		Attach(a->coef, a->expon, &rear);
		a = a->link;
	}
	while (b) {
		Attach(b->coef, b->expon, &rear);
		b = b->link;
	}

	delDumNode = front;
	front = front->link;
	free(delDumNode);

	return front;
}

void Erase(poly_pointer * ptr) {
	poly_pointer delNode;

	while (*ptr) {
		delNode = *ptr;
		*ptr = (*ptr)->link;
		free(delNode);
	}
}

int main(void) {
	poly_pointer delDumNode, currNode;
	poly_pointer aRear = (poly_pointer)malloc(sizeof(Node));
	poly_pointer bRear = (poly_pointer)malloc(sizeof(Node));
	
	a = aRear;
	b = bRear;

	Attach(3, 10, &aRear);
	Attach(100, 5, &aRear);
	Attach(45, 3, &aRear);
	Attach(5, 0, &aRear);
	Attach(10, 100, &bRear);
	Attach(5, 3, &bRear);
	Attach(5, 0, &bRear);

	delDumNode = a;
	a = a->link;
	free(delDumNode);
	delDumNode = b;
	b = b->link;
	free(delDumNode);

	d = padd(a, b);
	currNode = d;

	while (currNode) {
		printf("%dX^%d\n", currNode->coef, currNode->expon);
		currNode = currNode->link;
	}

	Erase(&d);

	return 0;
}