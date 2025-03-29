#include "inc/s21_tetris.h"

GameInfo_t updateCurrentState() {
  GameContext_t *gameContext = getCurrentContext();
  transitionToState();
  GameInfo_t currentGameInfo = gameContext->gameStateInfo;
  return currentGameInfo;
}

void userInput(UserAction_t action, bool hold) {
  GameContext_t *context = getCurrentContext();

  switch (action) {
    case Start:
      if (!hold && context->currentState == GameState_Start)
        context->gameStateInfo.pause = 0;
      break;
    case Left:
      if (context->currentState == GameState_Moving) {
        context->shiftRequested = true;
        context->userInput = Left;
      }
      break;
    case Right:
      if (context->currentState == GameState_Moving) {
        context->shiftRequested = true;
        context->userInput = Right;
      }
      break;
    case Down:
      if (context->currentState == GameState_Moving) {
        context->shiftRequested = true;
        context->userInput = Down;
      }
      break;
    case Action:
      if (!hold && context->currentState == GameState_Moving) {
        context->shiftRequested = true;
        context->userInput = Action;
      }
      break;
    case Pause:
      if (!hold) context->gameStateInfo.pause = !context->gameStateInfo.pause;
      break;
    case Terminate:
      if (!hold) {
        context->shiftRequested = true;
        context->userInput = Terminate;
      }
      break;
    default:
      break;
  }
}