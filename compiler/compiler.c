#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h> 

// Function to recursively traverse and list files/folders
void list_directory(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        printf("%s\n", full_path); 

        if (entry->d_type == DT_DIR) {
            list_directory(full_path); 
        }
    }
    closedir(dir);
}

// Function to be executed by worker threads
void *compile_and_run_c_code(void *arg) {
    char *filename = (char *)arg;

    // Build the compile command (adjust compiler and flags as needed)
    char compile_command[1024];
    snprintf(compile_command, sizeof(compile_command), "gcc %s -o %s.out", filename, filename);
    system(compile_command);  // Execute compilation 

    // Build the run command
    char run_command[1024];
    snprintf(run_command, sizeof(run_command), "./%s.out", filename);
    system(run_command); // Execute the compiled program

    return NULL;
}


// int main() {
//     // ... Logic to get the initial state of the 'build' directory ... 

//     printf("Listing files in the current directory:\n");
//     list_directory(".");

//     // ... Multithreading logic to run C files using `compile_and_run_c_code` ...

//     // ... Logic to check the final state of the 'build' directory and compare ...

//     return 0;
// }



int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <build_directory>\n", argv[0]);
        return 1;
    }

    char *build_directory = argv[1];

    // ... Logic to get the initial state of the 'build_directory' ... 

    printf("Listing files in the current directory:\n");
    list_directory(".");

    // ... Multithreading logic to run C files using `compile_and_run_c_code` ...

    // ... Logic to check the final state of the 'build_directory' and compare ...

    return 0;
}













































// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <dirent.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <pthread.h> 

// // ... (list_directory and compile_and_run_c_code functions remain the same)

// int main(int argc, char *argv[]) {
//     if (argc < 2) {
//         fprintf(stderr, "Usage: %s <build_directory>\n", argv[0]);
//         return 1;
//     }

//     char *build_directory = argv[1];

//     // ... Logic to get the initial state of the 'build_directory' ... 

//     printf("Listing files in the current directory:\n");
//     list_directory(".");

//     // ... Multithreading logic to run C files using `compile_and_run_c_code` ...

//     // ... Logic to check the final state of the 'build_directory' and compare ...

//     return 0;
// }

