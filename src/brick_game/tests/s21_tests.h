#ifndef S21_TESTS_H
#define S21_TESTS_H

#include <check.h>
#include <stdlib.h>

#include "../tetris/inc/s21_backend.h"
#include "../tetris/inc/s21_file_utils.h"
#include "../tetris/inc/s21_utils.h"

// Объявления для тестовых наборов
void runTests(void);
void runTestcase(Suite *testcase);

// Объявления для тестов матричных операций
Suite *suiteCreateMatrix(void);
Suite *suiteFreeMatrix(void);

// Объявления для тестов файловых операций
Suite *suiteInitHighScore(void);
Suite *suiteUpdateScore(void);

// Объявления для тестов core механик
Suite *suiteGetCurrentContext(void);
Suite *suiteInitRandom(void);
Suite *suiteGetCurrentTime(void);
Suite *suiteTimer(void);
Suite *suiteInitializeGame(void);
Suite *suiteFreeGame(void);
Suite *suiteCreateFigure(void);
Suite *suiteDropNewFigure(void);

// Тесты для операций с фигурами
Suite *suiteAddCurrentFigureToField(void);
Suite *suiteClearCurrentFigureFromField(void);
Suite *suiteAttachFigureToField(void);
Suite *suiteIsSquareFigure(void);
Suite *suiteCollision(void);
Suite *suitePixelInField(void);
Suite *suiteProcessShift(void);
Suite *suiteProcessAttaching(void);

// Тесты для логики очков и уровней
Suite *suiteCountScore(void);
Suite *suiteCountSpeed(void);
Suite *suiteClearLines(void);
Suite *suiteFullLine(void);
Suite *suiteRemoveLine(void);

// Тесты для движения фигур
Suite *suiteMoveFigureRight(void);
Suite *suiteMoveFigureLeft(void);
Suite *suiteMoveFigureDown(void);
Suite *suiteMoveFigureUp(void);
Suite *suiteRotationFigure(void);

#endif
