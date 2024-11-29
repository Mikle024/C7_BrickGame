#include "../s21_tests.h"

START_TEST(test_positive_create_figure) {
  int **actualFigure = createFigure();

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