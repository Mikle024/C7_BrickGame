#include "s21_tests.h"

START_TEST(test_isSquareFigure_true) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  int figurePattern[FIGURE_SIZE][FIGURE_SIZE] = {
      {0, 2, 2, 0}, {0, 2, 2, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  setupGameWithCustomValues(NULL, figurePattern, START_COORD_F_X,
                            START_COORD_F_Y);

  ck_assert_int_eq(isSquareFigure(), true);

  cleanupTest();
}
END_TEST

START_TEST(test_isSquareFigure_false) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  int figurePattern[FIGURE_SIZE][FIGURE_SIZE] = {
      {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  setupGameWithCustomValues(NULL, figurePattern, START_COORD_F_X,
                            START_COORD_F_Y);

  ck_assert_int_eq(isSquareFigure(), false);

  cleanupTest();
}
END_TEST

START_TEST(test_isSquareFigure_null) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  if (context->currentFigure) {
    freeMatrix(context->currentFigure, FIGURE_SIZE);
  }
  context->currentFigure = NULL;

  ck_assert_int_eq(isSquareFigure(), false);

  cleanupTest();
}
END_TEST

Suite *suiteIsSquareFigure(void) {
  Suite *s = suite_create("suite_isSquareFigure");
  TCase *tc_core = tcase_create("tc_isSquareFigure");

  tcase_add_checked_fixture(tc_core, setupTest, cleanupTest);
  tcase_add_test(tc_core, test_isSquareFigure_true);
  tcase_add_test(tc_core, test_isSquareFigure_false);
  tcase_add_test(tc_core, test_isSquareFigure_null);

  suite_add_tcase(s, tc_core);
  return s;
}