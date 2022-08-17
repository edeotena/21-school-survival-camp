#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

size_t s21_strlen(const char* str);
int s21_strcmp(const char *str1, const char *str2);
char* s21_strcpy(char *restrict str1, const char *restrict str2);
char* s21_strcat(char *restrict str1, const char *restrict str2);
char* s21_strchr(const char * str, int sym);
char* s21_strstr(const char * str1, const char *str2);
char* s21_strtok(char *restrict str, const char *restrict sep);

#endif  // SRC_S21_STRING_H_
