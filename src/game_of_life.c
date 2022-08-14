#include <stdio.h>
#include <ncurses.h>

#define LIVE '*'
#define DEAD ' '
#define LEFT_BORDER 0
#define RIGHT_BORDER 80
#define UP_BORDER 0
#define DOWN_BORDER 25
#define TIME_STOP 2000000000
#define TIME_LIMIT_MIN 100
#define TIME_LIMIT_MAX 1000
#define TIME_CHANGE 1.5
#define USUALL 0
#define CURSES 1

void draw(char field[DOWN_BORDER][RIGHT_BORDER], int type);
void next_gen(char field[DOWN_BORDER][RIGHT_BORDER], char this_gen[DOWN_BORDER][RIGHT_BORDER]);
void copy_matrix(char field[DOWN_BORDER][RIGHT_BORDER], char copy[DOWN_BORDER][RIGHT_BORDER]);
int equal_field(char field[DOWN_BORDER][RIGHT_BORDER], char copy[DOWN_BORDER][RIGHT_BORDER]);
int get_neighbors(char field[DOWN_BORDER][RIGHT_BORDER], int x, int y);
void input(char field[DOWN_BORDER][RIGHT_BORDER]);
int is_empty(char field[DOWN_BORDER][RIGHT_BORDER]);
void reset_field(char field[DOWN_BORDER][RIGHT_BORDER]);
void increase_speed(int *time);
void decrease_speed(int *time);

int main() {
    int time_sleep = TIME_LIMIT_MAX, exit = 0, generations_count = 0;
    char field[DOWN_BORDER][RIGHT_BORDER], last_gen[DOWN_BORDER][RIGHT_BORDER];
    reset_field(field);
    reset_field(last_gen);

    input(field);
    // Перенаправление ввода на stdin
    if (freopen("/dev/tty", "r", stdin) == 0) {
        printf("Error while redirecting to stdin\n");
        exit = 1;
    }
    // Создание curses экрана
    initscr();
    // Не показывать ввод пользователя
    noecho();
    // Не показывать курсор
    curs_set(FALSE);

    while (is_empty(field) == 0 && exit == 0) {
        draw(field, CURSES);
        printw("    (Press 'q' to quit, 's' to make game slower and 'f' to make game faster)\n");

        timeout(time_sleep);
        char inp = getch();
        if (inp == 'q' || inp == 'Q') {
            exit = 1;
        } else if (inp == 's' || inp == 'S') {
            decrease_speed(&time_sleep);
        } else if (inp == 'f' || inp == 'F') {
            increase_speed(&time_sleep);
        }

        if (exit == 0) {
            copy_matrix(field, last_gen);
            next_gen(field, last_gen);
            if (equal_field(field, last_gen) == 1) {
                exit = 2;
            }
            ++generations_count;
        }
    }

    // Закрыть curses экран
    endwin();
    draw(field, USUALL);

    if (exit == 0) {
        printf("Next generation - empty field! Game over!\n");
    } else if (exit == 1) {
        printf("Quit pressed! Game over!\n");
    } else {
        printf("Only still lifes stayed! Game over\n");
    }
    printf("Passed generations count: %d", generations_count);

    return 0;
}

void draw(char field[DOWN_BORDER][RIGHT_BORDER], int type) {
    if (type == USUALL) {
        printf("\x1b[2J\x1b[H");
    } else if (type == CURSES) {
        clear();
    }
    for (int i = UP_BORDER - 1; i < DOWN_BORDER + 1; ++i) {
        for (int j = LEFT_BORDER - 1; j < RIGHT_BORDER + 1; ++j) {
            if (i == UP_BORDER - 1 || i == DOWN_BORDER) {
                if (type == USUALL) {
                    printf("%c", (j == LEFT_BORDER - 1 || j == RIGHT_BORDER ? '+' : '-'));
                } else if (type == CURSES) {
                    printw("%c", (j == LEFT_BORDER - 1 || j == RIGHT_BORDER ? '+' : '-'));
                }
            } else if (j == LEFT_BORDER - 1 || j == RIGHT_BORDER) {
                if (type == USUALL) {
                    printf("|");
                } else if (type == CURSES)  {
                    printw("|");
                }
            } else {
                if (type == USUALL) {
                    printf("%c", field[i][j]);
                } else if (type == CURSES)  {
                    printw("%c", field[i][j]);
                }
            }
        }

        if (type == USUALL) {
            printf("\n");
        } else if (type == CURSES)  {
            printw("\n");
        }
    }
}

void next_gen(char field[DOWN_BORDER][RIGHT_BORDER], char this_gen[DOWN_BORDER][RIGHT_BORDER]) {
    for (int i = UP_BORDER; i < DOWN_BORDER; ++i) {
        for (int j = LEFT_BORDER; j < RIGHT_BORDER; ++j) {
            int neighbors = get_neighbors(this_gen, i, j);
            if (neighbors == 3 || (field[i][j] == LIVE && neighbors == 2)) {
                field[i][j] = LIVE;
            } else {
                field[i][j] = DEAD;
            }
        }
    }
}

void copy_matrix(char field[DOWN_BORDER][RIGHT_BORDER], char copy[DOWN_BORDER][RIGHT_BORDER]) {
    for (int i = UP_BORDER; i < DOWN_BORDER; ++i) {
        for (int j = LEFT_BORDER; j < RIGHT_BORDER; ++j) {
            copy[i][j] = field[i][j];
        }
    }
}

int equal_field(char field[DOWN_BORDER][RIGHT_BORDER], char copy[DOWN_BORDER][RIGHT_BORDER]) {
    int code = 1;
    for (int i = UP_BORDER; i < DOWN_BORDER; ++i) {
        for (int j = LEFT_BORDER; j < RIGHT_BORDER; ++j) {
            if (copy[i][j] != field[i][j]) {
                code = 0;
            }
        }
    }
    return code;
}

int get_neighbors(char field[DOWN_BORDER][RIGHT_BORDER], int x, int y) {
    int neighbors = 0;
    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            int real_i = (i != -1 ? i % DOWN_BORDER : DOWN_BORDER - 1);
            int real_j = (j != -1 ? j % RIGHT_BORDER : RIGHT_BORDER - 1);
            if (field[real_i][real_j] == LIVE && (i != x || j != y)) {
                ++neighbors;
            }
        }
    }

    return neighbors;
}

void input(char field[DOWN_BORDER][RIGHT_BORDER]) {
    int stop = 1;
    do {
        draw(field, USUALL);
        printf("   Input x[%d; %d], y[%d; %d] to change (x;y) cell stage or -1 -1 to stop input:\n",
               LEFT_BORDER + 1, RIGHT_BORDER, UP_BORDER + 1, DOWN_BORDER);
        char sym = 0;
        int x, y, sc = scanf("%d %d%c", &x, &y, &sym);
        if (sc == 3 && sym == '\n' && x > LEFT_BORDER && x <= RIGHT_BORDER &&
            y > UP_BORDER && y <= DOWN_BORDER) {
            field[y - 1][x - 1] = (field[y - 1][x - 1] == DEAD ? LIVE : DEAD);
        } else if (sc == 3 && sym == '\n' && x == -1 && y == -1) {
            stop = 0;
        } else if (sc == 0) {
            int c;
           while ((c = getchar()) != '\n' && c != EOF) {}
        }
    } while (stop != 0);
}

int is_empty(char field[DOWN_BORDER][RIGHT_BORDER]) {
    int found = 1;
    for (int i = UP_BORDER; i < DOWN_BORDER; ++i) {
        for (int j = LEFT_BORDER; j < RIGHT_BORDER; ++j) {
            if (field[i][j] == LIVE) {
                found = 0;
            }
        }
    }

    return found;
}

void reset_field(char field[DOWN_BORDER][RIGHT_BORDER]) {
    for (int i = UP_BORDER; i < DOWN_BORDER; ++i) {
        for (int j = LEFT_BORDER; j < RIGHT_BORDER; ++j) {
            field[i][j] = DEAD;
        }
    }
}

void increase_speed(int *time) {
    if (*time == TIME_STOP) {
        *time = TIME_LIMIT_MAX;
    } else if (*time > TIME_LIMIT_MIN) {
        *time /= TIME_CHANGE;
    }
}

void decrease_speed(int *time) {
    if (*time <= TIME_LIMIT_MAX) {
        *time *= TIME_CHANGE;
    } else {
        *time = TIME_STOP;
    }
}
