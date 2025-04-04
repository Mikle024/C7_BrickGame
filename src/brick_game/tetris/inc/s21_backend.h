#ifndef S21_BACKEND_H
#define S21_BACKEND_H

#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>

#include "s21_defines.h"
#include "s21_file_utils.h"
#include "s21_fsm.h"
#include "s21_types.h"
#include "s21_utils.h"

GameContext_t *getCurrentContext();
void initRandom(void);
long long getCurrentTime();
bool timer();
int initHighScore();
void initializeGame(GameContext_t *gameContext, bool *checkInit);
void freeGame();
int **createFigure(const int figureNum);
void dropNewFigure(const int x, const int y);
void addCurrentFigureToField();
void clearCurrentFigureFromField();
void attachFigureToField();
bool isSquareFigure();
bool collision();
bool pixelInField(const int x, const int y);
void countScore(const int lines);
void countSpeed();
int clearLines();
bool fullLine(const int numLine);
void removeLine(const int numLine);
void moveFigureRight();
void moveFigureLeft();
void moveFigureDown();
void moveFigureUp();
void rotationFigure();

#endif