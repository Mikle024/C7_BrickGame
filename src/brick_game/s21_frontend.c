#include "../inc/s21_frontend.h"

// frogger
void print_overlay(void) {
  print_rectangle(0, FIELD_HEIGHT + 1, 0, BOARD_M + 1);
  print_rectangle(0, FIELD_HEIGHT + 1, BOARD_M + 2, BOARD_M + HUD_WIDTH + 3);

  print_rectangle(1, 3, BOARD_M + 3, BOARD_M + HUD_WIDTH + 2);
  print_rectangle(4, 6, BOARD_M + 3, BOARD_M + HUD_WIDTH + 2);
  print_rectangle(7, 9, BOARD_M + 3, BOARD_M + HUD_WIDTH + 2);
  print_rectangle(10, 12, BOARD_M + 3, BOARD_M + HUD_WIDTH + 2);
  print_rectangle(13, 20, BOARD_M + 3, BOARD_M + HUD_WIDTH + 2);

  //  MVPRINTW(2, BOARD_M + 5, "LEVEL");
  //  MVPRINTW(5, BOARD_M + 8, "SCORE");
  //  MVPRINTW(8, BOARD_M + 5, "SPEED");
  //  MVPRINTW(11, BOARD_M + 5, "LIVES");

  MVPRINTW(BOARD_N / 2, (BOARD_M - INTRO_MESSAGE_LEN) / 2 + 1, INTRO_MESSAGE);
}

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  MVADDCH(top_y, left_x, ACS_ULCORNER);

  int i = left_x + 1;

  for (; i < right_x; i++) MVADDCH(top_y, i, ACS_HLINE);
  MVADDCH(top_y, i, ACS_URCORNER);

  for (int i = top_y + 1; i < bottom_y; i++) {
    MVADDCH(i, left_x, ACS_VLINE);
    MVADDCH(i, right_x, ACS_VLINE);
  }

  MVADDCH(bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; i++) MVADDCH(bottom_y, i, ACS_HLINE);
  MVADDCH(bottom_y, i, ACS_LRCORNER);
}
// end frogger

void frontPrint(GameInfo_t *gameInfo) {
  // Очищаем экран
  clear();

  // Отображение интерфейса (рамок, HUD и сообщений)
  print_overlay();

  // Рисуем игровое поле внутри заданной рамки
  for (int y = 0; y < FIELD_HEIGHT; y++) {
    for (int x = 0; x < FIELD_WIDTH; x++) {
      if (gameInfo->field[y][x] == 0) {
        MVPRINTW(1 + y, 1 + x, " ");  // Пустая клетка
      } else {
        MVPRINTW(1 + y, 1 + x, "#");  // Заполненная клетка
      }
    }
  }

  // Обновляем информацию в HUD
  MVPRINTW(2, BOARD_M + 7, "LEVEL: %d", gameInfo->level);
  MVPRINTW(5, BOARD_M + 7, "SCORE: %d", gameInfo->score);
  MVPRINTW(8, BOARD_M + 7, "SPEED: %d", gameInfo->speed);
  MVPRINTW(11, BOARD_M + 7, "LIVES: %d", 1);
  MVPRINTW(14, BOARD_M + 5, "NEXT FIGURE:");

  //    for (int y = 0; y < FIELD_HEIGHT; y++) {
  //        for (int x = 0; x < FIELD_WIDTH; x++) {
  //            if (gameInfo->next[y][x] == 0) {
  //                MVPRINTW(14 + y, BOARD_M + 5 + x, " ");  // Пустая клетка
  //            } else {
  //                MVPRINTW(14 + y, BOARD_M + 5 + x, "#");  // Заполненная
  //                клетка
  //            }
  //        }
  //    }

  // Обновляем экран
  refresh();
}

// void printField(GameInfo_t *gameInfo) {
//   //  clear();  // Очистить экран
//
//   printf("\033[H\033[J");
//
//   // Печать игрового поля
//   //  for (int y = 0; y < FIELD_HEIGHT; y++) {
//   //    for (int x = 0; x < FIELD_WIDTH; x++) {
//   //      if (gameInfo->field[y][x] == 0) {
//   //        mvprintw(y, x, ".");  // Пустая ячейка
//   //      } else {
//   //        mvprintw(y, x, "#");  // Заполненная ячейка
//   //      }
//   //    }
//   //  }
//
//   // Печатаем верхнюю границу
//   for (int i = 0; i < FIELD_WIDTH + 2; i++) {
//     printf("#");
//   }
//   printf("\n");
//
//   // Печать игрового поля
//   for (int y = 0; y < FIELD_HEIGHT; y++) {
//     printf("#");  // Левая граница
//     for (int x = 0; x < FIELD_WIDTH; x++) {
//       if (gameInfo->field[y][x] == 0) {
//         printf(".");  // Пустая ячейка
//       } else {
//         printf("#");  // Заполненная ячейка
//       }
//     }
//     printf("#\n");  // Правая граница
//   }
//
//   // Печать нижней границы
//   for (int i = 0; i < FIELD_WIDTH + 2; i++) {
//     printf("#");
//   }
//   printf("\n");
//
//   // Печать информации о счёте и уровне ниже поля
//   //  mvprintw(FIELD_HEIGHT + 1, 0, "Score: %d", gameInfo->score);
//   //  mvprintw(FIELD_HEIGHT + 2, 0, "High Score: %d", gameInfo->high_score);
//   //  mvprintw(FIELD_HEIGHT + 3, 0, "Level: %d", gameInfo->level);
//   //  mvprintw(FIELD_HEIGHT + 4, 0, "Speed: %d", gameInfo->speed);
//
//   // Печать информации о счёте и уровне
//   printf("Score: %d\n", gameInfo->score);
//   printf("High Score: %d\n", gameInfo->high_score);
//   printf("Level: %d\n", gameInfo->level);
//   printf("Speed: %d\n", gameInfo->speed);
//
//   //    refresh();  // Обновление экрана
// }