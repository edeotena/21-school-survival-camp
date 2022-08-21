#include "polish_notation.h"
#include <math.h>
#include <stdlib.h>

#define PRODUCED 4

int get_priority(char op) {
    int res = 0;
    if (op == '+' || op == '-') {
        res = 1;
    } else if (op == '*' || op == '/') {
        res = 2;
    } else if (op == '^') {
        res = 3;
    } else if (op == 's' || op == 'c' || op == 't' || op == 'g' || op == 'q' || op == 'l' || op == '~') {
        res = 4;
    }
    return res;
}

void handle_bin(queue **res, stack **operations, char op, int *code, int *operands) {
    while (*operations != NULL && get_priority((*operations)->value) >= get_priority(op)) {
        char p = pop(operations, code);
        if (p == '+' || p == '-' || p == '*' || p == '/' || p == '^') {
            --(*operands);
        }
        add(res, p, 0, code);
    }

    push(operations, op, code);
}

void handle_bracket(queue **res, stack **operations, int* code, int *operands) {
    while (*operations != NULL && (*operations)->value != '(' && *code != STOP_QUEUE) {
        char p = pop(operations, code);
        if (p == '+' || p == '-' || p == '*' || p == '/' || p == '^') {
            --(*operands);
        }
        add(res, p, 0, code);
    }
    if (*operations == NULL || (*operations)->value != '(') {
        *code = ERROR;
    } else {
        pop(operations, code);
    }
}

void flush_stack(queue **res, stack **operations, char op, int *code, int *operands) {
    while (*operations != NULL && *code == STOP_QUEUE) {
        op = pop(operations, code);
        if (op != '(') {
            if (op == '+' || op == '-' || op == '*' || op == '/' || op == '^') {
                --(*operands);
            }
            add(res, op, 0, code);
        } else {
            *code = ERROR;
        }
    }
}

queue *make_rpn(queue *queue_to_rpn) {
    int code = 0, operands = 0, scope_open = 1;
    double value;
    char op;
    get(&queue_to_rpn, &op, &value, &code);
    queue *res = NULL;
    stack *operations = NULL;
    while (code != STOP_QUEUE && code != ERROR) {
        if (op == 0 || op == 'x') {
            add(&res, op, value, &code);
            ++operands;
            scope_open = 0;
        } else if (op == 's' || op == 'c' || op == 't' || op == 'g' ||
                   op == 'q' || op == 'l' || op == '(' || op == '~') {
            push(&operations, op, &code);
            scope_open = (op == '(' ? 1 : 0);
        } else if (op == ')') {
            if (scope_open != 1) {
                handle_bracket(&res, &operations, &code, &operands);
                scope_open = 0;
            } else {
                code = ERROR;
            }
        } else if (op == '+' || op == '-' || op == '*' || op == '/' || op == '^') {
            handle_bin(&res, &operations, op, &code, &operands);
            scope_open = 0;
        }
        if (code != ERROR) {
            get(&queue_to_rpn, &op, &value, &code);
        }
    }
    if (code == STOP_QUEUE) {
        flush_stack(&res, &operations, op, &code, &operands);
    }
    if (code == ERROR || operands != 1) {
        free_queue(&res);
        free_stack(&operations);
    }

    return res;
}

int produce_un(stack_d **func, double x, char op) {
    int code = 0;
    if (op == 's') {
        code = PRODUCED;
        push_d(func, sin(x), &code);
    } else if (op == 'c') {
        code = PRODUCED;
        push_d(func, cos(x), &code);
    } else if (op == 't') {
        code = PRODUCED;
        push_d(func, tan(x), &code);
    } else if (op == 'g') {
        code = PRODUCED;
        push_d(func, cos(x) / sin(x), &code);
    } else if (op == 'q') {
        code = PRODUCED;
        push_d(func, sqrt(x), &code);
    } else if (op == 'l') {
        code = PRODUCED;
        push_d(func, log(x), &code);
    } else if (op == '~') {
        code = PRODUCED;
        push_d(func, -x, &code);
    }
    return code;
}

int produce_bin(stack_d **func, double fir, double sec, char op) {
    int code = 0;
    if (op == '-') {
        code = PRODUCED;
        push_d(func, sec - fir, &code);
    } else if (op == '+') {
        code = PRODUCED;
        push_d(func, sec + fir, &code);
    } else if (op == '*') {
        code = PRODUCED;
        push_d(func, sec * fir, &code);
    } else if (op == '/') {
        code = PRODUCED;
        push_d(func, sec / fir, &code);
    } else if (op == '^') {
        code = PRODUCED;
        double real_pow = pow(sec, fir);
        if (sec < 0 && fir < 0) {
            real_pow = -real_pow;
        }
        push_d(func, real_pow, &code);
    }
    return code;
}

double calculate(queue *func, double x, int *code_error) {
    int code = 0;
    *code_error = 0;
    double value;
    char op;
    stack_d *temp = NULL;
    get(&func, &op, &value, &code);
    while (code != STOP_QUEUE && code != ERROR) {
        if (op == 0) {
            push_d(&temp, value, &code);
        } else if (op == 'x') {
            push_d(&temp, x, &code);
        } else {
            double fir;
            if (temp != NULL) {
                fir = pop_d(&temp, &code);
                code = produce_un(&temp, fir, op);
            } else {
                code = ERROR;
            }
            if (code == 0 && temp != NULL) {
                double sec = pop_d(&temp, &code);
                code = produce_bin(&temp, fir, sec, op);
            }
        }
        if (code != ERROR) {
            get(&func, &op, &value, &code);
        }
    }
    double res = 0;
    if (temp == NULL || code == ERROR) {
        free_stack_d(&temp);
        code = ERROR;
        *code_error = ERROR;
    } else {
        res = pop_d(&temp, &code);
    }

    return res;
}
