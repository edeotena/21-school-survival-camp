// Copyright 2022 guinicy@student.21-school.ru

#include <stdio.h>

#define LEN 101
#define ERROR -1

void sum_cases(int *buff1, int start1, int *buff2, int start2, int* result,
              int* result_start);
void sum(int *buff1, int start1, int *buff2, int start2, int *result,
         int *result_start);
void sub_cases(int *buff1, int start1, int *buff2, int start2, int *result,
         int *result_start);
void sub(int *buff1, int start1, int *buff2, int start2, int *result,
         int *result_start);
int is_neg(const int *buff);
int is_pos(const int *buff);
void change_sign(int *buff, int start);
int is_bigger(const int *a, int a_st, const int *b, int b_st);
int input(int *buff, int *start);
void output(const int *buffet, int start);
void output_error();
void output_line();

int main() {
    int data1[LEN], start1;

    if (input(data1, &start1) != 0) {
        output_error();
    } else {
        int data2[LEN], start2;

        if (input(data2, &start2) != 0) {
            output_error();
        } else {
            int res1[LEN], res_start1;
            sum_cases(data1, start1, data2, start2, res1, &res_start1);
            output(res1, res_start1);

            output_line();

            if (is_bigger(data1, start1, data2, start2) != 0) {
                int res2[LEN], res_start2;
                sub_cases(data1, start1, data2, start2, res2, &res_start2);
                output(res2, res_start2);
            } else {
                output_error();
            }
        }
    }

    return 0;
}

int input(int *buff, int* start) {
    int code = 0;
    *start = LEN;

    for (int i = LEN; i >= 0 && code == 0; --i) {
        char sym;

        if (scanf("%d%c", &buff[i], &sym) != 2 || (buff[i] < 0 &&
            i != LEN) || buff[i] > 9 || sym != ' ' || buff[i] < -9) {
            if ((buff[i] < 0 && i != LEN) || buff[i] < -9 ||
                buff[i] > 9 || (sym && sym != '\n')) {
                code = ERROR;
            }
            code = (code == 0 ? 1 : code);
        }
        if (code == 0) {
            --(*start);
        }
    }

    code = (code == 1 ? 0 : code);

    return code;
}

void output(const int *buff, int start) {
    int skip_zeros = 0;
    int i = LEN;
    for (; i >= start + 1; --i) {
        if (skip_zeros == 1 || buff[i] != 0) {
            printf("%d ", buff[i]);
            skip_zeros = 1;
        }
    }

    if (skip_zeros == 1 || buff[i] != 0) {
        printf("%d", buff[i]);
    } else {
        printf("0");
    }
}

void change_sign(int *buff, int start) {
    for (int *p = buff + LEN; p >= buff + start; --p) {
        if (*p != 0) {
            *p *= -1;
            return;
        }
    }
}

int is_neg(const int *buff) {
    int code = 0, break_code = 0;
    for (int i = LEN; i >= 0 && code == 0 && break_code == 0; --i) {
        if (buff[i] < 0) {
            code = 1;
        } else if (buff[i] > 0) {
            break_code = 1;
        }
    }

    return code;
}

int is_pos(const int *buff) {
    return (is_neg(buff) == 1 ? 0 : 1);
}

int is_bigger(const int *a, int a_st, const int *b, int b_st) {
    int i = LEN, j = LEN;
    for (; i >= a_st; --i) {
        if (*(a + i) != 0) {
            break;
        }
    }

    for (; j >= b_st; --j) {
        if (*(b + j) != 0) {
            break;
        }
    }

    if (i - a_st == j - b_st) {
        for (i = LEN; i >= a_st; --i) {
            if (*(a + i) != *(b + i)) {
                return (*(a + i) > *(b + i) ? 1 : 0);
            }
        }
        return 2;
    }

    return (i - a_st > j - b_st ? 1 : 0);
}

void sum_cases(int *buff1, int start1, int *buff2, int start2, int* result,
              int* result_start) {
    if (is_neg(buff1) == 1 && is_neg(buff2) == 1) {
        change_sign(buff1, start1);
        change_sign(buff2, start2);

        sum(buff1, start1, buff2, start2, result, result_start);

        change_sign(buff1, start1);
        change_sign(buff2, start2);
        change_sign(result, *result_start);

    } else if (is_pos(buff1) == 1 && is_neg(buff2) == 1) {
        change_sign(buff2, start2);

        sub(buff1, start1, buff2, start2, result, result_start);

        change_sign(buff2, start2);

    } else if (is_pos(buff2) == 1 && is_neg(buff1) == 1) {
        change_sign(buff1, start1);

        sub(buff2, start2, buff1, start1, result, result_start);

        change_sign(buff1, start1);
    } else {
        sum(buff1, start1, buff2, start2, result, result_start);
    }
}

void sum(int *buff1, int start1, int *buff2, int start2, int *result,
         int *result_start) {
    int last_proc = 0;
    int index = 0;
    *result_start = (start1 < start2 ? start1 : start2);

    for (int i = *result_start; i <= LEN; ++i) {
        int digit = 0, first_end = 0, second_end = 0;

        if (start1 + index <= LEN) {
            digit += *(buff1 + start1 + index);
        }

        if (start1 + index >= LEN) {
            first_end = 1;
        }

        if (start2 + index <= LEN) {
            digit += *(buff2 + start2 + index);
        }

        if (start2 + index >= LEN) {
            second_end = 1;
        }

        *(result + i) = (digit + last_proc) % 10;
        last_proc = (digit + last_proc) / 10;
        ++index;

        if (first_end == 1 && second_end == 1) {
            if (last_proc > 0) {
                --(*result_start);

                for (int j = *result_start; j < LEN; ++j) {
                    *(result + j) = *(result + j + 1);
                }

                *(result + LEN) = last_proc;
            }
            return;
        }
    }
}

void sub_cases(int *buff1, int start1, int *buff2, int start2, int *result,
         int *result_start) {
    if (is_neg(buff1) == 1 && is_pos(buff2) == 1) {
        change_sign(buff1, start1);

        sum(buff1, start1, buff2, start2, result, result_start);

        change_sign(buff1, start1);
        change_sign(result, *result_start);

    } else if (is_neg(buff2) == 1 && is_pos(buff1) == 1) {
        change_sign(buff2, start2);

        sum(buff1, start1, buff2, start2, result, result_start);

        change_sign(buff2, start2);

    } else if (is_neg(buff1) == 1 && is_neg(buff2) == 1) {
        change_sign(buff1, start1);
        change_sign(buff2, start2);

        sub(buff1, start1, buff2, start2, result, result_start);

        change_sign(buff1, start1);
        change_sign(buff2, start2);
        change_sign(result, *result_start);

    } else {
        sub(buff1, start1, buff2, start2, result, result_start);
    }
}


void sub(int *buff1, int start1, int *buff2, int start2, int *result,
         int *result_start) {
    int biggest = is_bigger(buff1, start1, buff2, start2);
    if (biggest == 2) {
        *(result + LEN) = 0;
        *result_start = LEN;
        return;
    }
    int changed = 0;
    if (biggest == 0) {
        changed = 1;
        int *tmp_p = buff2;
        buff2 = buff1;
        buff1 = tmp_p;
        int tmp = start1;
        start1 = start2;
        start2 = tmp;
    }

    *result_start = start1;
    int index = 0, last_proc = 0;

    for (int i = *result_start; i <= LEN; ++i) {
        int digit = 0, first_end = 0, second_end = 0;

        if (start1 + index <= LEN) {
            digit += *(buff1 + start1 + index);
        }

        if (start1 + index >= LEN) {
            first_end = 1;
        }

        if (start2 + index <= LEN) {
            digit -= *(buff2 + start2 + index);
        }

        if (start2 + index >= LEN) {
            second_end = 1;
        }

        digit -= last_proc;
        last_proc = 0;

        if (digit < 0) {
            digit += 10;
            last_proc = 1;
        }

        *(result + i) = digit;
        ++index;

        if (first_end == 1 && second_end == 1) {
            if (last_proc > 0) {
                --(*result_start);

                for (int j = *result_start; j < LEN; ++j) {
                    *(result + j) = *(result + j + 1);
                }
            }
            break;
        }
    }
    if (changed == 1) {
        change_sign(result, *result_start);
    }
}

void output_error() {
    printf("n/a");

    return;
}

void output_line() {
    printf("\n");

    return;
}
