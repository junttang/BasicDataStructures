#include <stdio.h>
#include <string.h>

#define MAX_SIZE	50

void strnins(char *s, char *t, int i) {
	char str[MAX_SIZE];
	char *temp = str;

	if (i<0 && i>strlen(s)) {
		fprintf(stderr, "position is out of bounds.\n"); 
		exit(1);
	}

	if (!strlen(s)) 
		strcpy(s, t);
	else if (strlen(t)) {
		strncpy(temp, s, i);
		temp[i] = '\0';
		strcat(temp, t);
		strcat(temp, (s + i));
		strcpy(s, temp);
	}
}

int main(void) {
	char s[100] = "amobile";
	char t[] = "uto";

	strnins(s, t, 1);

	printf("%s", s);
	return 0;
}