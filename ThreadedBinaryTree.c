#include <stdio.h>
#include <stdlib.h>
// Chapter05. Threaded Binary Trees
#define TRUE		1
#define FALSE		0

struct threaded_tree {
	short int left_thread;
	struct threaded_tree *left_child;
	char data;
	struct threaded_tree *right_child;
	short int right_thread;
};
typedef struct threaded_tree * threaded_pointer;

threaded_pointer create_tree_node(char data) {
	threaded_pointer ptr = (threaded_pointer)malloc(sizeof(struct threaded_tree));
	ptr->data = data;
	ptr->left_child = NULL;
	ptr->right_child = NULL;
	ptr->left_thread = FALSE;
	ptr->right_thread = FALSE;
	return ptr;
}

threaded_pointer insucc(threaded_pointer tree) {
	threaded_pointer temp;
	temp = tree->right_child;
	if (!tree->right_thread)
		while (!temp->left_thread)
			temp = temp->left_child;
	return temp;
}

void insert_right(threaded_pointer parent, threaded_pointer child) {
	threaded_pointer temp;
	child->right_child = parent->right_child;
	child->right_thread = parent->right_thread;
	child->left_child = parent;
	child->left_thread = TRUE;
	parent->right_child = child;
	parent->right_thread = FALSE;
	if (!child->right_thread) {
		temp = insucc(child);
		temp->left_child = child;
	}
}

void insert_left(threaded_pointer parent, threaded_pointer child) {
	threaded_pointer temp;
	child->left_child = parent->left_child;
	child->left_thread = parent->left_thread;
	child->right_child = parent;
	child->right_thread = TRUE;
	parent->left_child = child;
	parent->left_thread = FALSE;
	if (!child->left_thread) {
		temp = insucc(child);
		temp->right_child = child;
	}
}

void tinorder(threaded_pointer tree) {
	threaded_pointer temp = tree;
	for (; ; ) {
		temp = insucc(temp);
		if (temp == tree) break;
		printf("%3c", temp->data);
	}
}

int main(void) {
	threaded_pointer ptr, temp, ptr1, n2, n3;
	threaded_pointer tree = (threaded_pointer)malloc(sizeof(struct threaded_tree));
	tree->right_child = tree;
	tree->left_thread = FALSE;
	tree->right_thread = FALSE;
	threaded_pointer n1 = (threaded_pointer)malloc(sizeof(struct threaded_tree));
	tree->left_child = n1;
	n1->data = 'A';
	n1->left_thread = TRUE;
	n1->left_child = tree;
	n1->right_thread = TRUE;
	n1->right_child = tree;

	temp = (threaded_pointer)malloc(sizeof(struct threaded_tree));
	temp->data = 'B';
	insert_left(n1, temp);
	ptr = temp;

	temp = (threaded_pointer)malloc(sizeof(struct threaded_tree));
	temp->data = 'E';
	insert_right(ptr, temp);
	temp = (threaded_pointer)malloc(sizeof(struct threaded_tree));
	temp->data = 'D';
	insert_left(ptr, temp);
	ptr = temp;

	temp = (threaded_pointer)malloc(sizeof(struct threaded_tree));
	temp->data = 'I';
	insert_right(ptr, temp);
	temp = (threaded_pointer)malloc(sizeof(struct threaded_tree));
	temp->data = 'H';
	insert_left(ptr, temp);
	
	ptr = (threaded_pointer)malloc(sizeof(struct threaded_tree));
	ptr->data = 'C';
	insert_right(n1, ptr);
	temp = (threaded_pointer)malloc(sizeof(struct threaded_tree));
	temp->data = 'F';
	insert_left(ptr, temp);
	n2 = temp;
	temp = (threaded_pointer)malloc(sizeof(struct threaded_tree));
	temp->data = 'G';
	insert_right(ptr, temp);
	ptr1 = ptr;
	ptr = temp;

	temp = (threaded_pointer)malloc(sizeof(struct threaded_tree));
	temp->data = 'J';
	insert_right(ptr, temp);

	tinorder(tree);
	printf("\n");

	temp = (threaded_pointer)malloc(sizeof(struct threaded_tree));
	temp->data = 'X';
	insert_left(n2, temp);
	temp = (threaded_pointer)malloc(sizeof(struct threaded_tree));
	temp->data = 'Y';
	insert_right(n2, temp);
	tinorder(tree);
	printf("\n");

	return 0;
}