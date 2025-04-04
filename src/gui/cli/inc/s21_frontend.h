#ifndef S21_FRONTEND_H
#define S21_FRONTEND_H

#include <ncurses.h>
#include <unistd.h>

#include "../../../brick_game/tetris/inc/s21_defines.h"
#include "../../../brick_game/tetris/inc/s21_tetris.h"
#include "s21_frontend_defs.h"

typedef enum {
  SCREEN_START,
  SCREEN_GAME,
  SCREEN_PAUSE,
  SCREEN_GAME_OVER
} ScreenState;

typedef struct WinCurses {
  WINDOW *winBoard;
  WINDOW *winBrick;
  WINDOW *winScore;
  WINDOW *winInput;
  ScreenState currentScreen;

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

void printManagement(WINDOW *win);
void printScore(GameInfo_t *game, WINDOW *win);

void clearNext(WINDOW *win);

#endif