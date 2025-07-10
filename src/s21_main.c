#include "s21_main.h"

#include "gui/cli/inc/s21_frontend.h"
#include "gui/cli/inc/s21_frontend_defs.h"

int main(void) {
  WinCurses *winGame = initCurses();
  if (winGame) {
    gameLoop(winGame);
    freeCurses(winGame);
  }
  return 0;
}

void gameLoop(WinCurses *winGame) {
  GameInfo_t currentGameInfo = initializeGameState();
  int lastKey = ERR;
  int ch = ERR;
  bool quitGame = false;

  while (currentGameInfo.field != NULL && currentGameInfo.next != NULL &&
         !quitGame) {
    renderGameState(&currentGameInfo, winGame);
    ch = getch();
    if (ch == 'q') {
      userInput(Terminate, (ch == lastKey));
      quitGame = true;
    } else if (ch != ERR) {
      handleUserInput(ch, lastKey, winGame);
      lastKey = ch;
    }

    if (!quitGame) {
      updateGameState(&currentGameInfo, &lastKey, ch);
      napms(GAME_LOOP_DELAY);
    }
  }

  if (!quitGame) {
    handleGameOver(&currentGameInfo, winGame);
  }
}

GameInfo_t initializeGameState(void) { return updateCurrentState(); }

void renderGameState(GameInfo_t *gameInfo, WinCurses *winGame) {
  printFrontend(gameInfo, winGame);
}

int handleUserInput(const int ch, const int lastKey, WinCurses *winGame) {
  bool hold = (ch == lastKey);

  switch (ch) {
    case ' ':
      userInput(Start, hold);
      if (winGame->currentScreen != SCREEN_PAUSE)
        winGame->currentScreen = SCREEN_GAME;
      break;
    case KEY_LEFT:
      userInput(Left, hold);
      break;
    case KEY_RIGHT:
      userInput(Right, hold);
      break;
    case KEY_DOWN:
      userInput(Down, hold);
      break;
    case KEY_UP: // god mode
      userInput(Up, hold); // god mode
      break; // god mode
    case 'g': // god mode
      userInput(Good_Mode, hold); // god mode
      break; // god mode
    case 'p':
      if (winGame->currentScreen != SCREEN_START) {
        userInput(Pause, hold);
        winGame->currentScreen = SCREEN_PAUSE;
      }
      break;
    case 'r':
      userInput(Action, hold);
      break;
    default:
      break;
  }

  return 0;
}

void updateGameState(GameInfo_t *gameInfo, int *lastKey, int ch) {
  *lastKey = (ch != ERR) ? ch : -1;
  *gameInfo = updateCurrentState();
}

void handleGameOver(GameInfo_t *gameInfo, WinCurses *winGame) {
  if (gameInfo->field == NULL || gameInfo->next == NULL) {
    winGame->currentScreen = SCREEN_GAME_OVER;
    printFrontend(NULL, winGame);
    napms(3000);
  }
}