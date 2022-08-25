#ifndef SRC_ARRAY_UTILS_H_
#define SRC_ARRAY_UTILS_H_

#define ERROR 1

void safe_free_str(char **str);
void safe_free_arr(int **arr);
int add_to_arr(int **res, int new, int* len, int *cap);

#endif  // SRC_ARRAY_UTILS_H_
