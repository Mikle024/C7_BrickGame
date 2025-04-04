#include "inc/s21_frontend.h"

WinCurses *initCurses() {
  initscr();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  raw();
  noecho();
  cbreak();
  curs_set(0);
  start_color();
  initColors();
  WinCurses *winGame = createFrontend();
  return winGame;
}

WinCurses *createFrontend() {
  WinCurses *winGame = (WinCurses *)malloc(sizeof(WinCurses));
  if (winGame == NULL) {
    return NULL;
  }
  winGame->winBoard = newwin(BOARD_HEIGHT, BOARD_WIDTH, Y_START, X_START);
  winGame->winBrick = newwin(NEXT_HEIGHT, NEXT_WIDTH, NEXT_Y, NEXT_X);
  winGame->winScore = newwin(SCORE_HEIGHT, SCORE_WIDTH, SCORE_Y, SCORE_X);
  winGame->winInput = newwin(INPUT_HEIGHT, INPUT_WIDTH, INPUT_Y, INPUT_X);

  refresh();

  winGame->currentScreen = SCREEN_START;

  box(winGame->winBoard, 0, 0);
  box(winGame->winBrick, 0, 0);
  box(winGame->winScore, 0, 0);
  box(winGame->winInput, 0, 0);
  return winGame;
}

void printFrontend(GameInfo_t *game, WinCurses *winGame) {
  if (winGame) {
    if (winGame->currentScreen == SCREEN_START) {
      printStartDashboard(winGame->winBoard);
    } else if (game && winGame->currentScreen == SCREEN_PAUSE && game->pause) {
      printPauseDashboard(winGame->winBoard);
    } else if (winGame->currentScreen == SCREEN_GAME_OVER) {
      gameOverDashboard(winGame->winBoard);
      clearNext(winGame->winBrick);
      printManagement(winGame->winInput);

    } else if (game && game->field)
      printField(game->field, winGame->winBoard);

    if (game) {
      printManagement(winGame->winInput);
      printScore(game, winGame->winScore);
      if (game->next) {
        printNext(game->next, winGame->winBrick);
      }
    }
    wrefresh(winGame->winBoard);
    wrefresh(winGame->winInput);
    wrefresh(winGame->winBrick);
    wrefresh(winGame->winScore);
  }
}

void printField(int **field, WINDOW *win) {
  if (field && win) {
    for (int i = 0; i < FIELD_HEIGHT; i++) {
      for (int j = 0; j < FIELD_WIDTH; j++) {
        if (field[i][j] == 0) {
          wbkgdset(win, COLOR_PAIR(1));
          mvwprintw(win, i + 1, 2 * j + 1, "%c", ' ');
          mvwprintw(win, i + 1, 2 * j + 2, "%c", ' ');
        } else {
          wbkgdset(win, COLOR_PAIR(field[i][j] + 2));
          mvwprintw(win, i + 1, 2 * j + 1, "%c", ' ');
          mvwprintw(win, i + 1, 2 * j + 2, "%c", ' ');
        }
      }
    }
  }
}

void printStartDashboard(WINDOW *win) {
  wbkgdset(win, COLOR_PAIR(0));
  mvwprintw(win, FIELD_HEIGHT / 2 - 1, (FIELD_WIDTH - 5), "PRESS SPACE");
  mvwprintw(win, FIELD_HEIGHT / 2, (FIELD_WIDTH - 4), "TO START!");
  wrefresh(win);
}

void printPauseDashboard(WINDOW *win) {
  wbkgdset(win, COLOR_PAIR(0));
  mvwprintw(win, FIELD_HEIGHT / 2 - 1, (FIELD_WIDTH - 2), "PAUSE");
  wrefresh(win);
}

void gameOverDashboard(WINDOW *win) {
  wbkgdset(win, COLOR_PAIR(0));

  for (int i = 1; i < BOARD_HEIGHT - 1; i++) {
    for (int j = 1; j < BOARD_WIDTH - 1; j++) {
      mvwprintw(win, i, j, " ");
    }
  }

  mvwprintw(win, F_HEIGHT / 2, F_WIDTH - 4, "GAME OVER!");

  wrefresh(win);
}

void printNext(int **next, WINDOW *win) {
  if (next && win) {
    clearNext(win);

    int minRow = FIGURE_SIZE, maxRow = 0;
    int minCol = FIGURE_SIZE, maxCol = 0;
    bool hasBlocks = false;

    for (int i = 0; i < FIGURE_SIZE; i++) {
      for (int j = 0; j < FIGURE_SIZE; j++) {
        if (next[i][j] != 0) {
          hasBlocks = true;
          if (i < minRow) minRow = i;
          if (i > maxRow) maxRow = i;
          if (j < minCol) minCol = j;
          if (j > maxCol) maxCol = j;
        }
      }
    }

    if (hasBlocks) {
      int figureHeight = maxRow - minRow + 1;
      int figureWidth = maxCol - minCol + 1;

      int centerY = NEXT_HEIGHT / 2;
      int centerX = NEXT_WIDTH / 2;

      int startY = centerY - figureHeight / 2;
      int startX = centerX - figureWidth;

      for (int i = minRow; i <= maxRow; i++) {
        for (int j = minCol; j <= maxCol; j++) {
          if (next[i][j] != 0) {
            wbkgdset(win, COLOR_PAIR(next[i][j] + 2));
            mvwprintw(win, startY + (i - minRow), startX + (j - minCol) * 2,
                      "%c", ' ');
            mvwprintw(win, startY + (i - minRow), startX + (j - minCol) * 2 + 1,
                      "%c", ' ');
          }
        }
      }
    }
  }
}

void printManagement(WINDOW *win) {
  mvwprintw(win, 3, 3, "%s", "Quit(Q)");
  mvwprintw(win, 1, 3, "%s", "Pause(P)");
  mvwprintw(win, 1, 20, "%s", "(R) - Rotate");
  mvwprintw(win, 3, 20, "%s", "DOWN - Drop");
  mvwprintw(win, 5, 20, "%s", "<- -> - move");
  mvwprintw(win, 5, 3, "%s", "by onionyas");
}

void printScore(GameInfo_t *game, WINDOW *win) {
  mvwprintw(win, 1, 2, "%s", "LEVEL:");
  mvwprintw(win, 3, 2, "%d", game->level);

  mvwprintw(win, 5, 2, "%s", "SCORE:");
  mvwprintw(win, 7, 2, "%d  ", game->score);

  mvwprintw(win, 9, 2, "%s", "RECORD:");
  mvwprintw(win, 11, 2, "%d", game->high_score);
}

void clearNext(WINDOW *win) {
  for (int i = 1; i < NEXT_HEIGHT - 1; i++) {
    for (int j = 1; j < NEXT_WIDTH - 1; j++) {
      wbkgdset(win, COLOR_PAIR(1));
      mvwprintw(win, i, j, "%c", ' ');
    }
  }
}

void initColors() {
  short i, j, ck = 1;
  for (i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      init_pair(ck++, i, j);
    }
  }
  init_pair(0, COLOR_WHITE, COLOR_BLACK);
}

void freeCurses(WinCurses *win) {
  if (win) free(win);
  endwin();
}