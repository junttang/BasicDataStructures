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
		temp = root;	// NULL로 가기 전에 temp에 기억시킴.
		if (k < root->data.key)
			root = root->leftChild;
		else if (k > root->data.key)
			root = root->rightChild;
		else // k와 key가 일치하는 경우 NULL 반환
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

	if (!current)	// 빈 트리인 경우
		return;
	while (1) {		// 트리를 다 돌 때까지 반복
		if (k > current->data.key) {	// k가 key보다 크면
			if (current->rightChild == NULL) // 우측 자식노드로!
				break;			// 근데 우측이 없으면 트리를 다 돈 것!
			previous = current;		// previous는 부모노드 지칭
			current = current->rightChild; // current는 우측자식노드 지칭
		}
		else {						// k매칭을 찾거나 key보다 작은 경우
			if (k == current->data.key)	// 매칭된 경우 해당 위치를
				target = current;		// target이 기억
			if (current->leftChild == NULL) // 더 좌측으로 못가면 트리 다 돈 것
				break;
			previous = current;		// 부모지칭
			current = current->leftChild;	// 좌로 이동
		}			// k 매칭 이후 계속 if에 걸릴 것. target의 좌측은 모두 target
	}				// 보다 작음. 계속 if에 걸리면 좌측서브트리의 최우측 노드로 
					// 자동으로 이동하게 될 것임. (좌측서브에서 가장 큰 값 :current)
	if (target == NULL)	// 트리를 움직였는데 k와 매칭된 key가 없는 경우
		return;
	else {
		if (previous == NULL) {		// 부모가 없는 상황 : 트리에 루트만 있고
			temp = current->data;	// k가 루트 key와 일치한 상황
			free(current);			// temp는 데이터 기억하고
			root = NULL;		// 루트노드 메모리 해제하고 NULL처리
			return temp;
		}
		else {						// 부모노드가 있는 상황
			temp = target->data;	// 우선 매칭된 key는 temp가 기억(리턴예정)
			target->data.key = current->data.key;	// 좌측서브에서 가장 큰 값으로
													// 대치
			if (previous->leftChild == current)		// terget 좌측서브트리가 노드 한 개
				previous->leftChild = current->leftChild;	// 인 경우
			else // target의 좌측서브트리에서 가장 key가 큰 노드가 current인 경우
				previous->rightChild = current->leftChild; // current의 부모의 우측 
								// 으로 current의 좌측트리를 연결해주면 된다.
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