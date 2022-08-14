// Copyright 2022 @student.21-school.ru

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Game settingis
// Field width (should be % 20)
#define RIGHT_BORDER 80
// Field height
#define DOWN_BORDER 25
// Scores to win (max - 99)
#define WIN_SCORE 21
// Game speed (higher -> slower)
#define TIC 40
// Rocket size = 1 + 2 * rocket border
#define ROCKET_BORDER 1

#define LEFT_BORDER 1
#define UP_BORDER 1
#define MIDDLE_VER (RIGHT_BORDER - LEFT_BORDER) / 2 + 1
#define MIDDLE_HOZ (DOWN_BORDER - UP_BORDER) / 2 + 1
#define MOVE_UP -1
#define MOVE_DOWN 1
#define MOVE_RIGHT 1
#define MOVE_LEFT -1
#define MOVE_HOR 0
#define NOT_MOVED 0
#define TRUE 1
#define FALSE 0
#define INDENT_SCORE_Y 3
#define INDENT_SCORE_X 3

int check_win(int ball_y, int ball_s_y, int rocket, int move);
void draw(int b_x, int b_y, int po_score, int pt_score, int rl, int rr);
void draw_line();
int get_y_bounce(int ball_y, int ball_s_y, int rocket, int move);
int abs(int num);
int is_in(int num, int lt, int rh);

int main() {
    int po_score = 0, pt_score = 0;
    int ball_s_x = MOVE_RIGHT, ball_s_y = MOVE_HOR;
    int ball_x = MIDDLE_VER, ball_y = MIDDLE_HOZ;
    int rocket_l = MIDDLE_HOZ, rocket_r = MIDDLE_HOZ;

    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    while (po_score < WIN_SCORE && pt_score < WIN_SCORE) {
        draw(ball_x, ball_y, po_score, pt_score, rocket_l, rocket_r);

        char inp = getch();
        usleep(TIC * 1000);

        int l_move = NOT_MOVED, r_move = NOT_MOVED;

        switch (inp) {
          case 'A':
            if (rocket_l > UP_BORDER + ROCKET_BORDER) {
                --rocket_l;
            }
            l_move = MOVE_UP;
            break;
          case 'Z':
            if (rocket_l < DOWN_BORDER - ROCKET_BORDER) {
                ++rocket_l;
            }
            l_move = MOVE_DOWN;
            break;
          case 'K':
            if (rocket_r > UP_BORDER + ROCKET_BORDER) {
                --rocket_r;
            }
            r_move = MOVE_UP;
            break;
          case 'M':
            if (rocket_r < DOWN_BORDER - ROCKET_BORDER) {
                ++rocket_r;
            }
            r_move = MOVE_DOWN;
            break;
          default:
            break;
        }

        ball_x += ball_s_x;
        ball_y += ball_s_y;

        if (ball_x == LEFT_BORDER &&
            check_win(ball_y, ball_s_y, rocket_l, l_move) == TRUE) {
            pt_score += 1;
            ball_x = MIDDLE_VER;
            ball_y = MIDDLE_HOZ;
            ball_s_y = MOVE_HOR;
            ball_s_x = MOVE_LEFT;
            continue;
        }

        if (ball_x == RIGHT_BORDER &&
            check_win(ball_y, ball_s_y, rocket_r, r_move) == TRUE) {
            po_score += 1;
            ball_x = MIDDLE_VER;
            ball_y = MIDDLE_HOZ;
            ball_s_y = MOVE_HOR;
            ball_s_x = MOVE_RIGHT;
            continue;
        }

        if (ball_x == LEFT_BORDER) {
            int temp_s_y = ball_s_y;
            ball_s_y = get_y_bounce(ball_y, ball_s_y, rocket_l, l_move);
            ball_x += 1;
            ball_y -= temp_s_y;
            ball_s_x = MOVE_RIGHT;

        } else if (ball_x == RIGHT_BORDER) {
            int temp_s_y = ball_s_y;
            ball_s_y = get_y_bounce(ball_y, ball_s_y, rocket_r, r_move);
            ball_x -= 1;
            ball_y -= temp_s_y;
            ball_s_x = MOVE_LEFT;
        }

        if (ball_y < UP_BORDER + 1 || ball_y > DOWN_BORDER - 1) {
            ball_s_y = -ball_s_y;
        }
    }

    clear();
    endwin();

    if (po_score == WIN_SCORE) {
        printf("Player 1 win! Congratulations");
    } else {
        printf("Player 2 win! Congratulations");
    }

    return 0;
}

int check_win(int ball_y, int ball_s_y, int rocket, int move) {
    if (is_in(ball_y, rocket - ROCKET_BORDER, rocket + ROCKET_BORDER) ==
            FALSE &&
        is_in(ball_y - ball_s_y, rocket - move - ROCKET_BORDER,
              rocket - move + ROCKET_BORDER) == FALSE &&
        is_in(ball_y - ball_s_y, rocket - ROCKET_BORDER,
              rocket + ROCKET_BORDER) == FALSE) {
        return TRUE;
    }
    return FALSE;
}

void draw(int b_x, int b_y, int po_score, int pt_score, int rl, int rr) {
    clear();
    draw_line();

    for (int i = UP_BORDER; i <= DOWN_BORDER; ++i) {
        for (int j = LEFT_BORDER; j <= RIGHT_BORDER; ++j) {
            if ((j == LEFT_BORDER &&
                 is_in(i, rl - ROCKET_BORDER, rl + ROCKET_BORDER) == TRUE) ||
                (j == RIGHT_BORDER &&
                 is_in(i, rr - ROCKET_BORDER, rr + ROCKET_BORDER) == TRUE)) {
                printw("|");
            } else if (j == b_x && i == b_y) {
                printw("o");
            } else if (j == MIDDLE_VER) {
                printw("|");
            } else if (j == MIDDLE_VER - INDENT_SCORE_X - 1 && po_score > 9 &&
                       i == INDENT_SCORE_Y) {
                printw("%d", po_score / 10);
            } else if (j == MIDDLE_VER - INDENT_SCORE_X &&
                       i == INDENT_SCORE_Y) {
                printw("%d", po_score % 10);
            } else if (j == MIDDLE_VER + INDENT_SCORE_X &&
                       i == INDENT_SCORE_Y) {
                if (pt_score > 9) {
                    printw("%d", pt_score / 10);
                } else {
                    printw("%d", pt_score % 10);
                }
            } else if (j == MIDDLE_VER + INDENT_SCORE_X + 1 &&
                       i == INDENT_SCORE_Y && pt_score > 9) {
                printw("%d", pt_score % 10);
            } else {
                printw(" ");
            }
        }
        printw("\n");
    }

    draw_line();
    printw("Player 1: A - up, Z - down\nPlayer 2: K - up, M - down\n");
    printw("(Use Caps Lock)\n");
}

void draw_line() {
    for (int i = LEFT_BORDER; i <= RIGHT_BORDER; ++i) {
        if (i == MIDDLE_VER) {
            printw("+");
        } else {
            printw("-");
        }
    }
    printw("\n");
}

int get_y_bounce(int ball_y, int ball_s_y, int rocket, int move) {
    if (ball_y - ball_s_y == rocket - move - ROCKET_BORDER) {
        return MOVE_UP;
    }
    if (ball_y - ball_s_y == rocket - move) {
        return MOVE_HOR;
    }
    if (ball_y - ball_s_y == rocket - move + ROCKET_BORDER) {
        return MOVE_DOWN;
    }
    if (ball_y == rocket - ROCKET_BORDER) {
        return MOVE_UP;
    }
    if (ball_y == rocket) {
        return MOVE_UP;
    }
    if (ball_y == rocket + ROCKET_BORDER) {
        return MOVE_DOWN;
    }
    if (is_in(ball_y - ball_s_y, rocket - ROCKET_BORDER,
              rocket + ROCKET_BORDER) == TRUE) {
        return MOVE_UP;
    }
    return MOVE_HOR;
}

int abs(int num) {
    if (num > 0) {
        return num;
    }
    return -num;
}

int is_in(int num, int lt, int rh) {
    if (num >= lt && num <= rh) {
        return TRUE;
    }
    return FALSE;
}
