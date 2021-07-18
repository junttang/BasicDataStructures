#include <stdio.h>
// Infix Expressions Evaluating
#define MAX_EXP_SIZE		100
#define MAX_STACK_SIZE		100
typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand }
precedence;
int stack[MAX_STACK_SIZE];
precedence Stack[MAX_STACK_SIZE];
char expr[MAX_EXP_SIZE];
char convert[MAX_EXP_SIZE];
int top = -1;
int Top = 0;
int k = 0;
static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

void push(int n) {
	stack[++top] = n;
}

int pop() {
	return stack[top--];
}

void Push(precedence n) {
	Stack[++Top] = n;
}

precedence Pop() {
	return Stack[Top--];
}


precedence getToken(char *symbol, int *n) {
	*symbol = expr[(*n)++];

	switch (*symbol) {
	case '(': return lparen;	
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}

int eval(void) {
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0;
	token = getToken(&symbol, &n);
	while (token != eos) {	
		if (token == operand)
			push(symbol - '0');
		else {	
			op2 = pop();
			op1 = pop();
			switch (token) {
			case plus: push(op1 + op2); break;
			case minus: push(op1 - op2); break;
			case times: push(op1*op2); break;
			case divide: push(op1 / op2); break;
			case mod: push(op1%op2);
			}
		}
		token = getToken(&symbol, &n);
	}
	return pop();
}

void printToken(precedence unit) {
	switch (unit) {
	case plus: convert[k++] = '+'; break;
	case minus: convert[k++] = '-'; break;
	case divide: convert[k++] = '/'; break;
	case times: convert[k++] = '*'; break;
	case mod: convert[k++] = '%'; break;
	case eos: convert[k++] = '\0'; break;
	}
}

void postfix(void) {
	char symbol;
	precedence token;
	int n = 0;	
	Top = 0;
	Stack[0] = eos;

	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		if (token == operand)
			convert[k++] = symbol;//printf("%c", symbol);
		else if (token == rparen) {
			while (Stack[Top] != lparen)
				printToken(Pop());
			Pop();
		}
		else {	
			while (isp[Stack[Top]] >= icp[token])	
				printToken(Pop());		
			Push(token);
		}
	}
	while ((token = Pop()) != eos) printToken(token);
	//printf("\n");
}

int main(void) {
	strcpy(expr, "6/(2-3)+4*2");
	printf("%s ", expr);
	postfix();
	strcpy(expr, convert);
	printf("= %d\n", eval());
	return 0;
}