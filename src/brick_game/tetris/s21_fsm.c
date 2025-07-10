#include "inc/s21_fsm.h"

void transitionToState() {
  GameContext_t *context = getCurrentContext();
  if (context) {
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

  if (context && context->currentFigure && context->gameStateInfo.field) {
    processShift();
    clearCurrentFigureFromField();
    addCurrentFigureToField();
    context->currentState = GameState_Moving;
  }
}

void stateOfAttaching() {
  GameContext_t *context = getCurrentContext();

  if (context) {
    attachFigureToField();
    int lines = clearLines();
    countScore(lines);
    if (processGameOver())
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

void processShift() {
  GameContext_t *context = getCurrentContext();
  if (context && context->currentFigure && context->gameStateInfo.field) {
    if (context->userInput == Left) {
      moveFigureLeft();
    } else if (context->userInput == Right) {
      moveFigureRight();
    } else if (context->userInput == Down) {
      moveFigureDown();
    } else if (context->userInput == Action) {
      if (!isSquareFigure()) rotationFigure();
    } else if (context->userInput == Up && context->goodMode) {
      moveFigureUp();
    }
    context->shiftRequested = false;
  }
}

bool processAttaching() {
  GameContext_t *context = getCurrentContext();
  bool willAttach = false;
  if (context) {
    int originalY = context->figureY;

    context->figureY++;
    willAttach = collision();

    context->figureY = originalY;
  }
  return willAttach;
}

bool processGameOver() {
  GameContext_t *context = getCurrentContext();
  bool willGameOver = false;
  if (context && context->gameStateInfo.field) {
    int **field = context->gameStateInfo.field;

    for (int x = 0; x < FIELD_WIDTH && !willGameOver; x++) {
      if (field[0][x] != 0) willGameOver = true;
    }
  }
  return willGameOver;
}