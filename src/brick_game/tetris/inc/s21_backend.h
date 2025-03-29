#ifndef S21_BACKEND_H
#define S21_BACKEND_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

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
int **createFigure(int figureNum);
void dropNewFigure(int x, int y);
void addCurrentFigureToField();
void clearCurrentFigureFromField();
bool attachFigureToField();
bool isSquareFigure();
bool collision();
bool pixelInField(int x, int y);
void processShift();
bool processAttaching();
void countScore(int lines);
void countSpeed();
void updateScore();
int clearLines();
bool fullLine(int numLine);
void removeLine(int numLine);
void moveFigureRight();
void moveFigureLeft();
bool moveFigureDown();
bool moveFigureUp();
void rotationFigure();

#endif