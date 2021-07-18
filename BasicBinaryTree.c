#include <stdio.h>
#include <stdlib.h>
#define max_stack_size 100

struct node {
	char data;
	struct node *left_child, *right_child;
};
typedef struct node *tree_pointer;

tree_pointer stack[max_stack_size];

tree_pointer create_tree_node(char data);
void recursive_inorder(tree_pointer ptr);
void iter_inorder(tree_pointer node);
void iter_postorder(tree_pointer ptr);
void iter_preorder(tree_pointer ptr);
void level_order(tree_pointer ptr);

void add(int *top, tree_pointer node) {
	(*top)++;

	stack[*top] = node;
}

tree_pointer delete(int* top) {
	return stack[(*top)--];
}

void main() {
	tree_pointer ptr, ptr1, ptr2;

	ptr1 = create_tree_node('a');
	ptr2 = create_tree_node('b');
	ptr = create_tree_node('/');
	ptr->left_child = ptr1;
	ptr->right_child = ptr2;

	ptr1 = ptr;
	ptr2 = create_tree_node('c');
	ptr = create_tree_node('*');
	ptr->left_child = ptr1;
	ptr->right_child = ptr2;

	ptr1 = ptr;
	ptr2 = create_tree_node('d');
	ptr = create_tree_node('*');
	ptr->left_child = ptr1;
	ptr->right_child = ptr2;

	ptr1 = ptr;
	ptr2 = create_tree_node('e');
	ptr = create_tree_node('+');
	ptr->left_child = ptr1;
	ptr->right_child = ptr2;

	recursive_inorder(ptr);
	printf("\n");
	iter_inorder(ptr);
	printf("\n");
	iter_preorder(ptr);
	printf("\n");
	iter_postorder(ptr);
	printf("\n");
	level_order(ptr);
	printf("\n");
}

tree_pointer create_tree_node(char data) {
	tree_pointer ptr = (tree_pointer)malloc(sizeof(struct node));
	ptr->data = data;
	ptr->left_child = NULL;
	ptr->right_child = NULL;
	return ptr;
}

void recursive_inorder(tree_pointer ptr) {
	if (ptr) {
		recursive_inorder(ptr->left_child);
		printf("%c ", ptr->data);
		recursive_inorder(ptr->right_child);
	}
}

void iter_inorder(tree_pointer node) {
	int top = -1;
	for (; ; ) {
		for (; node; node = node->left_child)
			add(&top, node);
		node = delete(&top);
		if (!node) break;
		printf("%c ", node->data);
		node = node->right_child;
	}
}

void iter_preorder(tree_pointer node) {
	int top = -1;
	for (; ; ) {
		for (; node; node = node->left_child) {
			printf("%c ", node->data);
			add(&top, node);
		}
		node = delete(&top);
		if (!node) break;
		
		node = node->right_child;
	}
}

void iter_postorder(tree_pointer node) {
	int top = -1;
	for (; ; ) {
		if (node->left_child) {
			add(&top, node);
			add(&top, node->right_child);
			node = node->left_child;
		}
		else {
			if (node->right_child) {
				add(&top, node);
				node = node->right_child;
			}
			else {
				printf("%c ", node->data);
				node = delete(&top);
				if (!node) break;
			}
		}
		
	}
}