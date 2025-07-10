#include "s21_tests.h"

START_TEST(test_clearLines_one_line) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  if (context->gameStateInfo.field) {
    freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  }
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);

  int fullLine = 5;
  for (int j = 0; j < FIELD_WIDTH; j++) {
    context->gameStateInfo.field[fullLine][j] = 1;
  }

  int clearedLines = clearLines();
  ck_assert_int_eq(clearedLines, 1);

  for (int j = 0; j < FIELD_WIDTH; j++) {
    ck_assert_int_eq(context->gameStateInfo.field[fullLine][j], 0);
  }

  cleanupTest();
}
END_TEST

START_TEST(test_clearLines_multiple_lines) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  if (context->gameStateInfo.field) {
    freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  }
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);

  int fullLines[] = {3, 5, 8};
  int numFullLines = sizeof(fullLines) / sizeof(fullLines[0]);

  for (int i = 0; i < numFullLines; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      context->gameStateInfo.field[fullLines[i]][j] = 1;
    }
  }

  int clearedLines = clearLines();
  ck_assert_int_eq(clearedLines, numFullLines);

  cleanupTest();
}
END_TEST

START_TEST(test_clearLines_no_lines) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  if (context->gameStateInfo.field) {
    freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  }
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);

  int nonFullLine = 5;
  for (int j = 0; j < FIELD_WIDTH - 1; j++) {
    context->gameStateInfo.field[nonFullLine][j] = 1;
  }
  context->gameStateInfo.field[nonFullLine][FIELD_WIDTH - 1] = 0;

  int clearedLines = clearLines();
  ck_assert_int_eq(clearedLines, 0);

  for (int j = 0; j < FIELD_WIDTH - 1; j++) {
    ck_assert_int_eq(context->gameStateInfo.field[nonFullLine][j], 1);
  }
  ck_assert_int_eq(context->gameStateInfo.field[nonFullLine][FIELD_WIDTH - 1],
                   0);

  cleanupTest();
}
END_TEST

Suite *suiteClearLines(void) {
  Suite *s = suite_create("suite_clearLines");
  TCase *tc = tcase_create("tc_clearLines");

  tcase_add_checked_fixture(tc, setupTest, cleanupTest);
  tcase_add_test(tc, test_clearLines_one_line);
  tcase_add_test(tc, test_clearLines_multiple_lines);
  tcase_add_test(tc, test_clearLines_no_lines);

  suite_add_tcase(s, tc);
  return s;
}