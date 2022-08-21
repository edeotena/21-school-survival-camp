#include <stdio.h>
#include "stack.h"

struct stack *test_push(struct stack *head);
struct stack *test_pop(struct stack *head);
void output_stack(struct stack *head);

int main() {
    struct stack *head = init(7);

    head = test_push(head);
    head = test_pop(head);

    destroy(head);
    return 0;
}

void output_stack(struct stack *head) {
    while (head != NULL && head->next != NULL) {
        printf("%d ", head->value);
        head = head->next;
    }

    if (head != NULL) {
        printf("%d\n", head->value);
    }
}

struct stack *test_push(struct stack *head) {
    printf("INPUT:\n%d\n", 5);
    head = push(head, 5);
    printf("OUTPUT:\n");
    output_stack(head);
    printf("%s\n", (head->value == 5 ? "SUCCESS" : "FALSE"));

    printf("INPUT:\n%d\n", 1);
    head = push(head, 1);
    printf("OUTPUT:\n");
    output_stack(head);
    printf("%s\n", (head->value == 1 ? "SUCCESS" : "FALSE"));

    printf("INPUT:\n%d\n", 0);
    head = push(head, 0);
    printf("OUTPUT:\n");
    output_stack(head);
    printf("%s\n", (head->value == 0 ? "SUCCESS" : "FALSE"));
    return head;
}

struct stack *test_pop(struct stack *head) {
    int code = 1;
    const int arr[] = {0, 1, 5, 7, 6, 5, 4, 3, 2, 1};
    int i = 0;
    while (head != NULL) {
        if (arr[i] != head->value) {
            code = 0;
        }
        ++i;
        printf("NUM: %d\n", head->value);
        head = pop(head);
    }
    printf("%s\n", (code == 1 ? "SUCCESS" : "FAIL"));
    return head;
}
