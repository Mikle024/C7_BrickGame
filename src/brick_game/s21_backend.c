#include "../inc/s21_backend.h"

void initRandom(void) { srand(time(NULL)); }

// Инициализация игры
void initializeGame(GameContext_t *context, bool *checkInit) {
  context->currentState = GameState_Start;

  context->gameStateInfo.field = createField(FIELD_WIDTH, FIELD_HEIGHT);
  context->gameStateInfo.next = createFigure(context->gameStateInfo);
  context->gameStateInfo.score = 0;
  context->gameStateInfo.high_score = 0;
  context->gameStateInfo.level = 1;
  context->gameStateInfo.speed = 1;
  context->gameStateInfo.pause = 0;

  context->currentFigure = createFigure(context->gameStateInfo);
  context->figureX = FIELD_WIDTH / 2 - FIGURE_SIZE / 2;
  context->figureY = -2;
  context->oldFigureX = FIELD_WIDTH / 2 - FIGURE_SIZE / 2;
  context->oldFigureY = -2;
  context->ticksSinceLastMove = 0;
  context->collision = 0;
  context->gameOver = 0;

  *checkInit = true;
}

// Очистка игры
void freeGame(GameContext_t *currentContext) {
  if (currentContext) {
    if (currentContext->currentFigure) {
      freeFigure(currentContext->currentFigure);
      currentContext->currentFigure = NULL;
    }
    if (currentContext->gameStateInfo.field) {
      freeField(currentContext->gameStateInfo.field);
      currentContext->gameStateInfo.field = NULL;
    }
    if (currentContext->gameStateInfo.next) {
      freeFigure(currentContext->gameStateInfo.next);
      currentContext->gameStateInfo.next = NULL;
    }
    memset(currentContext, 0, sizeof(GameContext_t));
  }
}

// DataHelper
int **createFigure() {
  int **newFigure = (int **)malloc(FIGURE_SIZE * sizeof(int *));
  for (int i = 0; i < FIGURE_SIZE; i++) {
    newFigure[i] = (int *)malloc(FIGURE_SIZE * sizeof(int));
    for (int j = 0; j < FIGURE_SIZE; j++) {
      newFigure[i][j] = 0;
    }
  }
  return newFigure;
}

void freeFigure(int **currentFigure) {
  if (currentFigure) {
    for (int i = 0; i < FIGURE_SIZE; i++) {
      free(currentFigure[i]);
    }
    free(currentFigure);
  }
}

int **createField() {
  int **newField = (int **)malloc(FIELD_HEIGHT * sizeof(int *));
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    newField[i] = (int *)malloc(FIELD_WIDTH * sizeof(int));
    for (int j = 0; j < FIELD_WIDTH; j++) {
      newField[i][j] = 0;
    }
  }
  return newField;
}

void freeField(int **currentField) {
  if (currentField) {
    for (int i = 0; i < FIELD_HEIGHT; i++) {
      free(currentField[i]);
    }
    free(currentField);
  }
}

void dropNewFigure(GameContext_t *context) {
  // Паттерны фигур
  static const int patternFigure[FIGURE_COUNT][FIGURE_SIZE][FIGURE_SIZE] = {
      // I
      {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      // O
      {{0, 2, 2, 0}, {0, 2, 2, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      // T
      {{0, 0, 0, 0}, {3, 3, 3, 0}, {0, 3, 0, 0}, {0, 0, 0, 0}},
      // L
      {{0, 4, 0, 0}, {0, 4, 0, 0}, {0, 4, 4, 0}, {0, 0, 0, 0}},
      // J
      {{0, 0, 5, 0}, {0, 0, 5, 0}, {0, 5, 5, 0}, {0, 0, 0, 0}},
      // S
      {{0, 0, 0, 0}, {0, 0, 6, 6}, {0, 6, 6, 0}, {0, 0, 0, 0}},
      // Z
      {{0, 0, 0, 0}, {7, 7, 0, 0}, {0, 7, 7, 0}, {0, 0, 0, 0}}};

  // Генерация случайной фигуры
  int figureNum = rand() % FIGURE_COUNT;

  // Создание новой фигуры
  int **newFigure = createFigure();

  // Копирование данных из паттерна в новую фигуру
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      newFigure[i][j] = patternFigure[figureNum][i][j];
    }
  }

  // Обновление координат и текущей фигуры
  context->figureX = FIELD_WIDTH / 2 - FIGURE_SIZE / 2;
  context->figureY = -2;
  context->oldFigureY = -2;

  // Очистка предыдущей фигуры
  freeFigure(context->currentFigure);
  context->currentFigure = newFigure;
  context->collision = 0;
}

void collision(GameContext_t *context) {
  int **currentFigure = context->currentFigure;

  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (currentFigure[i][j] != 0) {  // Проверяем блок текущей фигуры.
        int fx = context->figureX + j;  // Абсолютная X-координата.
        int fy = context->figureY + i;  // Абсолютная Y-координата.

        // Проверка пересечения с другим блоком игрового поля.
        if (fy >= 0 && fx >= 0 && fx < FIELD_WIDTH && fy < FIELD_HEIGHT) {
          int fieldValue = context->gameStateInfo.field[fy][fx];

          // Игнорируем коллизию с блоками текущей фигуры.
          if (fieldValue != 0 && fieldValue != currentFigure[i][j]) {
            context->collision = 1;

            // Если коллизия произошла выше верхней границы, конец игры.
            if (context->figureY + i == 0) {
              context->gameOver = 1;
            }
          }
        }
        // Проверка выхода за нижнюю границу игрового поля.
        else if (fy >= FIELD_HEIGHT) {
          context->collision = 1;
        }
      }
    }
  }
}

void calculate(GameContext_t *context) {
  // Увеличиваем количество тактов
  context->ticksSinceLastMove++;
  //   Если прошло достаточно тактов, двигаем фигуру вниз
  if (context->ticksSinceLastMove >= TICKS_PER_MOVE) {
    context->ticksSinceLastMove = 0;  // Сбрасываем счётчик тактов
    // Проверяем, нет ли столкновения перед движением вниз
    context->figureY++;
    collision(context);
    if (context->collision) context->figureY--;
  }
}

void addCurrentFigureToField(GameContext_t *context) {
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (context->currentFigure[i][j] != 0 && context->figureY + i >= 0 &&
          context->figureY + i < FIELD_HEIGHT && context->figureX + j >= 0 &&
          context->figureX + j < FIELD_WIDTH) {
        context->gameStateInfo
            .field[context->figureY + i][context->figureX + j] =
            context->currentFigure[i][j];
      }
    }
  }
}

void attachFigureToField(GameContext_t *context) {
  // Убедиться, что текущая фигура есть на поле
  if (context->currentFigure != NULL) {
    // Сначала добавляем текущую фигуру на поле
    addCurrentFigureToField(context);

    // Обновляем значения блоков фигуры (прибавляем 7)
    int **field = context->gameStateInfo.field;

    for (int i = 0; i < FIGURE_SIZE; i++) {
      for (int j = 0; j < FIGURE_SIZE; j++) {
        if (context->currentFigure[i][j] != 0) {  // Блок фигуры
          int fx = context->figureX + j;
          int fy = context->figureY + i;

          // Проверка границ поля
          if (fx >= 0 && fx < FIELD_WIDTH && fy >= 0 && fy < FIELD_HEIGHT) {
            field[fy][fx] += 7;  // Увеличиваем значение для приклеивания
          }
        }
      }
    }
  }
}

void clearCurrentFigureFromField(GameContext_t *context) {
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      // Проверяем, находится ли часть фигуры внутри границ игрового поля
      int fieldX = context->oldFigureX + j;
      int fieldY = context->oldFigureY + i;

      if (context->currentFigure[i][j] != 0 && fieldY >= 0 &&
          fieldY < FIELD_HEIGHT && fieldX >= 0 && fieldX < FIELD_WIDTH) {
        // Очищаем ячейку, если она соответствует части фигуры
        context->gameStateInfo.field[fieldY][fieldX] = 0;
      }
    }
  }

  // Обновляем старые координаты
  context->oldFigureX = context->figureX;
  context->oldFigureY = context->figureY;
}

void transitionTo(GameContext_t *context, GameState newState) {
  // Определение переходов: 1 - переход возможен, 0 - недопустим
  const int transitionMatrix[STATE_COUNT][STATE_COUNT] = {
      {0, 1, 0, 0, 0, 0},  // GameState_Start (0)
      {0, 0, 1, 0, 0, 0},  // GameState_Spawn (1)
      {0, 0, 1, 1, 1, 0},  // GameState_Moving (2)
      {0, 0, 1, 0, 1, 0},  // GameState_Shifting (3)
      {0, 1, 0, 0, 0, 1},  // GameState_Attaching (4)
      {1, 0, 0, 0, 0, 0}   // GameState_GameOver (5)
  };
  if (transitionMatrix[context->currentState][newState]) {
    //    context->currentState = newState;
    switch (newState) {
      case GameState_Start:
        // Инициализация
        transitionToStart(context);
        break;
      case GameState_Spawn:
        transitionToSpawn(context);
        break;
      case GameState_Moving:
        transitionToMoving(context);
        break;
      case GameState_Shifting:
        transitionToShifting(context);
        break;
      case GameState_Attaching:
        transitionToAttaching(context);
        break;
      case GameState_GameOver:
        transitionToGameOver(context);
        break;
    }
  }
}

// Функция для перехода в состояние начала игры
void transitionToStart(GameContext_t *context) {
  context->currentState = GameState_Start;
}

// Функция для перехода в состояние появления новой фигуры
void transitionToSpawn(GameContext_t *context) {
  dropNewFigure(context);
  addCurrentFigureToField(context);
  context->currentState = GameState_Spawn;
}

// Функция для перехода в состояние перемещения
void transitionToMoving(GameContext_t *context) {
  calculate(context);
  clearCurrentFigureFromField(context);
  addCurrentFigureToField(context);
  context->currentState = GameState_Moving;
}

// Функция для перехода в состояние изменения положения
void transitionToShifting(GameContext_t *context) {
  context->currentState = GameState_Shifting;
}

// Функция для перехода в состояние прикрепления фигуры
void transitionToAttaching(GameContext_t *context) {
  attachFigureToField(context);
  //  int clearedLines = eraseLines(context);
  //  if (clearedLines > 0) {
  //    context->gameStateInfo.score++;
  //  }
  context->gameStateInfo.level++;
  context->currentState = GameState_Attaching;
}

// Функция для перехода в состояние завершения игры
void transitionToGameOver(GameContext_t *context) {
  context->currentState = GameState_GameOver;
}

GameInfo_t updateCurrentState() {
  static GameContext_t gameContext;
  GameInfo_t currentGameInfo;
  static bool initGame = false;
  if (!initGame) {
    initializeGame(&gameContext, &initGame);
    currentGameInfo = gameContext.gameStateInfo;
  } else {
    switch (gameContext.currentState) {
      case GameState_Start:
        transitionTo(&gameContext, GameState_Spawn);
        currentGameInfo = gameContext.gameStateInfo;
        break;
      case GameState_Spawn:
        transitionTo(&gameContext, GameState_Moving);
        currentGameInfo = gameContext.gameStateInfo;
        break;
      case GameState_Moving:
        if (gameContext.collision) {
          transitionTo(&gameContext, GameState_Attaching);
          currentGameInfo = gameContext.gameStateInfo;
        } else {
          transitionTo(&gameContext, GameState_Moving);
          currentGameInfo = gameContext.gameStateInfo;
        }
        break;
      case GameState_Attaching:
        if (!gameContext.gameOver) {
          transitionTo(&gameContext, GameState_Spawn);
          currentGameInfo = gameContext.gameStateInfo;
        } else {
          transitionTo(&gameContext, GameState_GameOver);
          currentGameInfo = gameContext.gameStateInfo;
        }
        break;
      case GameState_GameOver:
        freeGame(&gameContext);
        break;
    }
  }
  return currentGameInfo;
}

// void userInput(UserAction_t action, bool hold) {
//     // Получаем контекст игры из глобальной обёртки
//     GameContext_t current = updateCurrentState();
//
//     // Проверяем, если контекст не инициализирован или поле игры пусто
//     if (context == NULL || context->gameStateInfo.field == NULL) {
//         return;
//     }
//
//     // Обрабатываем действие пользователя
//     switch (action) {
//         case Left:
//             moveFigureLeft(context);
//             collision(context);
//             if (context->collision) {
//                 moveFigureRight(context);
//                 context->collision--;
//             }
//             break;
//         case Right:
//             moveFigureRight(context);
//             collision(context);
//             if (context->collision) {
//                 moveFigureLeft(context);
//                 context->collision--;
//             }
//             break;
//         case Down:
//             moveFigureDown(context);
//             collision(context);
//             if (context->collision) {
//                 moveFigureUp(context);
//                 context->collision--;
//             }
//             break;
//         case Action: {
//             // Поворачиваем фигуру
//             int **rotatedFigure = rotationFigure(context);
//             int **tmp = context->currentFigure;
//             context->currentFigure = rotatedFigure;
//             collision(context);
//             if (context->collision) {
//                 context->currentFigure = tmp;
//                 freeFigure(rotatedFigure);
//                 context->collision--;
//             } else {
//                 freeFigure(tmp);
//             }
//             break;
//         }
//         case Pause:
//             context->gameStateInfo.pause = !context->gameStateInfo.pause;
//             break;
//         case Terminate:
//             context->gameOver = true;
//             break;
//         case Up:
//         default:
//             // Ничего не делаем
//             break;
//     }
// }

// int **rotationFigure(GameContext_t *context) {
//     // Создаем новый массив для повернутой фигуры
//     int **shiftFigure = createFigure();
//     int **currentFigure = context->currentFigure;
//
//     // Выполняем вращение на 90 градусов по часовой стрелке
//     for (int i = 0; i < FIGURE_SIZE; i++) {
//         for (int j = 0; j < FIGURE_SIZE; j++) {
//             // Новый элемент [i][j] в повернутой фигуре берётся из
//             [FIGURE_SIZE - j - 1][i] в исходной shiftFigure[i][j] =
//             currentFigure[FIGURE_SIZE - j - 1][i];
//         }
//     }
//
//     return shiftFigure;
// }

// void moveFigureDown(GameContext_t *context) {
//   context->figureY++;
//   collision(context);
//   if (context->collision) {
//     context->figureY--;  // Возвращаем, если столкновение
//   }
// }
//
// void moveFigureUp(GameContext_t *context) {
//   context->figureY--;
//   collision(context);
//   if (context->collision) {
//     context->figureY++;  // Возвращаем, если столкновение
//   }
// }
//
// void moveFigureRight(GameContext_t *context) {
//   context->figureX++;
//   collision(context);
//   if (context->collision) {
//     context->figureX--;  // Возвращаем, если столкновение
//   }
// }
//
// void moveFigureLeft(GameContext_t *context) {
//   context->figureX--;
//   collision(context);
//   if (context->collision) {
//     context->figureX++;  // Возвращаем, если столкновение
//   }
// }

// Функция для инициализации контекста игры
// void initializeGameContextWrapper(void) {
//    if (globalContextWrapper == NULL) {
//        globalContextWrapper = createGameContextWrapper();
//    }
//}
//
// GameContextWrapper* createGameContextWrapper(void) {
//    GameContextWrapper* wrapper =
//    (GameContextWrapper*)malloc(sizeof(GameContextWrapper));
//    wrapper->gameContext = (GameContext_t*)malloc(sizeof(GameContext_t));
//    // Инициализация контекста игры
//    return wrapper;
//}
//
// GameContext_t* getGameContext(GameContextWrapper *wrapper) {
//    return wrapper->gameContext;
//}
//
// void freeGameContextWrapper(GameContextWrapper *wrapper) {
//    free(wrapper->gameContext);
//    free(wrapper);
//}

// void plantFigure(GameContext_t *context) {
//  int **currentFigure = context->currentFigure;
//
//  for (int i = 0; i < FIGURE_SIZE; i++) {
//    for (int j = 0; j < FIGURE_SIZE; j++) {
//      if (currentFigure[i][j] != 0) {
//        int fx = context->figureX + j;
//        int fy = context->figureY + i;
//        context->gameStateInfo.field[fy][fx] = currentFigure[i][j];
//      }
//    }
//  }
//  freeFigure(currentFigure);
//  context->currentFigure = NULL;
//}
//
// int lineFilled(int i, int **currentField) {
//  int emptyBlock = 1;
//  for (int j = 0; j < FIELD_WIDTH; j++) {
//    if (currentField[i][j] == 0) emptyBlock = 0;
//  }
//  return emptyBlock;
//}
//
// void dropLine(int i, int **currentField) {
//  for (int k = i; k > 0; k--) {
//    for (int j = 0; j < FIELD_WIDTH; j++) {
//      currentField[k][j] = currentField[k - 1][j];
//    }
//  }
//  for (int j = 0; j < FIELD_WIDTH; j++) {
//    currentField[0][j] = 0;
//  }
//}
//
// int eraseLines(GameContext_t *context) {
//  int countLines = 0;
//  int **currentField = context->gameStateInfo.field;
//
//  for (int i = FIELD_HEIGHT - 1; i >= 0; i--) {
//    if (lineFilled(i, currentField)) {
//      dropLine(i, currentField);
//      countLines++;
//      i++;
//    }
//  }
//  return countLines;
//}