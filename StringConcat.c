#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Warning Point when concatenating strings
void strconcat(char *s, char *t) {
	char temp[100];
	strcpy(temp, s);
	strcat(temp, t);
	strcpy(s, temp);
}

void strnins(char *s, char *t, int index) {
	char temp[100];

	if (index < 0 || index > strlen(s)) {
		fprintf(stderr, "Index input error!\n");
		exit(-1);
	}

	if (index == strlen(s))
		strcat(s, t);
	else if (index == 0) {
		strcpy(temp, t);
		strcat(temp, s);
		strcpy(s, temp);
	}
	else {
		strncpy(temp, s, index);
		temp[index] = '\0';
		strcat(temp, t);
		strcat(temp, (s + index));
		strcpy(s, temp);
	}
}

int main(void) {
	char s[100] = "amobile";
	char t[] = "uto";
	char u[] = "rainbow";

	strconcat(s, t);
	printf("%s", s);

	return 0;
}