CC=gcc
BUILD=../build/
QUEST=Quest_
CFLAGS=-Wall -Wextra -Werror
S21_STR=s21_string.c
S21_STR_TEST=s21_string_test.c
QUEST8=text_processor.c

clean:
	rm -rf $(BUILD)*

build:
	$(CC) $(CFLAGS) $(S21_STR) $(S21_STR_TEST) -D S21_STR -D STRCMP -D STRCPY -D STRCAT -D STRCHR -D STRSTR -D STRTOK

strlen_tests:
	$(CC) $(CFLAGS) $(S21_STR) $(S21_STR_TEST) -o $(BUILD)$(QUEST)1 -D STRLEN

strcmp_tests:
	$(CC) $(CFLAGS) $(S21_STR) $(S21_STR_TEST) -o $(BUILD)$(QUEST)2 -D STRCMP

strcpy_tests:
	$(CC) $(CFLAGS) $(S21_STR) $(S21_STR_TEST) -o $(BUILD)$(QUEST)3 -D STRCPY

strcat_tests:
	$(CC) $(CFLAGS) $(S21_STR) $(S21_STR_TEST) -o $(BUILD)$(QUEST)4 -D STRCAT

strchr_tests:
	$(CC) $(CFLAGS) $(S21_STR) $(S21_STR_TEST) -o $(BUILD)$(QUEST)5 -D STRCHR

strstr_tests:
	$(CC) $(CFLAGS) $(S21_STR) $(S21_STR_TEST) -o $(BUILD)$(QUEST)6 -D STRSTR

strtok_tests:
	$(CC) $(CFLAGS) $(S21_STR) $(S21_STR_TEST) -o $(BUILD)$(QUEST)7 -D STRTOK

text_processor:
	$(CC) $(CFLAGS) $(S21_STR) $(QUEST8) -o $(BUILD)$(QUEST)8
