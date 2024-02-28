// write me c code that creates a 'history' dir3ctory in the directory before the current directory, if it does not exist

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    int check;
    check = mkdir("../History", 0777);
    if (!check) {
	printf("Directory created\n");
    } else {
	printf("Unable to create directory\n");
    }
    return 0;
}


