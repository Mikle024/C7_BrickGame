#ifndef S21_TEST_H
#define S21_TEST_H

#include <check.h>

#include "../tetris/inc/s21_tetris.h"

Suite *suiteGetCurrentContext(void);
Suite *suiteInitRandom(void);
Suite *suiteGetCurrentTime(void);
Suite *suiteTimer(void);
Suite *suiteInitHighScore(void);
Suite *suiteFreeMatrix(void);
Suite *suiteFreeGame(void);
Suite *suiteDropNewFigure(void);
Suite *suiteAddCurrentFigureToField(void);
Suite *suiteClearCurrentFigureFromField(void);
Suite *suiteAttachFigureToField(void);
Suite *suiteIfSquare(void);
Suite *suiteCollision(void);
Suite *suiteProcessShift(void);

void runTests(void);
void runTestcase(Suite *testcase);

#endif
