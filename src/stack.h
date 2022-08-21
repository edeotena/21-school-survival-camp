#ifndef SRC_STACK_H_
#define SRC_STACK_H_

struct stack {
    int value;
    struct stack *next;
};

struct stack *init(int num);
struct stack *push(struct stack *head, int elem);
struct stack *pop(struct stack *head);
void destroy(struct stack* head);

#endif  // SRC_STACK_H_
