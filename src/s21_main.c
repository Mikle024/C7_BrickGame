#include "gui/cli/inc/s21_frontend.h"

void gameLoop(WinCurses *winGame);

int main(void) {
  WinCurses *winGame = initCurses();
  gameLoop(winGame);
  if (winGame) freeCurses(winGame);

  return 0;
}

void gameLoop(WinCurses *winGame) {
  GameInfo_t currentGameInfo = updateCurrentState();
  int lastKey = ERR;
  while (currentGameInfo.field != NULL || currentGameInfo.next != NULL) {
    printFrontend(&currentGameInfo, winGame);

    int ch = getch();
    bool hold = (ch == lastKey);

    if (ch != ERR) {
      lastKey = ch;
      switch (ch) {
        case ' ':
          userInput(Start, hold);
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
        case 'p':
          userInput(Pause, hold);
          break;
        case KEY_UP:
          userInput(Action, hold);
          break;
        default:
          break;
      }
    }

    lastKey = (ch != ERR) ? ch : -1;
    currentGameInfo = updateCurrentState();
    napms(16);
  }
}