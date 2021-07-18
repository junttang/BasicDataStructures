#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// น้มุ 7575น๘ KMP
void failure(int failure[], int *pat) {
	int i, j, n = strlen(pat);
	failure[0] = -1;
	for (j = 1; j < n; j++) {
		i = failure[j - 1];
		while (pat[j] != pat[i + 1] && i >= 0)
			i = failure[i];
		if (pat[j] == pat[i + 1])
			failure[j] = i + 1;
		else
			failure[j] = -1;
	}
}

int pmatch(int failure[], int*string, int*pat, int lens, int lenp) {
	int i = 0, j = 0;
	while (i < lens && j < lenp) {
		if (string[i] == pat[j]) {
			i++;
			j++;
		}
		else if (j == 0)
			i++;
		else
			j = failure[j - 1] + 1;
	}
	return (j == lenp) ? 1 : 0;
}

int main(void) {
	int n, k;
	int*m[100];
	int size[100];
	int*pat;

	scanf("%d %d", &n, &k);

	for (int i = 0; i < n; i++) {
		int nOfM;
		scanf("%d", &nOfM);
		size[i] = nOfM;

		m[i] = (int*)malloc(sizeof(int)*nOfM);

		for (int j = 0; j < nOfM; j++)
			scanf("%d", &m[i][j]);
	}
	for (int i = 0; i <= size[0] - k; i++) {
		pat = (int*)malloc(sizeof(int)*k);
		for (int j = i; j < i + k; j++)
			pat[j - i] = m[0][j];
		for (int j = 0; j < k; j++)
			printf("%d ", pat[j]);
		printf("\n");
	}

	return 0;
}