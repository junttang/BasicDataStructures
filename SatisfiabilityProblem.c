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
// 트리의 노드의 종류 및 논리값을 확인할 열거형 정의
struct node {
	struct node *left_child;
	logical data;			// 노드의 종류 결정 변수
	short int value;		// 논리값을 저장할 변수
	struct node *right_child;
};
typedef struct node* tree_pointer;

char expr[MAX_EXPR_SIZE];	// 중위식
char convert[MAX_EXPR_SIZE];// 후위식
struct node* Stack[MAX_STACK_SIZE];	// 이진트리 구축에 사용되는 노드 스택
logical stack[MAX_STACK_SIZE]; // 후위식 변환에 사용되는 우선순위 스택
int top = 0; // 스택 인덱스
int idx = 0; // 후위식 저장시 사용되는 인덱스
static int isp[] = { 0, 19, 13, 12, 12, 0 };	// top에 있는 연산자의 우선순위
static int icp[] = { 20, 19, 13, 12, 12, 0 };	// 스택에 새로 들어오는 연산자
												// 의 우선순위
// 후위식 변환에 쓰이는 스택 기능 함수
void push(logical n) {
	stack[++top] = n;
}

logical pop() {
	return stack[top--];
}
// 후위식->이진트리 구축에 쓰이는 스택 기능 함수
void Push(struct node* n) {
	Stack[++top] = n;
}

struct node* Pop() {
	return Stack[top--];
}

/*
getToken함수는 입력받은 문자열 배열(전역) expr의 문자를 하나 하나 읽어
해당 문자의 우선순위 종류를 반환하는 함수이다.
(입력받은 중위논리식을 후위논리식으로 변환하기 위해서 필요하다.)
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
getToken을 통해 인식한 문자의 종류에 따라서 후위식 문자열 배열(전역)
convert에 옮기는 함수이다.
*/
void printToken(logical unit) { 	// 토큰을 후위식 문자열로 옮기는 함수
	switch (unit) {
	case and: convert[idx++] = '&'; break;
	case or: convert[idx++] = '|'; break;
	case not: convert[idx++] = '~'; break;
	case eos: convert[idx++] = '\0'; break;
	}
}

void postfix(void) {
	char symbol;		// 문자를 call by reference로 입력받을 변수
	logical token;	// 문자의 종류를 token에 기억
	int n = 0;			// 문자를 입력받을 때 쓰이는 인덱스 변수
	top = 0;			// 스택의 top을 초기화
	stack[0] = eos;		// 첫 번째 연산자의 경우에서도 비교대상이 있어야하므로 eos로
	// 초기화를 시켜놓는 것! eos의 우선순위는 0이므로 논리연산자들이 지속적으로 들어갈
	// 것이고, 가장 마지막 Pop때 날린다.
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		if (token == operand)	// 읽어들인 문자가 논리변수이면,
			convert[idx++] = symbol;	// 그대로 후위식으로 옮긴다.
		else if (token == rparen) {	// 닫는 소괄호이면,
			while (stack[top] != lparen)	// 여는 소괄호가 나올 때가지
				printToken(pop());	// 스택의 연산자들을 모두 후위식으로 옮긴다.
			pop();	// 여는 소괄호 자체는 날린다.
		}
		else {	// 문자가 논리연산자이면,
			while (isp[stack[top]] >= icp[token]) // 새로 들어오는 연산자의 우선순위
				printToken(pop());	// 보다 높은 연산자는 모조리 후위식으로 옮긴다.
			push(token);	// 새 연산자가 더 높으면 그냥 스택에 넣는다.
		}
	}
	while ((token = pop()) != eos)	// 남아있는 스택 요소들을 모두 후위식으로 옮긴다.
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
	char symbol;		// 문자를 call by reference로 입력받을 변수
	logical token;
	int n = 0;

	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		ptr = create_tree_node(token); // 트리 노드를 생성하고,
		switch (token) {
		case and:	// AB&이면, BA순으로 스택에서 빠지므로 우측자식노드부터 연결한다.
			ptr->right_child = Pop(); // ★★★
			ptr->left_child = Pop();
			break;
		case or:	// and와 마찬가지
			ptr->right_child = Pop(); // ★★★
			ptr->left_child = Pop();
			break;
		case not:	// not연산자의 경우 우측자식노드로만 연결한다.
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

		Push(ptr); // 생성 및 연결된 노드는 다시 스택으로 들어간다. ★★★
	}

	return Pop();	// 마지막 루트 노드를 Pop한다. 이렇게 해서 수식 이진 트리가
}					// 구축된다.

void post_order_eval(tree_pointer node) {
	if (node) {
		post_order_eval(node->left_child);	// 재귀적 후위순회를 진행한다.
		post_order_eval(node->right_child);
		switch (node->data) {				// 조회 중인 노드의 데이터가
		case not: node->value = !node->right_child->value;
			break;	// not연산자인 경우 우측 자식노드의 논리값의 반대값을 가진다.★
		case and: node->value = node->right_child->value && node->left_child->value;
			break;	// and연산자인 경우 두 자식노드의 논리값의 and값을 가진다.★
		case or: node->value = node->right_child->value || node->left_child->value;
			break;	// or연산자인 경우 두 자식노드의 논리값의 or값을 가진다.★
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