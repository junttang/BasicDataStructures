#include <stdio.h>
#define MAX_STACK_SIZE 100
// Rat in Maze
typedef struct {
	int vert;
	int horiz;
}offset;

typedef struct {
	short int row;
	short int col;
	short int dir;
} element;

typedef struct {
	int numOfStack;
	int top;
	element list[MAX_STACK_SIZE];
}Stack;

void StackInit(Stack* stack) {
	stack->numOfStack = 0;
	stack->top = -1;
}

int SIsEmpty(Stack stack) {
	if (stack.numOfStack == 0)
		return 1;
	return 0;
}

void SPush(Stack*stack, element item) {
	if (stack->numOfStack == MAX_STACK_SIZE - 1)
		return;

	stack->list[++(stack->top)] = item;
	(stack->numOfStack)++;
}

element SPop(Stack*stack) {
	if (SIsEmpty(*stack))
		return;

	(stack->numOfStack)--;
	return stack->list[(stack->top)--];
}

int main(void) {
	int maze[7][7] = { 
		1,1,1,1,1,1,1,
		1,0,0,0,0,1,1,
		1,1,1,1,1,0,1,
		1,1,0,0,0,1,1,
		1,0,1,1,1,1,1,
		1,1,0,0,0,0,1,
		1,1,1,1,1,1,1
	};
	int maze[7][7] = {
		1,1,1,1,1,1,1,
		1,0,1,0,1,1,1,
		1,1,0,1,0,0,1,
		1,1,1,0,1,0,1,
		1,1,0,1,1,1,1,
		1,1,1,0,0,0,1,
		1,1,1,1,1,1,1
	};
	int mark[7][7] = {
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0
	};
	Stack stack;
	element entrance = { 1,1,2 };
	int nextRow, nextCol, nextDir;
	int cnt = 0, flag = 0, i, k = 0;
	offset move[8] = { {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1} };

	StackInit(&stack);
	SPush(&stack, entrance);

	while (!SIsEmpty(stack)) {
		i = 0;
		if (flag == 1)
			break;
		if (cnt != 0)
			SPop(&stack);

		while (i < 8) {
			nextRow = stack.list[stack.top].row + move[i].vert;
			nextCol = stack.list[stack.top].col + move[i].horiz;
			nextDir = i;
			if (nextRow == 5 && nextCol == 5) {
				printf("Success!\n");
				maze[nextRow][nextCol] = 3;
				flag = 1;
				break;
			}
			if (maze[nextRow][nextCol] == 0 && mark[nextRow][nextCol] == 0) {
				printf("%d %d\n", nextRow, nextCol);
				element newItem = { nextRow,nextCol,nextDir };
				mark[nextRow][nextCol] = 1;
				SPush(&stack, newItem);
				i = 0;
			}
			i++;
		}
		cnt = 1;
	}
	printf("\n\n");
	for (int i = 0;; i++) {
		if (SIsEmpty(stack))
			break;
		maze[stack.list[stack.top].row][stack.list[stack.top].col] = 2;
		SPop(&stack);
	}
	printf("\n\n");
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++)
			printf("%d ", maze[i][j]);
		printf("\n");
	}

	return 0;
}