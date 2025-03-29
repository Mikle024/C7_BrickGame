#include "inc/s21_fsm.h"

void transitionToState() {
  GameContext_t *context = getCurrentContext();
  switch (context->currentState) {
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

void stateOfStart() {
  GameContext_t *context = getCurrentContext();

  if (context && timer()) {
    if (!context->gameStateInfo.pause) context->currentState = GameState_Spawn;
  }
}

void stateOfSpawn() {
  GameContext_t *context = getCurrentContext();

  if (context) {
    dropNewFigure(START_COORD_F_X, START_COORD_F_Y);
    addCurrentFigureToField();
    context->currentState = GameState_Moving;
  }
}

void stateOfMoving() {
  GameContext_t *context = getCurrentContext();

  if (context && !context->gameStateInfo.pause) {
    if (processAttaching() && timer())
      context->currentState = GameState_Attaching;
    else if (context->shiftRequested)
      context->currentState = GameState_Shifting;
    else if (timer()) {
      moveFigureDown();
      clearCurrentFigureFromField();
      addCurrentFigureToField();
    }
  }
}

void stateOfShifting() {
  GameContext_t *context = getCurrentContext();

  if (context) {
    processShift();
    clearCurrentFigureFromField();
    addCurrentFigureToField();
    context->currentState = GameState_Moving;
  }
}

void stateOfAttaching() {
  GameContext_t *context = getCurrentContext();

  if (context) {
    bool outOfField = attachFigureToField();
    int lines = clearLines();
    countScore(lines);
    if (outOfField)
      context->currentState = GameState_GameOver;
    else
      context->currentState = GameState_Spawn;
  }
}

void stateOfGameOver() {
  GameContext_t *context = getCurrentContext();

  if (context) {
    freeGame();
  }
}