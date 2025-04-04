#ifndef S21_TESTS_H
#define S21_TESTS_H

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#define MKDIR(dir) mkdir(dir, 0700)

#include "../tetris/inc/s21_backend.h"
#include "../tetris/inc/s21_file_utils.h"
#include "../tetris/inc/s21_fsm.h"
#include "../tetris/inc/s21_tetris.h"
#include "../tetris/inc/s21_utils.h"

typedef struct {
  int total;
  int passed;
  int failed;
  int skipped;
  clock_t startTime;
  clock_t endTime;
} TestStats;

void runTests(void);
void runTestcase(Suite *testcase, const char *category);
void cleanupAfterTest(void);
void setupTest(void);
void cleanupTest(void);
int **createTestField(int pattern[FIELD_HEIGHT][FIELD_WIDTH]);
int **createTestFigure(int pattern[FIGURE_SIZE][FIGURE_SIZE]);
void setupGameWithCustomValues(int fieldPattern[FIELD_HEIGHT][FIELD_WIDTH],
                               int figurePattern[FIGURE_SIZE][FIGURE_SIZE],
                               int posX, int posY);

Suite *suiteCreateMatrix(void);
Suite *suiteFreeMatrix(void);

Suite *suiteInitHighScore(void);
Suite *suiteUpdateScore(void);

Suite *suiteGetCurrentContext(void);
Suite *suiteInitRandom(void);
Suite *suiteGetCurrentTime(void);
Suite *suiteTimer(void);
Suite *suiteInitializeGame(void);
Suite *suiteFreeGame(void);
Suite *suiteCreateFigure(void);
Suite *suiteDropNewFigure(void);

Suite *suiteAddCurrentFigureToField(void);
Suite *suiteClearCurrentFigureFromField(void);
Suite *suiteAttachFigureToField(void);
Suite *suiteIsSquareFigure(void);
Suite *suiteCollision(void);
Suite *suitePixelInField(void);

Suite *suiteTetrisLibrary(void);
Suite *suiteTransitionToState(void);
Suite *suiteStateUtils(void);
Suite *suiteFsm(void);

Suite *suiteCountScore(void);
Suite *suiteCountSpeed(void);
Suite *suiteClearLines(void);
Suite *suiteFullLine(void);
Suite *suiteRemoveLine(void);

Suite *suiteMoveFigureLeft(void);
Suite *suiteMoveFigureRight(void);
Suite *suiteMoveFigureDown(void);
Suite *suiteMoveFigureUp(void);
Suite *suiteRotationFigure(void);

#endif
