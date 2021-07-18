#include <stdio.h>
// Sparse Matrix
#define MAX_ARR_SIZE	101

typedef struct {
	int row;
	int col;
	int value;
}Term;

Term matrix[MAX_ARR_SIZE];

void CreateMatrix(int row, int col, int terms) {
	matrix[0].row = row;
	matrix[0].col = col;
	matrix[0].value = terms;
}

Term* Transpose(Term arr[]) {
	Term* tmatrix = (Term*)malloc(sizeof(Term)*MAX_ARR_SIZE);
	int i = 0, j, cnt = 1;
	int n = arr[0].value;

	tmatrix[0].row = arr[0].col;
	tmatrix[0].col = arr[0].row;
	tmatrix[0].value = n;

	while (i < arr[0].col) {
		j = 1;
		while (j<=n) {
			if (arr[j].col == i) {
				tmatrix[cnt].col = arr[j].row;
				tmatrix[cnt].row = arr[j].col;
				tmatrix[cnt++].value = arr[j].value;
			}
			j++;
		}
		i++;
	}
	
	return tmatrix;
}

Term* AdvancedTranspose(Term arr[]) {
	Term* tmatrix = (Term*)malloc(sizeof(Term)*MAX_ARR_SIZE);
	int temp[MAX_ARR_SIZE] = { 0, };
	int start[MAX_ARR_SIZE] = { 0, };
	int i = 1;
	int n = arr[0].value;

	tmatrix[0].row = arr[0].col;
	tmatrix[0].col = arr[0].row;
	tmatrix[0].value = n;

	while (i <= n) {
		temp[arr[i].col]++;
		i++;
	}
	i = 1;
	while (i < arr[0].col) {
		start[i] = start[i - 1] + temp[i - 1];
		i++;
	}

	i = 1;
	while (i <= n) {
		tmatrix[start[arr[i].col] + 1].col = arr[i].row;
		tmatrix[start[arr[i].col] + 1].row = arr[i].col;
		tmatrix[start[arr[i].col] + 1].value = arr[i].value;
		start[arr[i].col]++;
		i++;
	}

	return tmatrix;
}

void PrintMatrix(Term arr[]) {
	int i, j, k;
	int in = arr[0].row;
	int jn = arr[0].col;
	int kn = arr[0].value;
	for (i = 0; i < in; i++) {
		for (j = 0; j < jn; j++) {
			int kflag = 0;
			for (k = 1; k <= kn; k++) {
				if (arr[k].row == i && arr[k].col == j) {
					printf("%3d ", arr[k].value);
					kflag = 1;
					break;
				}
			}
			if (kflag == 1)
				continue;
			printf("%3d ", 0);
		}
		printf("\n");
	}
	printf("\n");
}

int main(void) {
	Term*tmatrix;
	CreateMatrix(6, 6, 8);

	matrix[1].row = 0; matrix[1].col = 0; matrix[1].value = 15;
	matrix[2].row = 0; matrix[2].col = 3; matrix[2].value = 22;
	matrix[3].row = 0; matrix[3].col = 5; matrix[3].value = -15;
	matrix[4].row = 1; matrix[4].col = 1; matrix[4].value = 11;
	matrix[5].row = 1; matrix[5].col = 2; matrix[5].value = 3;
	matrix[6].row = 2; matrix[6].col = 3; matrix[6].value = -6;
	matrix[7].row = 4; matrix[7].col = 0; matrix[7].value = 91;
	matrix[8].row = 5; matrix[8].col = 2; matrix[8].value = 28;

	PrintMatrix(matrix);

	tmatrix = AdvancedTranspose(matrix);

	for (int i = 0; i < 9; i++)
		printf("%d %d %d\n", tmatrix[i].row, tmatrix[i].col, tmatrix[i].value);
	printf("\n\n");

	PrintMatrix(tmatrix);
	
	return 0;
}