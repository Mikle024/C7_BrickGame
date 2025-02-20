#include "../inc/s21_fsm.h"

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
  //  dropNewFigure(context);
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
  if (!context->gameStateInfo.pause) {
    moveFigureDown(context);
    clearCurrentFigureFromField(context);
    addCurrentFigureToField(context);
  }
  context->currentState = GameState_Moving;
}

// Функция для перехода в состояние изменения положения
void transitionToShifting(GameContext_t *context) {
  processShift(context);  // Функция обработки сдвига
  clearCurrentFigureFromField(context);
  addCurrentFigureToField(context);
  context->currentState = GameState_Shifting;
}

// Функция для перехода в состояние прикрепления фигуры
void transitionToAttaching(GameContext_t *context) {
  attachFigureToField(context);
  int lines = clearLines();
  countScore(lines);
  context->currentState = GameState_Attaching;
  //  checkTopLine(context);
}

// Функция для перехода в состояние завершения игры
void transitionToGameOver(GameContext_t *context) {
  context->currentState = GameState_GameOver;
}