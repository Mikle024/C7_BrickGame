#include "../inc/s21_brick_game.h"

int main(void) {
  WIN_INIT(50);
  print_overlay();

  initRandom();

  GameInfo_t currentGameInfo = updateCurrentState();

  while (1) {
    if (currentGameInfo.field == NULL || currentGameInfo.next == NULL) {
      printw("EXIT\n");
      break;
    }

    frontPrint(&currentGameInfo);

    int ch = getch();
    if (ch != ERR) {
      bool hold = false;
      switch (ch) {
        case KEY_LEFT:
          userInput(Left, hold);
          break;
        case KEY_RIGHT:
          userInput(Right, hold);
          break;
        case KEY_DOWN:
          userInput(Down, hold);
          break;
        case KEY_UP:
          userInput(Action, hold);
          break;
        case 'p':
          userInput(Pause, hold);
          break;
        case 'q':
          userInput(Terminate, hold);
          break;
        default:
          break;
      }
    }

    currentGameInfo = updateCurrentState();

    refresh();
  }

  endwin();

  return 0;
}