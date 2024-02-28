#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Please provide a file path as an argument.\n");
        return 1;
    }

    const char *filepath = argv[1];

    // Verify file exists
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: File not found: %s\n", filepath);
        return 1;
    }

    // ... Platform-specific clipboard operations would go here
    // linux
    // ... (previous code) ...


    // Copy file contents to clipboard using xclip
    char command[100]; 
    sprintf(command, "xclip -selection clipboard < %s", filepath);
    int status = system(command); 

    if (status != 0) { 
        fprintf(stderr, "Error: Failed to copy to clipboard.\n"); 
        return 1; 
    }

// ... (rest of the code) ... 


    fclose(file);
    printf("File contents copied to clipboard!\n"); // Placeholder 
    return 0;
}


