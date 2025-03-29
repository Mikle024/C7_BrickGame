#include "s21_tests.h"

START_TEST(test_dropNewFigure_positive) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  // Выделяем память для текущей и следующей фигур
  context->currentFigure = createFigure(0);
  context->gameStateInfo.next = createFigure(1);

  // Координаты, куда должна упасть фигура
  int x = 5, y = 3;

  // Вызываем функцию
  dropNewFigure(x, y);

  // Проверяем, что currentFigure обновился на предыдущий next
  ck_assert_ptr_eq(context->currentFigure, context->gameStateInfo.next);

  // Проверяем, что next теперь указывает на новую фигуру
  ck_assert_ptr_nonnull(context->gameStateInfo.next);
  ck_assert_ptr_ne(context->currentFigure, context->gameStateInfo.next);

  // Проверяем координаты
  ck_assert_int_eq(context->figureX, x);
  ck_assert_int_eq(context->figureY, y);
  ck_assert_int_eq(context->oldFigureX, x);
  ck_assert_int_eq(context->oldFigureY, y);

  // Очищаем выделенную память
  freeMatrix(context->currentFigure, FIGURE_SIZE);
  freeMatrix(context->gameStateInfo.next, FIGURE_SIZE);
}
END_TEST

Suite *suiteDropNewFigure(void) {
  Suite *suite = suite_create("suite_dropNewFigure");
  TCase *tc = tcase_create("tc_dropNewFigure");

  tcase_add_test(tc, test_dropNewFigure_positive);

  suite_add_tcase(suite, tc);
  return suite;
}