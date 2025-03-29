#include "s21_tests.h"

START_TEST(test_processShift_left) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  // Устанавливаем фигуру в позицию
  context->figureX = 5;
  context->userInput = Left;
  context->shiftRequested = true;

  processShift();

  // Ожидаем, что фигура сдвинулась влево
  ck_assert_int_eq(context->figureX, 4);
}
END_TEST

START_TEST(test_processShift_right) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  context->figureX = 5;
  context->userInput = Right;
  context->shiftRequested = true;

  processShift();

  // Ожидаем, что фигура сдвинулась вправо
  ck_assert_int_eq(context->figureX, 6);
}
END_TEST

START_TEST(test_processShift_down) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  context->figureY = 3;
  context->userInput = Down;
  context->shiftRequested = true;

  processShift();

  // Ожидаем, что фигура упала вниз
  ck_assert_int_eq(context->figureY, 4);
}
END_TEST

START_TEST(test_processShift_rotate) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  context->userInput = Action;
  context->shiftRequested = true;

  // Переопределим поведение isSquareFigure для теста
  context->currentFigure = createMatrix(FIGURE_SIZE, FIGURE_SIZE);
  // Создаем не квадратную фигуру (значение 1 вместо 2)
  context->currentFigure[1][1] = 1;

  processShift();

  // Проверяем, что shiftRequested сбрасывается
  ck_assert_int_eq(context->shiftRequested, false);
  
  // Очистка
  freeMatrix(context->currentFigure, FIGURE_SIZE);
}
END_TEST

Suite *suiteProcessShift(void) {
  Suite *s = suite_create("suite_processShift");
  TCase *tc_core = tcase_create("tc_processShift");

  tcase_add_test(tc_core, test_processShift_left);
  tcase_add_test(tc_core, test_processShift_right);
  tcase_add_test(tc_core, test_processShift_down);
  tcase_add_test(tc_core, test_processShift_rotate);

  suite_add_tcase(s, tc_core);
  return s;
}