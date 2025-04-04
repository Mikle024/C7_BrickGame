#include "s21_tests.h"

START_TEST(test_moveFigureDown_basic) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  int figurePattern[FIGURE_SIZE][FIGURE_SIZE] = {
      {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  setupGameWithCustomValues(NULL, figurePattern, START_COORD_F_X, 1);
  int originalY = context->figureY;

  moveFigureDown();
  ck_assert_int_eq(context->figureY, originalY + 1);
  ck_assert_int_eq(context->oldFigureY, originalY);

  cleanupTest();
}
END_TEST

START_TEST(test_moveFigureDown_collision) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  int figurePattern[FIGURE_SIZE][FIGURE_SIZE] = {
      {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 1}};

  setupGameWithCustomValues(NULL, figurePattern, START_COORD_F_X, FIELD_HEIGHT);
  int originalY = context->figureY;

  moveFigureDown();
  ck_assert_int_eq(context->figureY, originalY);
  ck_assert_int_eq(context->oldFigureY, originalY);

  cleanupTest();
}
END_TEST

START_TEST(test_moveFigureDown_with_blocks) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  int fieldPattern[FIELD_HEIGHT][FIELD_WIDTH] = {0};
  fieldPattern[2][START_COORD_F_X] = 2;

  int figurePattern[FIGURE_SIZE][FIGURE_SIZE] = {
      {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  setupGameWithCustomValues(fieldPattern, figurePattern, START_COORD_F_X, 1);
  int originalY = context->figureY;

  moveFigureDown();
  ck_assert_int_eq(context->figureY, originalY);
  ck_assert_int_eq(context->oldFigureY, originalY);
  ck_assert_int_eq(context->gameStateInfo.field[2][START_COORD_F_X], 2);

  cleanupTest();
}
END_TEST

START_TEST(test_moveFigureDown_edge_case) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  int figurePattern[FIGURE_SIZE][FIGURE_SIZE] = {
      {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  setupGameWithCustomValues(NULL, figurePattern, START_COORD_F_X,
                            FIELD_HEIGHT - 1);
  int originalY = context->figureY;

  moveFigureDown();
  ck_assert_int_eq(context->figureY, originalY);
  ck_assert_int_eq(context->oldFigureY, originalY);

  cleanupTest();
}
END_TEST

Suite *suiteMoveFigureDown(void) {
  Suite *s = suite_create("suite_moveFigureDown");
  TCase *tc = tcase_create("tc_moveFigureDown");

  tcase_add_checked_fixture(tc, setupTest, cleanupTest);
  tcase_add_test(tc, test_moveFigureDown_basic);
  tcase_add_test(tc, test_moveFigureDown_collision);
  tcase_add_test(tc, test_moveFigureDown_with_blocks);
  tcase_add_test(tc, test_moveFigureDown_edge_case);

  suite_add_tcase(s, tc);
  return s;
}
