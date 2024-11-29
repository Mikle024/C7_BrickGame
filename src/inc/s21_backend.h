#ifndef S21_BACKEND_H
#define S21_BACKEND_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "s21_defines.h"
#include "s21_objects.h"

// typedef struct GameContextWrapper {
//   GameContext_t *gameContext;
// } GameContextWrapper; // Интерфейс
//
//  Глобальная переменная для обёртки контекста игры
// GameContextWrapper *globalContextWrapper = NULL;

// Функции для работы с интерфейсом
// void initializeGameContextWrapper(void);
// GameContextWrapper* createGameContextWrapper(void);
// GameContext_t* getGameContext(GameContextWrapper *wrapper);
// void freeGameContextWrapper(GameContextWrapper *wrapper);

// Переходы состояний
void transitionTo(GameContext_t *context, GameState newState);
void transitionToStart(GameContext_t *context);
void transitionToSpawn(GameContext_t *context);
void transitionToMoving(GameContext_t *context);
void transitionToShifting(GameContext_t *context);
void transitionToAttaching(GameContext_t *context);
void transitionToGameOver(GameContext_t *context);

// Логика игры
void dropNewFigure(GameContext_t *context);  // Спавн фигуры
void collision(GameContext_t *context);  // Проверка столкновения
void calculate(GameContext_t *context);  // Высчитывание такта

// Работа с массивом поля
void addCurrentFigureToField(
    GameContext_t *context);  // Добавляет текущую фигуру в массив поля
void clearCurrentFigureFromField(
    GameContext_t *context);  // Удаляет текущую фигуру из массива поля
void attachFigureToField(
    GameContext_t *context);  // Меняем значения массива фигур и клеем к полю

// Управление пользователя
// void moveFigureDown(GameContext_t *context);  // Смещение фигуры вниз
// void moveFigureUp(GameContext_t *context);  // Смещение фигуры вверх
// void moveFigureRight(GameContext_t *context);  // Смещение фигуры вправо
// void moveFigureLeft(GameContext_t *context);  // Смещение фигуры влево
// int **rotationFigure(GameContext_t *context);  // Поворот фигуры

// DataHelper
// Создание и очистка структуры игры
void initializeGame(GameContext_t *context,
                    bool *checkInit);  // Инициализация игры
void freeGame(GameContext_t *currentContext);  // Очистка игры
int **createFigure();                          // Создание фигуры
void freeFigure(int **currentFigure);  // Очистка указателя фигуры
int **createField();                   // Создание поля
void freeField(int **currentField);  // Очистка указателя поля

// Функции библиотеки
void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

// Инициализация рандома
void initRandom(void);

#endif