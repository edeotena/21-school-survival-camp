#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

int check_one_sym(const char* test) {
    int not_space = 0, code = 1;
    size_t size = s21_strlen(test);
    for (size_t i = 0; i < size && code == 1; ++i) {
        if (test[i] != ' ') {
            ++not_space;
            if (not_space > 1) {
                code = 0;
            }
        } else {
            not_space = 0;
        }
    }
    return code;
}

int main(int argc, char** argv) {
    if (argc == 2 && s21_strcmp(argv[1], "-w") == 0) {
        char sym;
        size_t width;
        int sc = scanf("%zu%c", &width, &sym);
        if ((sc == 1 && sym == 0) || (sc == 2 && sym == '\n')) {
            char *buff;
            size_t size;

            getline(&buff, &size, stdin);
            if (buff[s21_strlen(buff) - 1] == '\n') {
                buff[s21_strlen(buff) - 1] = '\0';
            }
            if (s21_strlen(buff) <= 100) {
                if (width != 1 || check_one_sym(buff) == 1) {
                    char* word = s21_strtok(buff, " ");
                    size = s21_strlen(word);
                    size_t not_first = 0;
                    size_t printed_word = 0, last_printed = 1;

                    while (word != NULL) {
                        if (not_first == 1) {
                            printf("\n");
                        } else {
                            not_first = 1;
                        }
                        size_t first_printed = 0;

                        size_t printed = 0;
                        if (last_printed == 2) {
                            last_printed = 0;
                        }
                        if (last_printed == 0) {
                            while (width - printed > 1 && size != printed_word) {
                                printf("%c", word[printed_word]);
                                ++printed;
                                ++printed_word;
                            }

                            if (size - printed_word > 1) {
                                printf("-");
                            } else {
                                if (size - printed_word == 1) {
                                    printf("%c", word[printed_word]);
                                }
                                last_printed = 2;
                                printed_word = 0;
                                word = s21_strtok(NULL, " ");
                                size = s21_strlen(word);
                            }
                        }

                        if (last_printed == 1 && word != NULL) {
                            if (width - printed >= size) {
                                printf("%s", word);
                                printed += size;
                                word = s21_strtok(NULL, " ");
                                size = s21_strlen(word);
                                first_printed = 1;
                            }
                        } else if (last_printed == 2 && word != NULL) {
                            if (width - printed >= size + 1) {
                                printf(" %s", word);
                                printed += size + 1;
                                word = s21_strtok(NULL, " ");
                                size = s21_strlen(word);
                                first_printed = 1;
                            }
                        }

                        if (last_printed != 0 && word != NULL) {
                            while (width - printed >= size + 1 && word != NULL) {
                                printf(" %s", word);
                                printed += size + 1;
                                word = s21_strtok(NULL, " ");
                                size = s21_strlen(word);
                            }

                            if (width < size) {
                                if (width - printed > 2 && first_printed == 1) {
                                    printf(" ");
                                    ++printed;
                                    last_printed = 0;
                                }

                                while (width - printed > 1) {
                                    printf("%c", word[printed_word]);
                                    ++printed_word;
                                    ++printed;
                                }

                                printf("-");
                                last_printed = 0;
                            }
                        }
                    }
                } else {
                    printf("n/a");
                }
            } else {
                printf("n/a");
            }
            free(buff);
        } else {
            printf("n/a");
        }
    } else {
        printf("n/a");
    }
}
