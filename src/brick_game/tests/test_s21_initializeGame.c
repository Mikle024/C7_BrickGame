#include "s21_tests.h"

START_TEST(test_initializeGame_basic) {
  GameContext_t context;
  bool checkInit = false;
  
  // Вызываем функцию инициализации
  initializeGame(&context, &checkInit);
  
  // Проверяем, что флаг инициализации установлен
  ck_assert_int_eq(checkInit, true);
  
  // Проверяем, что все поля инициализированы корректно
  ck_assert_ptr_nonnull(context.gameStateInfo.field);
  ck_assert_ptr_nonnull(context.gameStateInfo.next);
  ck_assert_ptr_nonnull(context.currentFigure);
  
  ck_assert_int_eq(context.currentState, GameState_Start);
  ck_assert_int_eq(context.gameStateInfo.score, 0);
  ck_assert_int_eq(context.gameStateInfo.level, START_LEVEL);
  ck_assert_int_eq(context.gameStateInfo.speed, START_DELAY);
  ck_assert_int_eq(context.gameStateInfo.pause, 1);
  
  ck_assert_int_eq(context.figureX, START_COORD_F_X);
  ck_assert_int_eq(context.figureY, START_COORD_F_Y);
  ck_assert_int_eq(context.oldFigureX, START_COORD_F_X);
  ck_assert_int_eq(context.oldFigureY, START_COORD_F_Y);
  ck_assert_int_eq(context.exit, 0);
  ck_assert_int_eq(context.lastTime, 0);
  
  // Освобождаем ресурсы
  freeMatrix(context.gameStateInfo.field, FIELD_HEIGHT);
  freeMatrix(context.gameStateInfo.next, FIGURE_SIZE);
  freeMatrix(context.currentFigure, FIGURE_SIZE);
}
END_TEST

START_TEST(test_initializeGame_field_dimensions) {
  GameContext_t context;
  bool checkInit = false;
  
  // Вызываем функцию инициализации
  initializeGame(&context, &checkInit);
  
  // Проверяем размеры поля
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    ck_assert_ptr_nonnull(context.gameStateInfo.field[i]);
    for (int j = 0; j < FIELD_WIDTH; j++) {
      // Проверяем, что все ячейки изначально пусты
      ck_assert_int_eq(context.gameStateInfo.field[i][j], 0);
    }
  }
  
  // Освобождаем ресурсы
  freeMatrix(context.gameStateInfo.field, FIELD_HEIGHT);
  freeMatrix(context.gameStateInfo.next, FIGURE_SIZE);
  freeMatrix(context.currentFigure, FIGURE_SIZE);
}
END_TEST

// Набор тестов для функции initializeGame
Suite *suiteInitializeGame(void) {
  Suite *s = suite_create("suite_initializeGame");
  TCase *tc = tcase_create("tc_initializeGame");
  
  tcase_add_test(tc, test_initializeGame_basic);
  tcase_add_test(tc, test_initializeGame_field_dimensions);
  
  suite_add_tcase(s, tc);
  return s;
} 