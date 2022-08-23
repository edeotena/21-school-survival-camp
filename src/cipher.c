#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "des.h"

#ifdef LOG
#include "logger.h"
#endif

#define ERROR (-1)

void read_file(char **file_name, int *code);
void write_file(const char *file_name, const char *str);
void flush_stdin();
char *handle_one(int *code);
void handle_two(char *file_name, int *code);
void handle_three(int shift);
void handle_four();
void handle_dir_files(char *dir, int shift, int type);
void handle_c_file_caesar(char *file_name, int shift);
void handle_header(char *file_name);
void remove_end_line(char *str, size_t len);
void safe_free(char *str);
int read_act(int *act);
unsigned char cipher_caesar(unsigned char ch, int key);
void handle_c_file(char *file_name);

int main() {
#ifdef LOG
    FILE *logger = NULL;
    char *logger_name = NULL;
    size_t cap, len = getline(&logger_name, &cap, stdin);
    remove_end_line(logger_name, len);
    while (logger_name == NULL || logger == NULL) {
        if (logger_name != NULL) {
            logger = log_init(logger_name);
        }
        if (logger != NULL) {
            logcat(logger, "new logger", debug);
            free(logger_name);
        } else {
            printf("n/a\n");
            len = getline(&logger_name, &cap, stdin);
            remove_end_line(logger_name, len);
        }
    }
#endif
    int code, act = 0;
    char *file_name = NULL;
    code = read_act(&act);
    while (act != -1) {
        if (code == 0) {
            if (act == 1) {
#ifdef LOG
                logcat(logger, "file read", trace);
#endif
#ifdef LOG
                logcat(logger, "last filename free", warning);
#endif
                safe_free(file_name);
#ifdef LOG
                logcat(logger, "opening file", info);
#endif
                file_name = handle_one(&code);
                if (code != ERROR) {
                    printf("\n");
                }
            } else if (act == 2) {
                code = 0;
#ifdef LOG
                logcat(logger, "adding to file", trace);
#endif
                handle_two(file_name, &code);
            } else if (act == 3) {
                int shift = 0;
#ifdef LOG
                logcat(logger, "waiting for shift input", info);
#endif
                code = read_act(&shift);
                if (code == 0) {
#ifdef LOG
                    logcat(logger, "start cipher", warning);
#endif
                    handle_three(shift);
                }
                code = 0;
            } else if (act == 4) {
                handle_four();
            } else {
#ifdef LOG
                logcat(logger, "wrong action", error);
#endif
                printf("n/a\n");
            }
        } else {
#ifdef LOG
            logcat(logger, "wrong input", error);
#endif
            printf("n/a\n");
#ifdef LOG
            logcat(logger, "buffer flush", warning);
#endif
            flush_stdin();
        }
#ifdef LOG
        logcat(logger, "get next action", trace);
#endif
        code = read_act(&act);
    }

#ifdef LOG
    logcat(logger, "logger close", debug);
    log_close(logger);
#endif
    safe_free(file_name);

    return 0;
}

unsigned char cipher_caesar(unsigned char ch, int key) {
    if (ch >= 'a' && ch <= 'z') {
        ch = ch + (key % 26);
        if (ch > 'z') {
            ch = 'a'- 1 + (ch - 'z');
        } else if (ch < 'a') {
            ch = 'z' + 1 - 'a' + ch;
        }
    } else if (ch >= 'A' && ch <= 'Z') {
        ch = ch + (key % 26);
        if (ch > 'Z') {
            ch = 'A'- 1 + (ch - 'Z');
        } else if (ch < 'A') {
            ch = 'Z' + 1 - 'A' + ch;
        }
    }
    return ch;
}

void handle_dir_files(char *dir, int shift, int type) {
    DIR *directory;
    directory = opendir(dir);
    if (directory != NULL) {
        struct dirent *dirs;
        while ((dirs = readdir(directory)) != NULL) {
            size_t len = strlen(dirs->d_name);
            if (len > 2 && dirs->d_name[len - 1] == 'c' && dirs->d_name[len - 2] == '.') {
                char *temp = (char *)calloc(len + 1 + strlen(dir), sizeof(char));
                if (temp != NULL) {
                    strcat(temp, dir);
                    if (dir[strlen(dir) - 1] != '/') {
                        strcat(temp, "/");
                    }
                    strcat(temp, dirs->d_name);
                    if (type == 1) {
                        handle_c_file_caesar(temp, shift);
                    } else {
                        handle_c_file(temp);
                    }
                    free(temp);
                }
            } else if (len > 2 && dirs->d_name[len - 1] == 'h' && dirs->d_name[len - 2] == '.') {
                char *temp = (char *)calloc(len + 1 + strlen(dir), sizeof(char));
                if (temp != NULL) {
                    strcat(temp, dir);
                    if (dir[strlen(dir) - 1] != '/') {
                        strcat(temp, "/");
                    }
                    strcat(temp, dirs->d_name);
                    handle_header(temp);
                    free(temp);
                }
            }
        }
        closedir(directory);
    } else {
        printf("n/a\n");
    }
}

void handle_header(char *file_name) { fclose(fopen(file_name, "w")); }

void handle_c_file(char *file_name) {
    fclose(fopen("cipher.txt", "wb+"));
    create16Keys();
    long int n = findFileSize(file_name) / 8;
    convertCharToBit(n, file_name);
    encrypt(n);
    rename("cipher.txt", file_name);
}

void handle_c_file_caesar(char *file_name, int shift) {
    char *copy = (char *)calloc(strlen(file_name) + 1, sizeof(char));
    if (copy != NULL) {
        strcpy(copy, file_name);
        copy[strlen(copy)] = '~';
        FILE *real = fopen(file_name, "r");
        if (real != NULL) {
            FILE *file = fopen(copy, "w");
            if (file != NULL) {
                char c = (char)fgetc(real);
                while (c != EOF) {
                    fputc(cipher_caesar(c, shift), file);
                    c = (char)fgetc(real);
                }
                fclose(file);
            }
            rename(copy, file_name);
            fclose(real);
        }
        free(copy);
    }
}

char *handle_one(int *code) {
    char *file_name = NULL;

    size_t cap = 0, len = getline(&file_name, &cap, stdin);
    remove_end_line(file_name, len);

    read_file(&file_name, code);

    return file_name;
}

void handle_two(char *file_name, int *code) {
    char *str = NULL;
    size_t cap = 0;
    getline(&str, &cap, stdin);

    write_file(file_name, str);

    safe_free(str);

    if (file_name != NULL) {
        read_file(&file_name, code);
    }
}

void handle_three(int shift) {
    char *dir = NULL;
    size_t cap = 0, len = getline(&dir, &cap, stdin);
    remove_end_line(dir, len);

    handle_dir_files(dir, shift, 1);
    safe_free(dir);
}

void handle_four() {
    char *dir = NULL;
    size_t cap = 0, len = getline(&dir, &cap, stdin);
    remove_end_line(dir, len);

    handle_dir_files(dir, 0, 0);
    safe_free(dir);
}

void read_file(char **file_name, int *code) {
    FILE *file = fopen(*file_name, "r");

    if (file != NULL) {
        char sym = 0;
        int is_empty = 1;
        while (sym != EOF) {
            sym = (char)fgetc(file);
            if (sym != EOF) {
                printf("%c", sym);
                is_empty = 0;
            }
        }
        if (is_empty == 1) {
            printf("n/a\n");
            *code = ERROR;
        }
        fclose(file);
    } else {
        printf("n/a\n");
        *code = ERROR;
        free(*file_name);
        (*file_name) = NULL;
    }
}

void write_file(const char *file_name, const char *str) {
    if (file_name != NULL) {
        FILE *file = fopen(file_name, "a");
        if (file != NULL) {
            fprintf(file, str);
            fclose(file);
        } else {
            printf("n/a\n");
        }
    } else {
        printf("n/a\n");
    }
}

void flush_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void remove_end_line(char *str, size_t len) {
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void safe_free(char *str) {
    if (str != NULL) {
        free(str);
    }
}

int read_act(int *act) {
    char sym = 0;
    int sc = scanf("%d%c", act, &sym), code = 0;
    if (!((sc == 1 && sym == 0) || (sc == 2 && sym == '\n'))) {
        code = ERROR;
    }
    return code;
}
