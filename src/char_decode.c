// Copyright 2022 guinicyb@student.21-school.ru

#include <stdio.h>

#define CHAR_LIMIT 255
#define MIN_HEX 16

int hex(int a) {
    if (a >= 'A') {
        return a - 'A' + 10;
    }
    return a - '0';
}

int encode() {
    int letter = getchar(), last_char;

    if (letter == '\n') {
        return 0;
    }

    int space_counter = 0;

    while (letter != '\n') {
        if (space_counter == 0) {
            if (letter < MIN_HEX || letter > CHAR_LIMIT) {
                return 1;
            }
        } else {
            if (letter != ' ') {
                return 1;
            }

            printf("%X ", last_char);
        }

        space_counter = (space_counter + 1) % 2;
        last_char = letter;
        letter = getchar();
    }

    if (space_counter != 1) {
        return 1;
    }
    printf("%X", last_char);

    return 0;
}

int decode() {
    int letter = getchar(), res;

    if (letter == '\n') {
         return 0;
    }

    int space_counter = 0;
    while (letter != '\n') {
        if (space_counter > 1) {
            if (letter != ' ') {
                return 1;
            }

            printf("%c ", res);
            res = 0;
        } else {
            if ((letter < '0' || letter > '9') && (letter < 'A' || letter > 'Z')) {
                return 1;
            }
            res *= 16;
            res += hex(letter);
        }
        space_counter = (space_counter + 1) % 3;
        letter = getchar();
    }

    if (res < MIN_HEX) {
        return 1;
    }
    printf("%c", res);

    return 0;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("n/a");
        return 0;
    }

    if ((argv[1][0] != '1' && argv[1][0] != '0') || argv[1][1] != '\0') {
        printf("n/a");
        return 0;
    }

    if (argv[1][0] == '0') {
        int code = encode();
        if (code != 0) {
            printf("n/a");
        }
        return 0;
    }

    int code = decode();
    if (code != 0) {
        printf("n/a");
    }
    return 0;
}
