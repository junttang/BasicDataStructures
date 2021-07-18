#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Chapter05. The Satisfiability Problem
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100
#define TRUE 1
#define FALSE 0
//typedef enum { not, and, or , T, F } logical;
typedef enum { lparen, rparen, not, and, or , eos, operand, T, F } logical;
// Ʈ���� ����� ���� �� ������ Ȯ���� ������ ����
struct node {
	struct node *left_child;
	logical data;			// ����� ���� ���� ����
	short int value;		// ������ ������ ����
	struct node *right_child;
};
typedef struct node* tree_pointer;

char expr[MAX_EXPR_SIZE];	// ������
char convert[MAX_EXPR_SIZE];// ������
struct node* Stack[MAX_STACK_SIZE];	// ����Ʈ�� ���࿡ ���Ǵ� ��� ����
logical stack[MAX_STACK_SIZE]; // ������ ��ȯ�� ���Ǵ� �켱���� ����
int top = 0; // ���� �ε���
int idx = 0; // ������ ����� ���Ǵ� �ε���
static int isp[] = { 0, 19, 13, 12, 12, 0 };	// top�� �ִ� �������� �켱����
static int icp[] = { 20, 19, 13, 12, 12, 0 };	// ���ÿ� ���� ������ ������
												// �� �켱����
// ������ ��ȯ�� ���̴� ���� ��� �Լ�
void push(logical n) {
	stack[++top] = n;
}

logical pop() {
	return stack[top--];
}
// ������->����Ʈ�� ���࿡ ���̴� ���� ��� �Լ�
void Push(struct node* n) {
	Stack[++top] = n;
}

struct node* Pop() {
	return Stack[top--];
}

/*
getToken�Լ��� �Է¹��� ���ڿ� �迭(����) expr�� ���ڸ� �ϳ� �ϳ� �о�
�ش� ������ �켱���� ������ ��ȯ�ϴ� �Լ��̴�.
(�Է¹��� ���������� ������������ ��ȯ�ϱ� ���ؼ� �ʿ��ϴ�.)
*/
logical getToken(char *symbol, int *n) {
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '&': return and;
	case '|': return or;
	case '~': return not;
	case '\0': return eos;
	default: return operand;
	}
}

/*
getToken�� ���� �ν��� ������ ������ ���� ������ ���ڿ� �迭(����)
convert�� �ű�� �Լ��̴�.
*/
void printToken(logical unit) { 	// ��ū�� ������ ���ڿ��� �ű�� �Լ�
	switch (unit) {
	case and: convert[idx++] = '&'; break;
	case or: convert[idx++] = '|'; break;
	case not: convert[idx++] = '~'; break;
	case eos: convert[idx++] = '\0'; break;
	}
}

void postfix(void) {
	char symbol;		// ���ڸ� call by reference�� �Է¹��� ����
	logical token;	// ������ ������ token�� ���
	int n = 0;			// ���ڸ� �Է¹��� �� ���̴� �ε��� ����
	top = 0;			// ������ top�� �ʱ�ȭ
	stack[0] = eos;		// ù ��° �������� ��쿡���� �񱳴���� �־���ϹǷ� eos��
	// �ʱ�ȭ�� ���ѳ��� ��! eos�� �켱������ 0�̹Ƿ� �������ڵ��� ���������� ��
	// ���̰�, ���� ������ Pop�� ������.
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		if (token == operand)	// �о���� ���ڰ� �������̸�,
			convert[idx++] = symbol;	// �״�� ���������� �ű��.
		else if (token == rparen) {	// �ݴ� �Ұ�ȣ�̸�,
			while (stack[top] != lparen)	// ���� �Ұ�ȣ�� ���� ������
				printToken(pop());	// ������ �����ڵ��� ��� ���������� �ű��.
			pop();	// ���� �Ұ�ȣ ��ü�� ������.
		}
		else {	// ���ڰ� ���������̸�,
			while (isp[stack[top]] >= icp[token]) // ���� ������ �������� �켱����
				printToken(pop());	// ���� ���� �����ڴ� ������ ���������� �ű��.
			push(token);	// �� �����ڰ� �� ������ �׳� ���ÿ� �ִ´�.
		}
	}
	while ((token = pop()) != eos)	// �����ִ� ���� ��ҵ��� ��� ���������� �ű��.
		printToken(token);
}

tree_pointer create_tree_node(char data) {
	tree_pointer ptr = (tree_pointer)malloc(sizeof(struct node));
	ptr->data = data;
	ptr->left_child = NULL;
	ptr->right_child = NULL;
	return ptr;
}

struct node* MakeExpTree(logical valueArr[]) {
	struct node* ptr;
	char symbol;		// ���ڸ� call by reference�� �Է¹��� ����
	logical token;
	int n = 0;

	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		ptr = create_tree_node(token); // Ʈ�� ��带 �����ϰ�,
		switch (token) {
		case and:	// AB&�̸�, BA������ ���ÿ��� �����Ƿ� �����ڽĳ����� �����Ѵ�.
			ptr->right_child = Pop(); // �ڡڡ�
			ptr->left_child = Pop();
			break;
		case or:	// and�� ��������
			ptr->right_child = Pop(); // �ڡڡ�
			ptr->left_child = Pop();
			break;
		case not:	// not�������� ��� �����ڽĳ��θ� �����Ѵ�.
			ptr->right_child = Pop();
			break;
		default:
			if (symbol == 'a')
				ptr->data = valueArr[0];
			else if (symbol == 'b')
				ptr->data = valueArr[1];
			else if (symbol == 'c')
				ptr->data = valueArr[2];
			break;
		}

		Push(ptr); // ���� �� ����� ���� �ٽ� �������� ����. �ڡڡ�
	}

	return Pop();	// ������ ��Ʈ ��带 Pop�Ѵ�. �̷��� �ؼ� ���� ���� Ʈ����
}					// ����ȴ�.

void post_order_eval(tree_pointer node) {
	if (node) {
		post_order_eval(node->left_child);	// ����� ������ȸ�� �����Ѵ�.
		post_order_eval(node->right_child);
		switch (node->data) {				// ��ȸ ���� ����� �����Ͱ�
		case not: node->value = !node->right_child->value;
			break;	// not�������� ��� ���� �ڽĳ���� ������ �ݴ밪�� ������.��
		case and: node->value = node->right_child->value && node->left_child->value;
			break;	// and�������� ��� �� �ڽĳ���� ������ and���� ������.��
		case or: node->value = node->right_child->value || node->left_child->value;
			break;	// or�������� ��� �� �ڽĳ���� ������ or���� ������.��
		case T: node->value = TRUE;	// 1
			break;
		case F: node->value = FALSE; // 0
		}
	}
}

void recursive_inorder(tree_pointer ptr) {
	if (ptr) {
		recursive_inorder(ptr->left_child);
		switch (ptr->data) {
		case and: printf("&"); break;
		case or : printf("|"); break;
		case not: printf("~"); break;
		case T: printf("1"); break;
		case F: printf("0"); break;
		}
		recursive_inorder(ptr->right_child);
	}
}

int main(void) {
	tree_pointer tree;
	strcpy(expr, "(a&~b)|(~a&c)|~c");
	printf("%s \n", expr);
	postfix();
	//printf("\n%s\n", convert);
	strcpy(expr, convert);

	for (int i = 0; i < 8; i++) {
		logical valueArr[3];

		if (i / 4 == 0)
			valueArr[0] = T;
		else
			valueArr[0] = F;
		if ((i / 2) % 2 == 0)
			valueArr[1] = T;
		else
			valueArr[1] = F;
		if (i % 2 == 0)
			valueArr[2] = T;
		else
			valueArr[2] = F;
		tree = MakeExpTree(valueArr);
		//recursive_inorder(tree);
		//printf("\n");
		post_order_eval(tree);
		if (tree->value)
			printf("(%d,%d,%d)\n", valueArr[0]%2, valueArr[1]%2, valueArr[2]%2);
	}

	return 0;
}