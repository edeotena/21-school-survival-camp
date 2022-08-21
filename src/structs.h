#ifndef SRC_STRUCTS_H_
#define SRC_STRUCTS_H_

#define ERROR 1
#define STOP_QUEUE 2
#define STOP_STACK 3

typedef struct stack_d {
    struct stack_d *next;
    double value;
} stack_d;

typedef struct stack {
    struct stack *next;
    char value;
} stack;

typedef struct queue {
    struct queue *next;
    char op;
    double value;
} queue;

void add(queue **head, char op, double value, int *code);
void get(queue **head, char *op, double *value, int *code);
void free_queue(queue **head);

char pop(stack **head, int *code);
void push(stack **head, char elem, int *code);
void free_stack(stack **head);

double pop_d(stack_d **head, int *code);
void push_d(stack_d **head, double elem, int *code);
void free_stack_d(stack_d **head);

#endif  // SRC_STRUCTS_H_
