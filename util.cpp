#include "util.h"
#include "stdio.h"
#include <cstdio>

/**
* Utility class providing interface functionality
* 3/8/19
* Nic Breuer
*/

// This gets all veriables of the next command
char util::nextCommand()
{
	char c;
	while (1) {
		scanf_s("%c", &c);
		if (c == ' ' || c == '\n' || c == '\t') {
			continue;
		}
		if (c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'w' || c == 'W' || c == 'c' || c == 'C') {
			break;
		}
		printf("ERROR: Invalid Command\n\n");
	}
	return c;
}

void util::DCommand(int *s, int *t, int *f)
{
	scanf_s("%d", s); scanf_s("%d", t); scanf_s("%d", f);
}

