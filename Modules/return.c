// write me c code that takes a string cli argument as input and returns the string in normal order

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
	printf("Usage: %s <string>\n", argv[0]);
	return 1;
    }
    printf("%s\n", argv[1]);
    return 0;
}

// finished.
