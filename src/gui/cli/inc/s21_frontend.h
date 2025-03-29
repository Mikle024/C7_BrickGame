#ifndef S21_FRONTEND_H
#define S21_FRONTEND_H

#include <ncurses.h>
#include <unistd.h>

#include "../../../brick_game/tetris/inc/s21_defines.h"
#include "../../../brick_game/tetris/inc/s21_tetris.h"

// board size
#define Y_START 5  // new_win
#define X_START 5  // new_win
#define F_HEIGHT 20
#define F_WIDTH 10

// board size for printing
#define BOARD_HEIGHT (FIELD_HEIGHT + 2)
#define BOARD_WIDTH (FIELD_WIDTH * 2 + 2)

// figure size
#define FIGURE_X (F_WIDTH / 2 - 2)
#define FIGURE_S 4

//  next figure size
#define NEXT_HEIGHT 8
#define NEXT_WIDTH 14
#define NEXT_Y 5
#define NEXT_X 27

// score size
#define SCORE_HEIGHT 14
#define SCORE_WIDTH 14
#define SCORE_Y 13
#define SCORE_X 27

// input size
#define INPUT_HEIGHT 7
#define INPUT_WIDTH 36
#define INPUT_Y 27
#define INPUT_X 5

typedef struct WinCurses {
  WINDOW *winBoard;
  WINDOW *winBrick;
  WINDOW *winScore;
  WINDOW *winInput;

} WinCurses;

WinCurses *initCurses();
WinCurses *createFrontend();
void printStartDashboard(WINDOW *win);
void printFrontend(GameInfo_t *game, WinCurses *winGame);
void printPauseDashboard(WINDOW *win);
void gameOverDashboard(WINDOW *win);
void freeCurses(WinCurses *win);

void initColors();
void printField(int **field, WINDOW *win);
void printNext(int **figure, WINDOW *win);
void clearNext(WINDOW *win, int y_pos, int x_pos);

void printManagement(WINDOW *win);
void printScore(GameInfo_t *game, WINDOW *win);

#endif