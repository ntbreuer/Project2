#include "util.h"
#include "stdio.h"
#include <cstdio>

/**
* Utility class providing interface functionality
* 4/11/19
* Nic Breuer
*/

// This gets all veriables of the next command
char util::nextCommand()
{
	char c;
	while (1) {
		scanf("%c", &c);
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
	scanf("%d", s); scanf("%d", t); scanf("%d", f);
}

