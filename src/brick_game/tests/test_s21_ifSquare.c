#include "s21_tests.h"

START_TEST(test_ifSquare_true) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  // Создаем тестовую фигуру 4x4 (пусть это будет квадрат с 2)
  context->currentFigure = calloc(FIGURE_SIZE, sizeof(int *));
  for (int i = 0; i < FIGURE_SIZE; i++) {
    context->currentFigure[i] = calloc(FIGURE_SIZE, sizeof(int));
  }

  // Задаем фигуру O-образного типа (квадрат)
  context->currentFigure[1][1] = 2;
  context->currentFigure[1][2] = 2;
  context->currentFigure[2][1] = 2;
  context->currentFigure[2][2] = 2;

  // Проверяем, что функция ifSquare() возвращает true
  ck_assert_int_eq(ifSquare(), true);

  // Очистка памяти
  freeMatrix(context->currentFigure, FIGURE_SIZE);
}
END_TEST

START_TEST(test_ifSquare_false) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  // Создаем тестовую фигуру 4x4 без 2
  context->currentFigure = calloc(FIGURE_SIZE, sizeof(int *));
  for (int i = 0; i < FIGURE_SIZE; i++) {
    context->currentFigure[i] = calloc(FIGURE_SIZE, sizeof(int));
  }

  // Заполняем случайными значениями, но без 2
  context->currentFigure[1][1] = 1;
  context->currentFigure[1][2] = 3;
  context->currentFigure[2][1] = 3;
  context->currentFigure[2][2] = 1;

  // Проверяем, что ifSquare() возвращает false
  ck_assert_int_eq(ifSquare(), false);

  // Очистка памяти
  freeMatrix(context->currentFigure, FIGURE_SIZE);
}
END_TEST

Suite *suiteIfSquare(void) {
  Suite *s = suite_create("suite_ifSquare");
  TCase *tc_core = tcase_create("tc_ifSquare");

  tcase_add_test(tc_core, test_ifSquare_true);
  tcase_add_test(tc_core, test_ifSquare_false);

  suite_add_tcase(s, tc_core);
  return s;
}