#include "s21_tests.h"

START_TEST(test_moveFigureRight_basic) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  int figurePattern[FIGURE_SIZE][FIGURE_SIZE] = {
      {0, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  setupGameWithCustomValues(NULL, figurePattern, 5, 0);
  int originalX = context->figureX;

  moveFigureRight();
  ck_assert_int_eq(context->figureX, originalX + 1);
  ck_assert_int_eq(context->oldFigureX, originalX);

  cleanupTest();
}
END_TEST

START_TEST(test_moveFigureRight_collision) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  int figurePattern[FIGURE_SIZE][FIGURE_SIZE] = {
      {0, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  setupGameWithCustomValues(NULL, figurePattern, FIELD_WIDTH - FIGURE_SIZE, 0);
  int originalX = context->figureX;

  moveFigureRight();
  ck_assert_int_eq(context->figureX, originalX);
  ck_assert_int_eq(context->oldFigureX, originalX);

  cleanupTest();
}
END_TEST

START_TEST(test_moveFigureRight_with_blocks) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  int fieldPattern[FIELD_HEIGHT][FIELD_WIDTH] = {0};
  fieldPattern[0][6] = 2;

  int figurePattern[FIGURE_SIZE][FIGURE_SIZE] = {
      {0, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  setupGameWithCustomValues(fieldPattern, figurePattern, 2, 0);
  int originalX = context->figureX;

  moveFigureRight();
  ck_assert_int_eq(context->figureX, originalX);
  ck_assert_int_eq(context->oldFigureX, originalX);

  cleanupTest();
}
END_TEST

START_TEST(test_moveFigureRight_edge_case) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  int figurePattern[FIGURE_SIZE][FIGURE_SIZE] = {
      {0, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  setupGameWithCustomValues(NULL, figurePattern, 0, 0);
  int originalX = context->figureX;

  moveFigureRight();
  ck_assert_int_eq(context->figureX, originalX + 1);
  ck_assert_int_eq(context->oldFigureX, originalX);

  cleanupTest();
}
END_TEST

Suite *suiteMoveFigureRight(void) {
  Suite *s = suite_create("suite_moveFigureRight");
  TCase *tc = tcase_create("tc_moveFigureRight");

  tcase_add_checked_fixture(tc, setupTest, cleanupTest);
  tcase_add_test(tc, test_moveFigureRight_basic);
  tcase_add_test(tc, test_moveFigureRight_collision);
  tcase_add_test(tc, test_moveFigureRight_with_blocks);
  tcase_add_test(tc, test_moveFigureRight_edge_case);

  suite_add_tcase(s, tc);
  return s;
}