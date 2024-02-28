// write me c code that takes a command line string as user input and reverses the order of words, returning the reversed string.

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
	printf("Usage: %s <string>\n", argv[0]);
	return 1;
    }

    char *str = argv[1];
    int len = strlen(str);
    int i = 0;
    int j = len - 1;
    while (i < j) {
	char temp = str[i];
	str[i] = str[j];
	str[j] = temp;
	i++;
	j--;
    }

    i = 0;
    j = 0;
    while (i < len) {
	while (i < len && str[i] == ' ') {
	    i++;
	}
	j = i;
	while (j < len && str[j] != ' ') {
	    j++;
	}
	int k = i;
	int l = j - 1;
	while (k < l) {
	    char temp = str[k];
	    str[k] = str[l];
	    str[l] = temp;
	    k++;
	    l--;
	}
	i = j;
    }

    printf("%s\n", str);
    return 0;
}

// Path: reverse.c
