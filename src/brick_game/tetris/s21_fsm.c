#include "inc/s21_fsm.h"

void transitionToState() {
  switch (getCurrentContext()->currentState) {
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
  if (getCurrentContext() && timer()) {
    if (!getCurrentContext()->gameStateInfo.pause)
      getCurrentContext()->currentState = GameState_Spawn;
  }
}

void stateOfSpawn() {
  if (getCurrentContext()) {
    dropNewFigure(START_COORD_F_X, START_COORD_F_Y);
    addCurrentFigureToField();
    getCurrentContext()->currentState = GameState_Moving;
  }
}

void stateOfMoving() {
  if (getCurrentContext() && !getCurrentContext()->gameStateInfo.pause) {
    if (processAttaching() && timer())
      getCurrentContext()->currentState = GameState_Attaching;
    else if (getCurrentContext()->shiftRequested)
      getCurrentContext()->currentState = GameState_Shifting;
    else if (timer()) {
      moveFigureDown();
      clearCurrentFigureFromField();
      addCurrentFigureToField();
    }
  }
}

void stateOfShifting() {
  if (getCurrentContext() && getCurrentContext()->currentFigure &&
      getCurrentContext()->gameStateInfo.field) {
    processShift();
    clearCurrentFigureFromField();
    addCurrentFigureToField();
    getCurrentContext()->currentState = GameState_Moving;
  }
}

void stateOfAttaching() {
  if (getCurrentContext()) {
    attachFigureToField();
    const int lines = clearLines();
    countScore(lines);
    if (processGameOver())
      getCurrentContext()->currentState = GameState_GameOver;
    else
      getCurrentContext()->currentState = GameState_Spawn;
  }
}

void stateOfGameOver() {
  if (getCurrentContext()) {
    freeGame();
  }
}

void processShift() {
  if (getCurrentContext() && getCurrentContext()->currentFigure &&
      getCurrentContext()->gameStateInfo.field) {
    if (getCurrentContext()->userInput == Left) {
      moveFigureLeft();
    } else if (getCurrentContext()->userInput == Right) {
      moveFigureRight();
    } else if (getCurrentContext()->userInput == Down) {
      moveFigureDown();
    } else if (getCurrentContext()->userInput == Action) {
      if (!isSquareFigure()) rotationFigure();
    } else if (getCurrentContext()->userInput == Up &&
               getCurrentContext()->goodMode) {
      moveFigureUp();
    } else if (getCurrentContext()->userInput == Respawn &&
               getCurrentContext()->goodMode) {
      processRespawn();
    }
    getCurrentContext()->shiftRequested = false;
  }
}

bool processAttaching() {
  bool willAttach = false;
  if (getCurrentContext()) {
    const int originalY = getCurrentContext()->figureY;

    getCurrentContext()->figureY++;
    willAttach = collision();

    getCurrentContext()->figureY = originalY;
  }
  return willAttach;
}

void processRespawn() {
  clearCurrentFigureFromField();
  stateOfSpawn();
} /**< good mode. */

bool processGameOver() {
  bool willGameOver = false;
  if (getCurrentContext() && getCurrentContext()->gameStateInfo.field) {
    int **field = getCurrentContext()->gameStateInfo.field;

    for (int x = 0; x < FIELD_WIDTH && !willGameOver; x++) {
      if (field[0][x] != 0) willGameOver = true;
    }
  }
  return willGameOver;
}