#ifndef S21_BACKEND_H
#define S21_BACKEND_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "s21_defines.h"
#include "s21_objects.h"
#include "s21_fsm.h"

void dropNewFigure();
int **createFigure(int figureNum);
bool collision();
bool pixelInField(int x, int y);
void processShift();
bool processAttaching();
void initScore();
void countScore(int lines);
void countSpeed();
void updateScore();

bool ifSquare();

int clearLines();
bool fullLine(int numLine);
void removeLine(int numLine);

void addCurrentFigureToField();
void clearCurrentFigureFromField();
void attachFigureToField();

void moveFigureRight();
void moveFigureLeft();
bool moveFigureDown();
bool moveFigureUp();
void rotationFigure();

void initializeGame(GameContext_t *gameContext, bool *checkInit);
void freeGame();
int **createMatrix(int rows, int column);
void freeMatrix(int **matrix, int rows);

GameContext_t *getCurrentContext();

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

void initRandom(void);
bool timer();
long long getCurrentTime();

#endif