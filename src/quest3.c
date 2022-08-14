// Copyright 2022 guinicyb@student.21-school.ru

#include <stdio.h>

#define ull unsigned long long

ull fibonacci(int num) {
    switch (num) {
        case 0:
            return 0;
            break;
        case 1:
            return 1;
            break;
        case 2:
            return 1;
            break;
    }
    return fibonacci(num - 1) + fibonacci(num - 2);
}

int main() {
    int num;
    if (scanf("%d", &num) != 1 || getchar() != '\n' || num < 0) {
        printf("n/a");
        return 0;
    }
    printf("%llu", fibonacci(num));
    return 0;
}
