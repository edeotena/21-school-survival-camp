#ifndef SRC_DRAW_H_
#define SRC_DRAW_H_

#include "structs.h"

double *get_values(queue* func, double left, double right, int steps);
void print_graph(const double *coords, double up, double down,  int steps_x, int steps_y);

#endif  // SRC_DRAW_H_
