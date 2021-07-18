#include <stdio.h>
#include <stdlib.h>
// Sparse Representation of Polynomial with MergeSort Logic
#define MAX_TERMS 100

typedef struct {
	float coef;
	int expon;
}Polynomial;

Polynomial terms[MAX_TERMS];
int avail = 0;

int Compare(int exp1, int exp2) {
	if (exp1 > exp2)
		return 1;
	else if (exp1 < exp2)
		return -1;
	else
		return 0;
}

void Attach(float coef, int expon) {
	if (avail >= MAX_TERMS)
		exit(-1);

	terms[avail].coef = coef;
	terms[avail++].expon = expon;
}

void PAdd(int starta, int finisha, int startb, int finishb, int* startd, int* finishd) {
	float coefficient;

	*startd = avail;
	while (starta <= finisha && startb <= finishb) {
		switch (Compare(terms[starta].expon, terms[startb].expon)) {
		case 1: // a>b
			Attach(terms[starta].coef, terms[starta].expon);
			starta++;
			break;
		case 0:
			coefficient = terms[starta].coef + terms[startb].coef;
			Attach(coefficient, terms[starta].expon);
			starta++; startb++;
			break;
		case -1:
			Attach(terms[startb].coef, terms[startb].expon);
			startb++;
			break;
		}
	}

	for (; starta <= finisha; starta++)
		Attach(terms[starta].coef, terms[starta].expon);
	for (; startb <= finishb; startb++)
		Attach(terms[startb].coef, terms[startb].expon);
	*finishd = avail;
}

int main(void) {
	int startA, finishA, startB, finishB, startC, finishC;

	terms[0].coef = 2; terms[0].expon = 1000; startA = 0;
	avail += 1;
	terms[1].coef = 1; terms[1].expon = 0; finishA = 1;
	avail += 1;
	terms[2].coef = 1; terms[2].expon = 4; startB = 2;
	avail += 1;
	terms[3].coef = 10; terms[3].expon = 3;
	avail += 1;
	terms[4].coef = 3; terms[4].expon = 2;
	avail += 1;
	terms[5].coef = 1; terms[5].expon = 0; finishB = 5;
	avail += 1;

	PAdd(startA, finishA, startB, finishB, &startC, &finishC);

	for (int i = startC; i < finishC - 1; i++)
		printf("%.0fx^%d + ", terms[i].coef, terms[i].expon);
	printf("%.0fx^%d", terms[finishC - 1].coef, terms[finishC - 1].expon);

	return 0;
}