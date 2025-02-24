#include "../inc/s21_fsm.h"

void transitionTo(GameState newState) {
  GameContext_t *context = getCurrentContext();
  const int transitionMatrix[STATE_COUNT][STATE_COUNT] = {
      {0, 1, 0, 0, 0, 0},  // GameState_Start (0)
      {0, 0, 1, 0, 0, 0},  // GameState_Spawn (1)
      {0, 0, 1, 1, 1, 0},  // GameState_Moving (2)
      {0, 0, 1, 0, 1, 0},  // GameState_Shifting (3)
      {0, 1, 0, 0, 0, 1},  // GameState_Attaching (4)
      {1, 0, 0, 0, 0, 0}   // GameState_GameOver (5)
  };
  if (transitionMatrix[context->currentState][newState]) {
    switch (newState) {
      case GameState_Start:
        stateOfStart();
        break;
      case GameState_Spawn:
        stateOfSpawn();
        break;
      case GameState_Moving:
        stateOfMoving();
        break;
      case GameState_Shifting:
        stateOfShifting();
        break;
      case GameState_Attaching:
        stateOfAttaching();
        break;
      case GameState_GameOver:
        stateOfGameOver();
        break;
    }
  }
}

void stateOfStart() {
  GameContext_t *context = getCurrentContext();
  context->currentState = GameState_Start;
}

void stateOfSpawn() {
  GameContext_t *context = getCurrentContext();
  dropNewFigure();
  addCurrentFigureToField();
  context->currentState = GameState_Spawn;
}

void stateOfMoving() {
  GameContext_t *context = getCurrentContext();
  if (!context->gameStateInfo.pause) {
    moveFigureDown();
    clearCurrentFigureFromField();
    addCurrentFigureToField();
  }
  context->currentState = GameState_Moving;
}

void stateOfShifting() {
  GameContext_t *context = getCurrentContext();
  processShift();  // Функция обработки сдвига
  clearCurrentFigureFromField();
  addCurrentFigureToField();
  context->currentState = GameState_Shifting;
}

void stateOfAttaching() {
  GameContext_t *context = getCurrentContext();
  attachFigureToField();
  int lines = clearLines();
  countScore(lines);
  context->currentState = GameState_Attaching;
}

void stateOfGameOver() {
  GameContext_t *context = getCurrentContext();
  context->currentState = GameState_GameOver;
}