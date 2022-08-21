#include <stdio.h>
#include "list.h"

struct node *test_remove_door(struct node *head);
void test_add_door(struct node *head);
void output_list(struct node *head);

int main() {
    struct door door = {0, 1};

    struct node *head = init(&door);

    test_add_door(head);
    head = test_remove_door(head);

    destroy(head);
    return 0;
}

void output_list(struct node *head) {
    while (head != NULL) {
        printf("%d, %d\n", head->door.id, head->door.status);
        head = head->next;
    }
}

struct node *test_remove_door(struct node *head) {
    printf("INPUT:\n");
    printf("0, 1\n");
    head = remove_door(find_door(0, head), head);
    printf("OUTPUT:\n");
    output_list(head);
    printf("%s\n", (find_door(0, head) == NULL ? "SUCCESS" : "FAIL"));

    printf("INPUT:\n");
    printf("4, 0\n");
    head = remove_door(find_door(4, head), head);
    printf("OUTPUT:\n");
    output_list(head);
    printf("%s\n", (find_door(4, head) == NULL ? "SUCCESS" : "FAIL"));

    printf("INPUT:\n");
    printf("5, 0\n");
    head = remove_door(find_door(5, head), head);
    printf("OUTPUT:\n");
    output_list(head);
    printf("%s\n", (find_door(5, head) == NULL ? "SUCCESS" : "FAIL"));
    return head;
}

void test_add_door(struct node *head) {
    printf("INPUT:\n");
    printf("3, 1\n");
    struct door temp;
    temp.id = 3;
    temp.status = 1;
    struct node *added = add_door(head, &temp);
    printf("OUTPUT:\n");
    output_list(head);
    printf("%s\n", (find_door(3, head) != NULL ? "SUCCESS" : "FAIL"));

    printf("INPUT:\n");
    printf("4, 0\n");
    temp.id = 4;
    temp.status = 0;
    add_door(added, &temp);
    printf("OUTPUT:\n");
    output_list(head);
    printf("%s\n", (find_door(4, head) != NULL ? "SUCCESS" : "FAIL"));

    printf("INPUT:\n");
    printf("5, 0\n");
    temp.id = 5;
    temp.status = 0;
    add_door(find_door(4, head), &temp);
    printf("OUTPUT:\n");
    output_list(head);
    printf("%s\n", (find_door(5, head) != NULL ? "SUCCESS" : "FAIL"));
}
