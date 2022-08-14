// Copyright 2022 guinicyb@student.21-school.ru

/*------------------------------------
    Здравствуй, человек!
    Чтобы получить ключ 
    поработай с комментариями.
-------------------------------------*/

#include <stdio.h>
#define NMAX 10
#define ERROR -1

int input(int *buffer, int *length);
void output(int *buffer, int length);
int sum_numbers(int *buffer, int length);
int find_numbers(int* buffer, int length, int number, int* numbers);
void output_error();
void output_num(int num);

/*------------------------------------
    Функция получает массив данных 
   3 через stdin.
    Выдает в stdout особую сумму
    и сформированный массив 
    специальных элементов
    (выбранных с помощью найденной суммы):
    это и будет частью ключа
-------------------------------------*/
int main() {
    int n, data[NMAX], code = 0;
    if (input(data, &n) != 0) {
        output_error();
        code = ERROR;
    }

    if (code == 0) {
        int num = sum_numbers(data, n);
        if (num != 1) {
            output_num(num);

            int res[NMAX];
            output(res, find_numbers(data, n, num, res));
        } else {
            printf("n/a");
        }
    }

    return 0;
}

int input(int *buffer, int *length) {
    int code = 0;
    if (scanf("%d", length) != 1 || *length < 0 || *length > NMAX) {
        code = ERROR;
    }

    if (*length != 0 && code == 0) {
        int *p = buffer;

        for (; p - buffer < *length - 1; ++p) {
            if (code == 0 && scanf("%d", p) != 1) {
                code = ERROR;
            }
        }

        if (code == 0) {
            char sym;
            int sc = scanf("%d%c", p, &sym);
            if (!((sc == 1 && !sym) || (sc == 2 && sym == '\n'))) {
                code = ERROR;
            }
        }
    }

    return code;
}

void output(int *buffer, int length) {
    int *p = buffer;
    for (; p - buffer < length - 1; ++p) {
        printf("%d ", *p);
    }

    if (length > 0) {
        printf("%d", *p);
    }
}

/*------------------------------------
    Функция должна находить
    сумму четных элементов 
    с 0-й позиции.
-------------------------------------*/
int sum_numbers(int *buffer, int length) {
    int sum = 0, found = 0;

    for (int i = 0; i < length; i++) {
        if (*(buffer + i) % 2 == 0) {
            found = 1;
            sum = sum + *(buffer + i);
        }
    }

    if (found == 0) {
        sum = 1;
    }

    return sum;
}

/*------------------------------------
    Функция должна находить
    все элементы, на которые нацело
    делится переданное число и
    записывает их в выходной массив.
-------------------------------------*/
int find_numbers(int* buffer, int length, int number, int* numbers) {
    int j = 0;

    for (int i = 0; i < length; ++i) {
        if (*(buffer + i) != 0 && number % *(buffer + i) == 0) {
            *(numbers + j) = *(buffer + i);
            ++j;
        }
    }

    return j;
}

void output_error() {
    printf("n/a");

    return;
}

void output_num(int num) {
    printf("%d\n", num);

    return;
}
