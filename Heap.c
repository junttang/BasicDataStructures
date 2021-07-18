#include <stdio.h>
// Chapter05 - Heap
#define MAX_ELEMENTS 200/* maximum heap size + 1 */
#define TRUE		1
#define FALSE		0
#define HEAP_FULL(n) ((n == (MAX_ELEMENTS)) ? TRUE : FALSE) 
#define HEAP_EMPTY(n) (!n)
typedef struct {
	int key;
} element;

element heap[MAX_ELEMENTS];
element minheap[MAX_ELEMENTS];
int n = 0;
int min = 0;

void insert_max_heap(element item, int *n) {
	int i;

	if (HEAP_FULL(*n)) {
		fprintf(stderr, "The heap is full.\n");
		exit(1);
	}

	i = ++(*n);				// Call By Reference
	while ((i != 1) && (item.key > heap[i / 2].key)) {
		heap[i] = heap[i / 2];	
		i /= 2;	
	}
	heap[i] = item;
}

void insert_min_heap(element item, int *n) {
	int i;

	if (HEAP_FULL(*n)) {
		fprintf(stderr, "The heap is full.\n");
		exit(1);
	}

	i = ++(*n);				// Call By Reference
	while ((i != 1) && (item.key < minheap[i / 2].key)) {
		minheap[i] = minheap[i / 2];
		i /= 2;
	}
	minheap[i] = item;
}

element delete_max_heap(int *n) {
	int parent, child;
	element item, temp;

	if (HEAP_EMPTY(*n)) {
		fprintf(stderr, "The heap is empty");
		exit(1);
	}

	item = heap[1];
	temp = heap[(*n)--];

	parent = 1;
	child = 2;
	while (child <= *n) {
		if ((child < *n) && (heap[child].key < heap[child + 1].key))
			child++;			
		if (temp.key >= heap[child].key) 
			break;
		heap[parent] = heap[child];	 
		parent = child;
		child *= 2;
	}

	heap[parent] = temp;
	return item;
}

element delete_min_heap(int *n) {
	int parent, child;
	element item, temp;

	if (HEAP_EMPTY(*n)) {
		fprintf(stderr, "The heap is empty");
		exit(1);
	}

	item = minheap[1];
	temp = minheap[(*n)--];

	parent = 1;
	child = 2;
	while (child <= *n) {
		if ((child < *n) && (minheap[child].key > minheap[child + 1].key))
			child++;
		if (temp.key <= minheap[child].key)
			break;
		minheap[parent] = minheap[child];
		parent = child;
		child *= 2;
	}

	minheap[parent] = temp;
	return item;
}

int main(void) {
	int size;
	element item;
	item.key = 5;
	insert_max_heap(item, &n); insert_min_heap(item, &min);
	item.key = 6;
	insert_max_heap(item, &n); insert_min_heap(item, &min);
	item.key = 2;
	insert_max_heap(item, &n); insert_min_heap(item, &min);
	item.key = 7;
	insert_max_heap(item, &n); insert_min_heap(item, &min);
	item.key = 1;
	insert_max_heap(item, &n); insert_min_heap(item, &min);
	item.key = 3;
	insert_max_heap(item, &n); insert_min_heap(item, &min);
	item.key = 4;
	insert_max_heap(item, &n); insert_min_heap(item, &min);

	size = n;
	for (int i = 1; i <= size; i++)
		printf("%d ", delete_max_heap(&n).key);
	printf("\n");
	for (int i = 1; i <= size; i++)
		printf("%d ", delete_min_heap(&min).key);

	return 0;
}