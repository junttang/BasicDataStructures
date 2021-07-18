#include <stdio.h>
#include <stdlib.h>
// Chapter05. Binary Search Trees

typedef struct _elem {
	int key;
}element;

struct node {
	struct node * leftChild;
	element data;
	struct node * rightChild;
};
typedef struct node * treePointer;

void show(treePointer root) {
	if (root)
	{
		printf("%d ", root->data.key);
		show(root->leftChild);
		show(root->rightChild);
	}
}

element* search(treePointer root, int k) {
	if (!root)
		return NULL;
	if (k == root->data.key)
		return &(root->data);
	if (k < root->data.key)
		return search(root->leftChild, k);
	return search(root->rightChild, k);
}

element* iterSearch(treePointer tree, int k) {
	while (tree) {
		if (k == tree->data.key)
			return &(tree->data);
		if (k < tree->data.key)
			tree = tree->leftChild;
		else
			tree = tree->rightChild;
	}
	return NULL;
}

treePointer modifiedSearch(treePointer root, int k) {
	treePointer temp = root;

	while (root) {
		temp = root;	// NULL�� ���� ���� temp�� ����Ŵ.
		if (k < root->data.key)
			root = root->leftChild;
		else if (k > root->data.key)
			root = root->rightChild;
		else // k�� key�� ��ġ�ϴ� ��� NULL ��ȯ
			return NULL;
	}
	return temp;
}

void insertNode(treePointer *node, int k) {
	treePointer ptr, temp = modifiedSearch(*node, k);

	if (temp || !(*node)) {		
		ptr = (treePointer)malloc(sizeof(*ptr));	
		ptr->data.key = k;
		ptr->leftChild = ptr->rightChild = NULL;		

		if (*node) {				
			if (k < temp->data.key) 	
				temp->leftChild = ptr;
			else 			
				temp->rightChild = ptr;
		}
		else *node = ptr;			
	}
}

element delete(treePointer root, int k) {
	element temp;
	treePointer current, target, previous;
	current = root;
	target = NULL;

	if (!current)	// �� Ʈ���� ���
		return;
	while (1) {		// Ʈ���� �� �� ������ �ݺ�
		if (k > current->data.key) {	// k�� key���� ũ��
			if (current->rightChild == NULL) // ���� �ڽĳ���!
				break;			// �ٵ� ������ ������ Ʈ���� �� �� ��!
			previous = current;		// previous�� �θ��� ��Ī
			current = current->rightChild; // current�� �����ڽĳ�� ��Ī
		}
		else {						// k��Ī�� ã�ų� key���� ���� ���
			if (k == current->data.key)	// ��Ī�� ��� �ش� ��ġ��
				target = current;		// target�� ���
			if (current->leftChild == NULL) // �� �������� ������ Ʈ�� �� �� ��
				break;
			previous = current;		// �θ���Ī
			current = current->leftChild;	// �·� �̵�
		}			// k ��Ī ���� ��� if�� �ɸ� ��. target�� ������ ��� target
	}				// ���� ����. ��� if�� �ɸ��� ��������Ʈ���� �ֿ��� ���� 
					// �ڵ����� �̵��ϰ� �� ����. (�������꿡�� ���� ū �� :current)
	if (target == NULL)	// Ʈ���� �������µ� k�� ��Ī�� key�� ���� ���
		return;
	else {
		if (previous == NULL) {		// �θ� ���� ��Ȳ : Ʈ���� ��Ʈ�� �ְ�
			temp = current->data;	// k�� ��Ʈ key�� ��ġ�� ��Ȳ
			free(current);			// temp�� ������ ����ϰ�
			root = NULL;		// ��Ʈ��� �޸� �����ϰ� NULLó��
			return temp;
		}
		else {						// �θ��尡 �ִ� ��Ȳ
			temp = target->data;	// �켱 ��Ī�� key�� temp�� ���(���Ͽ���)
			target->data.key = current->data.key;	// �������꿡�� ���� ū ������
													// ��ġ
			if (previous->leftChild == current)		// terget ��������Ʈ���� ��� �� ��
				previous->leftChild = current->leftChild;	// �� ���
			else // target�� ��������Ʈ������ ���� key�� ū ��尡 current�� ���
				previous->rightChild = current->leftChild; // current�� �θ��� ���� 
								// ���� current�� ����Ʈ���� �������ָ� �ȴ�.
			free(current);
			return temp;
		}
	}
}

int main(void) {
	treePointer root = NULL;

	insertNode(&root, 20);
	insertNode(&root, 10);
	insertNode(&root, 6);
	insertNode(&root, 2);
	insertNode(&root, 8);
	insertNode(&root, 7);
	insertNode(&root, 15);
	insertNode(&root, 40);
	insertNode(&root, 30);
	insertNode(&root, 55);
	insertNode(&root, 25);

	show(root);
	printf("\n");
	insertNode(&root, 18);
	insertNode(&root, 12);
	show(root);

	printf("\ndelete: %d \n", delete(root, 10));
	show(root);
	printf("\ndelete: %d \n", delete(root, 40));
	show(root);

	return 0;
}