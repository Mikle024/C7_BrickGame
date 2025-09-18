#include "inc/s21_tetris.h"

GameInfo_t updateCurrentState() {
  if (getCurrentContext()) transitionToState();
  return getCurrentContext()->gameStateInfo;
}

void userInput(const UserAction_t action, const bool hold) {
  if (getCurrentContext()) {
    switch (action) {
      case Start:
        if (getCurrentContext()->currentState == GameState_Start)
          getCurrentContext()->gameStateInfo.pause = 0;
        break;
      case Left:
        if (getCurrentContext()->currentState == GameState_Moving) {
          getCurrentContext()->shiftRequested = true;
          getCurrentContext()->userInput = Left;
        }
        break;
      case Right:
        if (getCurrentContext()->currentState == GameState_Moving) {
          getCurrentContext()->shiftRequested = true;
          getCurrentContext()->userInput = Right;
        }
        break;
      case Down:
        if (getCurrentContext()->currentState == GameState_Moving) {
          getCurrentContext()->shiftRequested = true;
          getCurrentContext()->userInput = Down;
        }
        break;
      case Up:
        if (getCurrentContext()->currentState == GameState_Moving) {
          getCurrentContext()->shiftRequested = true;
          getCurrentContext()->userInput = Up;
        }
        break;
      case Respawn:
        if (getCurrentContext()->currentState == GameState_Moving) {
          getCurrentContext()->shiftRequested = true;
          getCurrentContext()->userInput = Respawn;
        }
        break;
      case Good_Mode:
        if (getCurrentContext()->currentState == GameState_Moving) {
          getCurrentContext()->goodMode = !getCurrentContext()->goodMode;
        }
        break;
      case Action:
        if (!hold && getCurrentContext()->currentState == GameState_Moving) {
          getCurrentContext()->shiftRequested = true;
          getCurrentContext()->userInput = Action;
        }
        break;
      case Pause:
        if (!hold && getCurrentContext()->currentState == GameState_Moving)
          getCurrentContext()->gameStateInfo.pause =
              !getCurrentContext()->gameStateInfo.pause;
        break;
      case Terminate:
        if (!hold) {
          freeGame();
        }
        break;
      default:
        break;
    }
  }
}