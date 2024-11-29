#ifndef S21_TEST_H
#define S21_TEST_H

#include <check.h>

#include "../brick_game/s21_backend.h"

Suite *suiteInitializeGame(void);
Suite *suiteCreateFigure(void);
Suite *suiteTransitionTo(void);

void runTests(void);
void runTestcase(Suite *testcase);

#endif
