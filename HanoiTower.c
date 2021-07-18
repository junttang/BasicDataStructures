#include <stdio.h>
// Hanoi Tower
void HanoiTower(int n, char from, char by, char to) {
	if (n == 0)
		return;
	HanoiTower(n - 1, from, to, by);
	printf("%d원반을 %c에서 %c로 옮긴다.\n", n, from, to);
	HanoiTower(n - 1, by, from, to);
}

int main(void) {
	int n;

	scanf("%d", &n);

	HanoiTower(n, 'A', 'B', 'C');

	return 0;
}