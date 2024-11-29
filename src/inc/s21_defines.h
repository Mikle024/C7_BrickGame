#ifndef S21_DEFINES_H
#define S21_DEFINES_H

#include <ncurses.h>

#define FIELD_WIDTH 10   // Ширина поля
#define FIELD_HEIGHT 20  // Высота поля

#define FIGURE_SIZE 4   // Размер фигур
#define FIGURE_COUNT 7  // Количество фигур

#define STATE_COUNT 6     // Количество состояний
#define TICKS_PER_MOVE 1  // Определяет частоту перемещения фигуры вниз

// frogger
// Функция для инициализации ncurses
#define WIN_INIT(time)    \
  {                       \
    initscr();            \
    noecho();             \
    curs_set(0);          \
    keypad(stdscr, TRUE); \
    timeout(time);        \
  }

// nodelay(stdscr, TRUE);  \
// keypad(stdscr, TRUE);   \

// Макросы и константы
#define BOARDS_BEGIN 2
#define INTRO_MESSAGE_LEN 20
#define ROWS_MAP FIELD_HEIGHT
#define MAP_PADDING 3
#define BOARD_N (ROWS_MAP + MAP_PADDING * 2)
#define BOARD_M FIELD_WIDTH
#define HUD_WIDTH 15
#define INTRO_MESSAGE "Press ENTER to start!"

#define MVPRINTW(y, x, ...) \
  mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), __VA_ARGS__)
#define MVADDCH(y, x, c) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), c)

// end frogger

#endif
