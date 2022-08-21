#include "structs.h"
#include <stdlib.h>

void add(queue **head, char op, double value, int *code) {
    if (*head == NULL) {
        *head = (queue *) calloc(1, sizeof(queue));
        if (*head ==  NULL) {
            *code = ERROR;
        } else {
            (*head)->op = op;
            (*head)->value = value;
            (*head)->next = NULL;
        }
    } else {
        queue *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = calloc(1, sizeof(queue));
        if (temp->next ==  NULL) {
            *code = ERROR;
        } else {
            temp->next->op = op;
            temp->next->value = value;
            temp->next->next = NULL;
        }
    }
}

void get(queue **head, char *op, double *value, int *code) {
    if (*head != NULL) {
        *op = (*head)->op;
        *value = (*head)->value;
        (*head) = (*head)->next;
    } else {
        *code = STOP_QUEUE;
    }
}

void free_queue(queue **head) {
    while (*head != NULL) {
        queue *next = (*head)->next;
        free(*head);
        *head = next;
    }
}

char pop(stack **head, int *code) {
    char res = 0;

    if (head != NULL) {
        res = (*head)->value;
        stack *temp = *head;
        *head = (*head)->next;
        if (*head == NULL) {
            *code = STOP_STACK;
        }
        free(temp);
    } else {
        *code = STOP_STACK;
    }

    return res;
}

void push(stack **head, char elem, int *code) {
    if (*head == NULL) {
        *head = (stack *) calloc(1, sizeof(stack));
        if (*head != NULL) {
            (*head)->value = elem;
            (*head)->next = NULL;
        } else {
            *code = ERROR;
        }
    } else {
        stack *next = (stack *) calloc(1, sizeof(stack));
        if (next != NULL) {
            next->next = (*head);
            next->value = elem;
            (*head) = next;
        } else {
            *code = ERROR;
        }
    }
}

void free_stack(stack **head) {
    while (*head != NULL) {
        stack *next = (*head)->next;
        free(*head);
        *head = next;
    }
}

double pop_d(stack_d **head, int *code) {
    double res = 0;

    if (*head != NULL) {
        res = (*head)->value;
        stack_d *temp = *head;
        *head = (*head)->next;
        if (*head == NULL) {
            *code = STOP_STACK;
        }
        free(temp);
    } else {
        *code = STOP_STACK;
    }

    return res;
}

void push_d(stack_d **head, double elem, int *code) {
    if (*head == NULL) {
        *head = (stack_d *) calloc(1, sizeof(stack_d));
        if (*head != NULL) {
            (*head)->value = elem;
            (*head)->next = NULL;
        } else {
            *code = ERROR;
        }
    } else {
        stack_d *next = (stack_d *) calloc(1, sizeof(stack_d));
        if (next != NULL) {
            next->next = (*head);
            next->value = elem;
            (*head) = next;
        } else {
            *code = ERROR;
        }
    }
}

void free_stack_d(stack_d **head) {
    while (*head != NULL) {
        stack_d *next = (*head)->next;
        free(*head);
        *head = next;
    }
}
