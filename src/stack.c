#include <stdlib.h>
#include "stack.h"

void destroy(struct stack* head) {
    while (head != NULL) {
        struct stack *next = head->next;
        free(head);
        head = next;
    }
}

struct stack *init(int num) {
    struct stack *res = NULL;

    struct stack *temp = res;
    res = push(res, num);
    if (temp == res) {
        destroy(res);
    }

    return res;
}

struct stack *push(struct stack *head, int elem) {
    struct stack *new = NULL;
    new = (struct stack *) calloc(1, sizeof(struct stack));

    if (new != NULL) {
        new->value = elem;
        new->next = head;
    } else {
        new = head;
    }

    return new;
}

struct stack *pop(struct stack *head) {
    struct stack *res = NULL;
    if (head != NULL) {
        res = head->next;
        free(head);
    }

    return res;
}
