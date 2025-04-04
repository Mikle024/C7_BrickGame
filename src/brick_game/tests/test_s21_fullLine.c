#include "s21_tests.h"

START_TEST(test_fullLine_true) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  if (context->gameStateInfo.field) {
    freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  }
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);

  int testLine = 5;
  for (int j = 0; j < FIELD_WIDTH; j++) {
    context->gameStateInfo.field[testLine][j] = 1;
  }

  ck_assert_int_eq(fullLine(testLine), true);

  cleanupTest();
}
END_TEST

START_TEST(test_fullLine_false) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  if (context->gameStateInfo.field) {
    freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  }
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);

  int testLine = 5;
  for (int j = 0; j < FIELD_WIDTH - 1; j++) {
    context->gameStateInfo.field[testLine][j] = 1;
  }
  context->gameStateInfo.field[testLine][FIELD_WIDTH - 1] = 0;

  ck_assert_int_eq(fullLine(testLine), false);

  cleanupTest();
}
END_TEST

START_TEST(test_fullLine_empty) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  if (context->gameStateInfo.field) {
    freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  }
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);

  int testLine = 5;

  ck_assert_int_eq(fullLine(testLine), false);

  cleanupTest();
}
END_TEST

START_TEST(test_fullLine_partially_filled) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  if (context->gameStateInfo.field) {
    freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  }
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);

  int testLine = 5;
  for (int j = 0; j < FIELD_WIDTH / 2; j++) {
    context->gameStateInfo.field[testLine][j] = 1;
  }

  ck_assert_int_eq(fullLine(testLine), false);

  cleanupTest();
}
END_TEST

START_TEST(test_fullLine_middle_empty) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  if (context->gameStateInfo.field) {
    freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  }
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);

  int testLine = 5;
  for (int j = 0; j < FIELD_WIDTH; j++) {
    context->gameStateInfo.field[testLine][j] = 1;
  }
  context->gameStateInfo.field[testLine][FIELD_WIDTH / 2] = 0;

  ck_assert_int_eq(fullLine(testLine), false);

  cleanupTest();
}
END_TEST

Suite *suiteFullLine(void) {
  Suite *s = suite_create("suite_fullLine");
  TCase *tc = tcase_create("tc_fullLine");

  tcase_add_checked_fixture(tc, setupTest, cleanupTest);
  tcase_add_test(tc, test_fullLine_true);
  tcase_add_test(tc, test_fullLine_false);
  tcase_add_test(tc, test_fullLine_empty);
  tcase_add_test(tc, test_fullLine_partially_filled);
  tcase_add_test(tc, test_fullLine_middle_empty);

  suite_add_tcase(s, tc);
  return s;
}
