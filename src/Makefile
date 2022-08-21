CC = gcc
CFLAGS = -Wall -Werror -Wextra
QUEST = ../build/Quest_

print_module:
	$(CC) $(CFLAGS) print_module.c main_module_entry_point.c documentation_module.c -o $(QUEST)1

documentation_module:
	$(CC) $(CFLAGS) main_module_entry_point.c print_module.c documentation_module.c -o $(QUEST)2

bst_create_test:
	$(CC) $(CFLAGS) bst.c bst_create_test.c -o $(QUEST)3

bst_insert_test:
	$(CC) $(CFLAGS) bst.c bst_insert_test.c -o $(QUEST)4

bst_traverse_test:
	$(CC) $(CFLAGS) bst.c bst_traverse_test.c -o $(QUEST)5
