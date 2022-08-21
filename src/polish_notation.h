#ifndef SRC_POLISH_NOTATION_H_
#define SRC_POLISH_NOTATION_H_

#include "structs.h"

queue *make_rpn(queue *queue_to_rpn);
double calculate(queue *func, double x, int *code_error);

#endif  // SRC_POLISH_NOTATION_H_
