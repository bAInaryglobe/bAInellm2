#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <regex.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

#define MAX_PATH 1024
#define MAX_STRING 1024
#define MAX_LINE 1024

int is_dir(const char *path) {
    struct stat path_stat;
    if (stat(path, &path_stat) != 0) {
        perror("stat");
        return 0;
    }
    return S_ISDIR(path_stat.st_mode);
}

int is_file(const char *path) {
    struct stat path_stat;
    if (stat(path, &path_stat) != 0) {
        perror("stat");
        return 0;
    }
    return S_ISREG(path_stat.st_mode);
}

int is_feed(const char *path) {
    if (is_dir(path)) {
        DIR *dir;
        struct dirent *ent;
        
        if ((dir = opendir(path)) != NULL) {
            while ((ent = readdir(dir)) != NULL) {
                if (strcmp(ent->d_name, "Feed") == 0) {
                    closedir(dir);
                    return 1;
                }
            }
            closedir(dir);
        }
    }
    return 0;
}

int is_words(const char *path) {
    if (is_dir(path)) {
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir(path)) != NULL) {
            while ((ent = readdir(dir)) != NULL) {
                if (strcmp(ent->d_name, "words") == 0) {
                    closedir(dir);
                    return 1;
                }
            }
            closedir(dir);
        }
    }
    return 0;
}

int append_string(const char *path, const char *string) {
    FILE *file = fopen(path, "a");
    if (file == NULL) {
        perror("fopen");
        return 0;
    }
    fprintf(file, "%s\n", string);
    fclose(file);
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }
    char *string = argv[1];
    char cwd[MAX_PATH];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd");
        return 1;
    }
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(cwd)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
                continue;
            }
            char path[MAX_PATH];
            snprintf(path, sizeof(path), "%s/%s", cwd, ent->d_name);
            if (is_feed(path)) {
                if (is_words(path)) {
                    DIR *dir2;
                    struct dirent *ent2;
                    if ((dir2 = opendir(path)) != NULL) {
                        while ((ent2 = readdir(dir2)) != NULL) {
                            if (strcmp(ent2->d_name, ".") == 0 || strcmp(ent2->d_name, "..") == 0) {
                                continue;
                            }
                            char path2[MAX_PATH];
                            snprintf(path2, sizeof(path2), "%s/%s", path, ent2->d_name);
                            FILE *file = fopen(path2, "r+");
                            if (file == NULL) {
                                continue;
                            }
                            char line[MAX_LINE];
                            while (fgets(line, sizeof(line), file) != NULL) {
                                regex_t regex;
                                if (regcomp(&regex, string, REG_EXTENDED) != 0) {
                                    continue;
                                }
                                regmatch_t match;
                                if (regexec(&regex, line, 1, &match, 0) == 0) {
                                    if (match.rm_so != -1) {
                                        char *match_string = malloc(match.rm_eo - match.rm_so + 1);
                                        strncpy(match_string, line + match.rm_so, match.rm_eo - match.rm_so);
                                        match_string[match.rm_eo - match.rm_so] = '\0';
                                        if (strlen(match_string) > strlen(string) / 2) {
                                            char *temp = strdup(line);
                                            fseek(file, 0, SEEK_END);
                                            long size = ftell(file);
                                            long pos = ftell(file);
                                            while (pos > 0) {
                                                pos--;
                                                fseek(file, pos, SEEK_SET);
                                                if (fgetc(file) == '\n') {
                                                    break;
                                                }
                                            }
                                            if (pos == 0) {
                                                fseek(file, 0, SEEK_SET);
                                            }
                                            char *buffer = malloc(size - pos);
                                            if (buffer == NULL) {
                                                perror("malloc");
                                                continue;
                                            }
                                            if (fread(buffer, 1, size - pos, file) != size - pos) {
                                                perror("fread");
                                                continue;
                                            }
                                            fseek(file, pos, SEEK_SET);
                                            fprintf(file, "%s\n", string);
                                            fprintf(file, "%s", buffer);
                                            free(buffer);                        
                                            free(temp);
                                        }
                                        free(match_string);
                                    }
                                }
                                regfree(&regex);
                            }
                            fclose(file);
                        }
                        closedir(dir2);
                    }
                }
            }
        }
        closedir(dir);
    }
    return 0;
}   