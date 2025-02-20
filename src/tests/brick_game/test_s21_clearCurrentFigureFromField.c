#include "../s21_tests.h"

START_TEST(test_positive_clear_I_figure) {
  GameInfo_t actualGame = updateCurrentState();
  GameInfo_t expectedGame = updateCurrentState();

  for (int i = 0; i < FIELD_HEIGHT; i++) {
    static const int patternFigure[FIGURE_COUNT][FIGURE_SIZE][FIGURE_SIZE] = {
        // I
        {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}};

    actualGame.field[i] = (int *)malloc(FIELD_WIDTH * sizeof(int));

    for (int j = 0; j < FIELD_WIDTH; j++) {
      actualGame.field[i][j] = 0;

      if (i < FIGURE_SIZE && j >= FIELD_WIDTH / 2 - FIGURE_SIZE / 2 &&
          j < FIELD_WIDTH / 2 + FIGURE_SIZE / 2) {
        actualGame.field[i][j] =
            patternFigure[0][i][j - (FIELD_WIDTH / 2 - FIGURE_SIZE / 2)];
      }
    }
  }

  clearCurrentFigureFromField(context);

  for (int i = 0; i < FIELD_HEIGHT; i++) {
    expectedGame.field[i] = (int *)malloc(FIELD_WIDTH * sizeof(int));
    for (int j = 0; j < FIELD_WIDTH; j++) {
      expectedGame.field[i][j] = 0;
    }
  }

  ck_assert_ptr_nonnull(actualFigure);  // Убедимся, что newFigure не равен NULL

  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      ck_assert_int_eq(actualFigure[i][j],
                       0);  // Проверяем инициализацию значений
    }
  }

  for (int i = 0; i < FIGURE_SIZE; i++) {
    free(actualFigure[i]);
  }
  free(actualFigure);
}
END_TEST

Suite *suiteCreateFigure(void) {
  Suite *suite = suite_create("suite_createFigure");
  TCase *tc = tcase_create("tc_createFigure");

  tcase_add_test(tc, test_positive_create_figure);

  suite_add_tcase(suite, tc);
  return suite;
}

// START_TEST(test_positive_clear_I_figure) {
//     GameInfo_t actualGame = updateCurrentState();
//
//     actualGame.field = (int **)malloc(FIELD_HEIGHT * sizeof(int *));
//     for (int i = 0; i < FIELD_HEIGHT; i++) {
//         actualGame.field[i] = (int *) malloc(FIELD_WIDTH * sizeof(int));
//         for (int j = 0; j < FIELD_WIDTH; j++) {
//             actualGame.field[i][j] = 0;
//         }
//     }
//
//     static const int patternFigure[FIGURE_COUNT][FIGURE_SIZE][FIGURE_SIZE] =
//     {
//         // I
//         {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
//         // O
//         {{0, 2, 2, 0}, {0, 2, 2, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
//         // T
//         {{0, 0, 0, 0}, {3, 3, 3, 0}, {0, 3, 0, 0}, {0, 0, 0, 0}},
//         // L
//         {{0, 4, 0, 0}, {0, 4, 0, 0}, {0, 4, 4, 0}, {0, 0, 0, 0}},
//         // J
//         {{0, 0, 5, 0}, {0, 0, 5, 0}, {0, 5, 5, 0}, {0, 0, 0, 0}},
//         // S
//         {{0, 0, 0, 0}, {0, 0, 6, 6}, {0, 6, 6, 0}, {0, 0, 0, 0}},
//         // Z
//         {{0, 0, 0, 0}, {7, 7, 0, 0}, {0, 7, 7, 0}, {0, 0, 0, 0}}};
//     // Создание новой фигуры
//     int **newFigure = createFigure();
//
//     // Копирование данных из паттерна в новую фигуру
//     for (int i = 0; i < FIGURE_SIZE; i++) {
//         for (int j = 0; j < FIGURE_SIZE; j++) {
//             newFigure[i][j] = patternFigure[figureNum][i][j];
//         }
//     }
//
//
//     ck_assert_ptr_nonnull(actualFigure);  // Убедимся, что newFigure не равен
//     NULL
//
//     for (int i = 0; i < FIGURE_SIZE; i++) {
//         for (int j = 0; j < FIGURE_SIZE; j++) {
//             ck_assert_int_eq(actualFigure[i][j],
//                              0);  // Проверяем инициализацию значений
//         }
//     }
//
//     for (int i = 0; i < FIGURE_SIZE; i++) {
//         free(actualFigure[i]);
//     }
//     free(actualFigure);
// }
// END_TEST