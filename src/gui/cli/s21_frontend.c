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

  box(winGame->winBoard, 0, 0);
  box(winGame->winBrick, 0, 0);
  box(winGame->winScore, 0, 0);
  box(winGame->winInput, 0, 0);
  return winGame;
}

void printFrontend(GameInfo_t *game, WinCurses *winGame) {
  printField(game->field, winGame->winBoard);
  printManagement(winGame->winInput);
  printScore(game, winGame->winScore);
  clearNext(winGame->winBrick, FIGURE_SIZE, FIGURE_SIZE);
  printNext(game->next, winGame->winBrick);
  if (game->pause) printPauseDashboard(winGame->winBoard);

  wrefresh(winGame->winBoard);
  wrefresh(winGame->winInput);
  wrefresh(winGame->winBrick);
  wrefresh(winGame->winScore);
}

void printField(int **field, WINDOW *win) {
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

void printNext(int **next, WINDOW *win) {
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (next[i][j] != 0) {
        wbkgdset(win, COLOR_PAIR(next[i][j] + 2));
        mvwprintw(win, i + 1 + 1, 2 * j + 1 + 1, "%c", ' ');
        mvwprintw(win, i + 1 + 1, 2 * j + 2 + 1, "%c", ' ');
      }
    }
  }
}

void clearNext(WINDOW *win, int y_pos, int x_pos) {
  for (int i = 0; i <= y_pos; i++) {
    for (int j = 0; j <= x_pos; j++) {
      wbkgdset(win, COLOR_PAIR(1));
      mvwprintw(win, i + 1 + 1, 2 * j + 2 + 1, "%c", ' ');
      mvwprintw(win, i + 1 + 1, 2 * j + 1 + 1, "%c", ' ');
    }
  }
}

void printManagement(WINDOW *win) {
  mvwprintw(win, 3, 3, "%s", "Quit(Q)");
  mvwprintw(win, 1, 3, "%s", "Pause(SPACE)");
  mvwprintw(win, 1, 20, "%s", "UP - Rotate");
  mvwprintw(win, 3, 20, "%s", "DOWN - Drop");
  mvwprintw(win, 5, 20, "%s", "<- -> - move");
  mvwprintw(win, 5, 3, "%s", "GIT GUD");
}

void printStartDashboard(WINDOW *win) {
  mvwprintw(win, FIELD_HEIGHT / 2 - 1, (FIELD_WIDTH - 6), "PRESS ANY KEY");
  mvwprintw(win, FIELD_HEIGHT / 2, (FIELD_WIDTH - 4), "TO START!");
  wrefresh(win);
}

void printPauseDashboard(WINDOW *win) {
  wbkgdset(win, COLOR_PAIR(0));
  mvwprintw(win, FIELD_HEIGHT / 2 - 1, (FIELD_WIDTH - 2), "PAUSE");
  wrefresh(win);
}

void printScore(GameInfo_t *game, WINDOW *win) {
  mvwprintw(win, 1, 2, "%s", "level:");
  mvwprintw(win, 3, 2, "%d", game->level);

  mvwprintw(win, 5, 2, "%s", "score:");
  mvwprintw(win, 7, 2, "%d  ", game->score);

  mvwprintw(win, 9, 2, "%s", "record:");
  mvwprintw(win, 11, 2, "%d", game->high_score);
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

void gameOverDashboard(WINDOW *win) {
  wbkgdset(win, COLOR_PAIR(0));
  mvwprintw(win, F_HEIGHT / 2 - 1, (F_WIDTH - 2), "GAME OVER!");
  wrefresh(win);
}