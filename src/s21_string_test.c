#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

void s21_strlen_test();
void s21_strcmp_test();
void s21_strcpy_test();
void s21_strcat_test();
void s21_strchr_test();
void s21_strstr_test();
void s21_strtok_test();

int main() {
    #ifdef STRLEN
        s21_strlen_test();
    #endif

    #ifdef STRCMP
        s21_strcmp_test();
    #endif

    #ifdef STRCPY
        s21_strcpy_test();
    #endif

    #ifdef STRCAT
        s21_strcat_test();
    #endif

    #ifdef STRCHR
        s21_strchr_test();
    #endif

    #ifdef STRSTR
        s21_strstr_test();
    #endif

    #ifdef STRTOK
        s21_strtok_test();
    #endif
}

void s21_strlen_test() {
    printf("INPUT:\n%s\n", "test");
    printf("OUTPUT:\n%zu\n", s21_strlen("test"));
    printf("%s\n", (s21_strlen("test") == 4 ? "SUCCESS" : "FAIL"));

    printf("INPUT:\n%s\n", "");
    printf("OUTPUT:\n%zu\n", s21_strlen(""));
    printf("%s\n", (s21_strlen("") == 0 ? "SUCCESS" : "FAIL"));

    printf("INPUT:\n%s\n", "21");
    printf("OUTPUT:\n%zu\n", s21_strlen("21"));
    printf("%s\n", (s21_strlen("21") == 2 ? "SUCCESS" : "FAIL"));

    printf("INPUT:\n%s\n", "looooooooooooooooooooooong");
    printf("OUTPUT:\n%zu\n", s21_strlen("looooooooooooooooooooooong"));
    printf("%s\n", (s21_strlen("looooooooooooooooooooooong") == 26 ? "SUCCESS" : "FAIL"));

    printf("INPUT:\n%s\n", "Works!");
    printf("OUTPUT:\n%zu\n", s21_strlen("Works!"));
    printf("%s\n", (s21_strlen("Works!") == 6 ? "SUCCESS" : "FAIL"));
}

void s21_strcmp_test() {
    printf("INPUT:\n%s\n%s\n", "test", "test");
    printf("OUTPUT:\n%d\n", s21_strcmp("test", "test"));
    printf("%s\n", (s21_strcmp("test", "test") == 0 ? "SUCCESS" : "FAIL"));

    printf("INPUT:\n%s\n%s\n", "test1", "test3");
    printf("OUTPUT:\n%d\n", s21_strcmp("test1", "test3"));
    printf("%s\n", (s21_strcmp("test1", "test3") == '1' - '3' ? "SUCCESS" : "FAIL"));

    printf("INPUT:\n%s\n%s\n", "", "");
    printf("OUTPUT:\n%d\n", s21_strcmp("", ""));
    printf("%s\n", (s21_strcmp("", "") == 0 ? "SUCCESS" : "FAIL"));

    printf("INPUT:\n%s\n%s\n", "311", "309");
    printf("OUTPUT:\n%d\n", s21_strcmp("311", "309"));
    printf("%s\n", (s21_strcmp("311", "309") == '1' - '0' ? "SUCCESS" : "FAIL"));

    printf("INPUT:\n%s\n%s\n", "looong", "looongg");
    printf("OUTPUT:\n%d\n", s21_strcmp("looong", "looongg"));
    printf("%s\n", (s21_strcmp("looong", "looongg") == '\0' - 'g' ? "SUCCESS" : "FAIL"));

    printf("INPUT:\n%s\n%s\n", "test1", "test");
    printf("OUTPUT:\n%d\n", s21_strcmp("test1", "test"));
    printf("%s\n", (s21_strcmp("test1", "test") == '1' - '\0' ? "SUCCESS" : "FAIL"));
}

void s21_strcpy_test() {
    char *test_str = (char *) malloc((s21_strlen("test") + 1) * sizeof(char));
    if (test_str != NULL) {
        printf("INPUT:\n%s\n", "test");
        s21_strcpy(test_str, "test");
        printf("OUTPUT:\n%s\n", test_str);
        printf("%s\n", (s21_strcmp(test_str, "test") == 0 ? "SUCCESS" : "FAIL"));
        free(test_str);
    }

    test_str = (char *) malloc((s21_strlen("") + 1) * sizeof(char));
    if (test_str != NULL) {
        printf("INPUT:\n%s\n", "");
        s21_strcpy(test_str, "");
        printf("OUTPUT:\n%s\n", test_str);
        printf("%s\n", (s21_strcmp(test_str, "") == 0 ? "SUCCESS" : "FAIL"));
        free(test_str);
    }

    test_str = (char *) malloc((s21_strlen("another looong") + 1) * sizeof(char));
    if (test_str != NULL) {
        printf("INPUT:\n%s\n", "another looong");
        s21_strcpy(test_str, "another looong");
        printf("OUTPUT:\n%s\n", test_str);
        printf("%s\n", (s21_strcmp(test_str, "another looong") == 0 ? "SUCCESS" : "FAIL"));
        free(test_str);
    }
}

void s21_strcat_test() {
    char *test_str = (char *) malloc((s21_strlen("test") + s21_strlen("ing is cool") + 1) * sizeof(char));
    if (test_str != NULL) {
        s21_strcpy(test_str, "test");
        printf("INPUT:\n%s\n%s\n", "test", "ing is cool");
        test_str = s21_strcat(test_str, "ing is cool");
        printf("OUTPUT:\n%s\n", test_str);
        printf("%s\n", (s21_strcmp(test_str, "testing is cool") == 0 ? "SUCCESS" : "FAIL"));
        free(test_str);
    }

    test_str = (char *) malloc((s21_strlen("") + s21_strlen("") + 1) * sizeof(char));
    if (test_str != NULL) {
        s21_strcpy(test_str, "");
        printf("INPUT:\n%s\n%s\n", "", "");
        test_str = s21_strcat(test_str, "");
        printf("OUTPUT:\n%s\n", test_str);
        printf("%s\n", (s21_strcmp(test_str, "") == 0 ? "SUCCESS" : "FAIL"));
        free(test_str);
    }

    test_str = (char *) malloc((s21_strlen("second empty test") + s21_strlen("") + 1) * sizeof(char));
    if (test_str != NULL) {
        s21_strcpy(test_str, "second empty test");
        printf("INPUT:\n%s\n%s\n", "second empty test", "");
        test_str = s21_strcat(test_str, "");
        printf("OUTPUT:\n%s\n", test_str);
        printf("%s\n", (s21_strcmp(test_str, "second empty test") == 0 ? "SUCCESS" : "FAIL"));
        free(test_str);
    }
}

void s21_strchr_test() {
    char *test_str = (char *) malloc(s21_strlen("testing is cool") * sizeof(char));
    if (test_str != NULL) {
        printf("INPUT:\n%s\n%c\n", "testing is cool", 's');
        s21_strcpy(test_str, "testing is cool");
        char *found_str = s21_strchr(test_str, 's');
        printf("OUTPUT:\n%s\n", found_str);
        printf("%s\n", (s21_strcmp(found_str, "sting is cool") == 0 ? "SUCCESS" : "FAIL"));
        free(test_str);
    }

    test_str = (char *) malloc(s21_strlen("") * sizeof(char));
    if (test_str != NULL) {
        printf("INPUT:\n%s\n%c\n", "", '\0');
        s21_strcpy(test_str, "");
        char *found_str = s21_strchr(test_str, '\0');
        printf("OUTPUT:\n%s\n", found_str);
        printf("%s\n", (s21_strcmp(found_str, "") == 0 ? "SUCCESS" : "FAIL"));
        free(test_str);
    }

    test_str = (char *) malloc(s21_strlen("cann't find") * sizeof(char));
    if (test_str != NULL) {
        printf("INPUT:\n%s\n%c\n", "cann't find", '1');
        s21_strcpy(test_str, "cann't find");
        char *found_str = s21_strchr(test_str, '1');
        if (found_str == NULL) {
            printf("OUTPUT:\nNULL\n");
            printf("SUCCESS\n");
        } else {
            printf("OUTPUT:\n%s\n", found_str);
            printf("FAIL");
        }
        free(test_str);
    }
}

void s21_strstr_test() {
    char *test_str = (char *) malloc(s21_strlen("testing is cool") * sizeof(char));
    if (test_str != NULL) {
        printf("INPUT:\n%s\n%s\n", "testing is cool", "is");
        s21_strcpy(test_str, "testing is cool");
        char *found_str = s21_strstr(test_str, "is");
        printf("OUTPUT:\n%s\n", found_str);
        printf("%s\n", (s21_strcmp(found_str, "is cool") == 0 ? "SUCCESS" : "FAIL"));
        free(test_str);
    }

    test_str = (char *) malloc(s21_strlen("woorks!") * sizeof(char));
    if (test_str != NULL) {
        printf("INPUT:\n%s\n%s\n", "woorks!", "or");
        s21_strcpy(test_str, "woorks!");
        char *found_str = s21_strstr(test_str, "or");
        printf("OUTPUT:\n%s\n", found_str);
        printf("%s\n", (s21_strcmp(found_str, "orks!") == 0 ? "SUCCESS" : "FAIL"));
        free(test_str);
    }

    test_str = (char *) malloc(s21_strlen("") * sizeof(char));
    if (test_str != NULL) {
        printf("INPUT:\n%s\n%s\n", "", "");
        s21_strcpy(test_str, "");
        char *found_str = s21_strstr(test_str, "");
        if (found_str == NULL) {
            printf("OUTPUT:\nNULL\n");
            printf("SUCCESS\n");
        } else {
            printf("OUTPUT:\n%s\n", found_str);
            printf("FAIL");
        }
        free(test_str);
    }

    test_str = (char *) malloc(s21_strlen("Founded it") * sizeof(char));
    if (test_str != NULL) {
        printf("INPUT:\n%s\n%s\n", "Founded it", "ded");
        s21_strcpy(test_str, "Founded it");
        char *found_str = s21_strstr(test_str, "ded");
        printf("OUTPUT:\n%s\n", found_str);
        printf("%s\n", (s21_strcmp(found_str, "ded it") == 0 ? "SUCCESS" : "FAIL"));
        free(test_str);
    }

    test_str = (char *) malloc(s21_strlen("Founded it") * sizeof(char));
    if (test_str != NULL) {
        printf("INPUT:\n%s\n%s\n", "Founded it", "Founded it");
        s21_strcpy(test_str, "Founded it");
        char *found_str = s21_strstr(test_str, "Founded it");
        printf("OUTPUT:\n%s\n", found_str);
        printf("%s\n", (s21_strcmp(found_str, "Founded it") == 0 ? "SUCCESS" : "FAIL"));
        free(test_str);
    }
}

void s21_strtok_test() {
    char *test_str = (char *) malloc(s21_strlen("lets.test.it") * sizeof(char));
    if (test_str != NULL) {
        char* res[4] = {"lets", "test", "it"};
        printf("INPUT:\n%s\n%s\n", "lets.test.it", ".");
        s21_strcpy(test_str, "lets.test.it");
        printf("OUTPUT:\n");
        char *test_str_part = s21_strtok(test_str, ".");
        int code = 1, i = 0;;
        while (test_str_part != NULL) {
            printf("%s\n", test_str_part);
            if (s21_strcmp(res[i], test_str_part) != 0) {
                code = 0;
            }
            ++i;
            test_str_part = s21_strtok(NULL, ".");
        }
        printf("%s\n", (code == 1 ? "SUCCESS" : "FAIL"));
        free(test_str);
    }

    test_str = (char *) malloc(s21_strlen("---") * sizeof(char));
    if (test_str != NULL) {
        char* res[4] = {"---"};
        printf("INPUT:\n%s\n%s\n", "---", "-");
        s21_strcpy(test_str, "---");
        printf("OUTPUT:\n");
        char *test_str_part = s21_strtok(test_str, "-");
        int code = 1, i = 0;
        while (test_str_part != NULL) {
            printf("%s\n", test_str_part);
            if (s21_strcmp(res[i], test_str_part) != 0) {
                code = 0;
            }
            ++i;
            test_str_part = s21_strtok(NULL, ".");
        }
        printf("%s\n", (code == 1 ? "SUCCESS" : "FAIL"));
        free(test_str);
    }

    test_str = (char *) malloc(s21_strlen("wow;-it-;works!") * sizeof(char));
    if (test_str != NULL) {
        char* res[4] = {"wow", "it", "works!"};
        printf("INPUT:\n%s\n%s\n", "wow;-it-;works!", "-;");
        s21_strcpy(test_str, "wow;-it-;works!");
        printf("OUTPUT:\n");
        char *test_str_part = s21_strtok(test_str, "-;");
        int code = 1, i = 0;;
        while (test_str_part != NULL) {
            printf("%s\n", test_str_part);
            if (s21_strcmp(res[i], test_str_part) != 0) {
                code = 0;
            }
            ++i;
            test_str_part = s21_strtok(NULL, "-;");
        }
        printf("%s\n", (code == 1 ? "SUCCESS" : "FAIL"));
        free(test_str);
    }

    test_str = (char *) malloc(s21_strlen("cool") * sizeof(char));
    if (test_str != NULL) {
        char* res[4] = {"cool"};
        printf("INPUT:\n%s\n%s\n", "cool", "-");
        s21_strcpy(test_str, "cool");
        printf("OUTPUT:\n");
        char *test_str_part = s21_strtok(test_str, "-");
        int code = 1, i = 0;;
        while (test_str_part != NULL) {
            printf("%s\n", test_str_part);
            if (s21_strcmp(res[i], test_str_part) != 0) {
                code = 0;
            }
            ++i;
            test_str_part = s21_strtok(NULL, "-");
        }
        printf("%s\n", (code == 1 ? "SUCCESS" : "FAIL"));
        free(test_str);
    }

    test_str = (char *) malloc(s21_strlen("still cool") * sizeof(char));
    if (test_str != NULL) {
        char* res[4] = {"still ccool"};
        printf("INPUT:\n%s\n%s\n", "still ccool", "");
        s21_strcpy(test_str, "still ccool");
        printf("OUTPUT:\n");
        char *test_str_part = s21_strtok(test_str, "");
        int code = 1, i = 0;;
        while (test_str_part != NULL) {
            printf("%s\n", test_str_part);
            if (s21_strcmp(res[i], test_str_part) != 0) {
                code = 0;
            }
            ++i;
            test_str_part = s21_strtok(NULL, "");
        }
        printf("%s\n", (code == 1 ? "SUCCESS" : "FAIL"));
        free(test_str);
    }
}
