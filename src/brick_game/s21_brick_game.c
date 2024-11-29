#include "../inc/s21_brick_game.h"

int main(void) {
  // Инициализация ncurses
  WIN_INIT(50);
  print_overlay();

  initRandom();  // Инициализация случайных чисел

  GameInfo_t currentGameInfo = updateCurrentState();

  while (1) {
    // Завершаем игру, если данные некорректны
    if (currentGameInfo.field == NULL || currentGameInfo.next == NULL) {
      printw("EXIT\n");
      break;
    }

    frontPrint(&currentGameInfo);
    // Обновляем состояние игры
    currentGameInfo = updateCurrentState();

    // Управляем скоростью игры
    usleep(100000);  // 100 мс

    // Обновляем экран
    refresh();
  }

  // Завершаем работу ncurses
  endwin();

  return 0;
}

// int main(void) {
//   // Инициализация ncurses
//   //  initscr();    // Инициализация окна
//   //  noecho();     // Отключение отображения ввода
//   //  curs_set(0);  // Скрытие курсора
//
//   initRandom();
//
//   // Инициализация начального состояния игры
//   GameInfo_t currentGameInfo = updateCurrentState();
//
//   while (1) {
//     if (currentGameInfo.field == NULL || currentGameInfo.next == NULL) {
//       printf("EXIT\n");
//       break;
//     }
//
//     // Пример симуляции пользовательского ввода
//     // userInput(Left, false);    // Движение влево
//     // userInput(Action, false);  // Поворот фигуры
//
//     printField(&currentGameInfo);
//     currentGameInfo = updateCurrentState();
//
//     // Добавляем задержку, чтобы контролировать скорость игры
//     //    usleep(100000);  // 100 мс (приблизительно 10 кадров в секунду)
//   }
//
//   // Завершение работы с ncurses
//   //  endwin();
//   return 0;
// }
//
// int main(void) {
//   // Инициализация ncurses
//   initscr();
//   noecho();
//   curs_set(0);
//   nodelay(stdscr, TRUE);
//   keypad(stdscr, TRUE);
//
//   initRandom();  // Инициализация случайных чисел
//
//   // Инициализация контекста игры
//   //    initializeGameContextWrapper();
//   //
//   //    // Получаем начальное состояние игры
//   //    GameContext_t *gameContext = getGameContext(globalContextWrapper);
//   GameInfo_t currentGameInfo = updateCurrentState();
//
//   while (1) {
//     // Завершаем игру, если данные некорректны
//     if (currentGameInfo.field == NULL || currentGameInfo.next == NULL) {
//       printw("EXIT\n");
//       break;
//     }
//
//     // Чтение пользовательского ввода
//     //        int ch = getch();
//     //        switch (ch) {
//     //            case KEY_LEFT:
//     //                userInput(Left, false);
//     //                break;
//     //            case KEY_RIGHT:
//     //                userInput(Right, false);
//     //                break;
//     //            case KEY_DOWN:
//     //                userInput(Down, false);
//     //                break;
//     //            case 'z':  // Вращение
//     //                userInput(Action, false);
//     //                break;
//     //            case 'p':  // Пауза
//     //                userInput(Pause, false);
//     //                break;
//     //            case 'q':  // Завершение игры
//     //                userInput(Terminate, false);
//     //                break;
//     //            default:
//     //                // Игнорируем другие нажатия
//     //                break;
//     //        }
//
//     drawGame(&currentGameInfo);
//     // Обновляем состояние игры
//     currentGameInfo = updateCurrentState();
//
//     // Управляем скоростью игры
//     usleep(100000);  // 100 мс
//
//     // Обновляем экран
//     refresh();
//   }
//
//   // Завершаем работу ncurses
//   endwin();
//
//   //    // Освобождаем ресурсы
//   //    freeGameContextWrapper(globalContextWrapper);
//
//   return 0;
// }
//
// void drawGame(GameInfo_t *gameInfo) {
//   // Очищаем экран и рисуем текущее состояние игры
//   clear();
//   // Верхняя граница
//   for (int i = 0; i < FIELD_WIDTH + 2; i++) {
//     printw("#");
//   }
//   printw("\n");
//
//   // Игровое поле
//   for (int y = 0; y < FIELD_HEIGHT; y++) {
//     printw("#");
//     for (int x = 0; x < FIELD_WIDTH; x++) {
//       if (gameInfo->field[y][x] == 0) {
//         printw(" ");
//       } else {
//         printw("#");
//       }
//     }
//     printw("#\n");
//   }
//
//   // Нижняя граница
//   for (int i = 0; i < FIELD_WIDTH + 2; i++) {
//     printw("#");
//   }
//   printw("\n");
//
//   // Отображение информации о состоянии игры
//   printw("Score: %d\n", gameInfo->score);
//   printw("High Score: %d\n", gameInfo->high_score);
//   printw("Level: %d\n", gameInfo->level);
//   printw("Speed: %d\n", gameInfo->speed);
// }
