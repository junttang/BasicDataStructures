#include <stdio.h>
#include <stdlib.h>
// Chapter07. Sorting - Quick Sort
#define SWAP(a, b) { item_type tmp; tmp = a; a = b; b = tmp; }

typedef int item_type;

int Rpartition(item_type *A, int left, int right) {
	int i, pivot;
	pivot = left;
	for (i = left; i < right; i++) {		// rightmost
		if (A[i] < A[right]) {
			SWAP(A[i], A[pivot]);
			pivot++;
		}
	}
	SWAP(A[right], A[pivot]);
	return(pivot);
}

int Lpartition(item_type *A, int left, int right) {
	int i, pivot;
	pivot = right;
	for (i = right; i > left; i--) {		// Leftmost
		if (A[i] > A[left]) {
			SWAP(A[i], A[pivot]);
			pivot--;
		}
	}
	SWAP(A[left], A[pivot]);
	return(pivot);
}

int Mpartition(item_type *A, int left, int right) {
	int i, pivot, mean;
	mean = left;
	mean += (rand() % (right - left) + rand() % (right - left) + rand() % (right - left)) / 3;
	pivot = left;
	for (i = left; i < mean; i++) {
		if (A[i] < A[mean]) {
			SWAP(A[i], A[pivot]);
			pivot++;
		}
	}
	SWAP(A[mean], A[pivot]);
	mean = pivot;
	pivot = right;
	for (i = right; i > mean; i--) {
		if (A[i] > A[mean]) {
			SWAP(A[i], A[pivot]);
			pivot--;
		}
	}
	SWAP(A[mean], A[pivot]);

	return(pivot);
}

void quick_sort(item_type *A, int left, int right) {
	int pivot;
	if (right - left > 0) {
		pivot = Mpartition(A, left, right);
		quick_sort(A, left, pivot - 1);
		quick_sort(A, pivot + 1, right);
	}
}

int main(void) {
	item_type A[8] = { 15,22,13,20,12,10,27,25 };

	quick_sort(A, 0, 7);

	for (int i = 0; i < 8; i++)
		printf("%d  ", A[i]);
	return 0;
}