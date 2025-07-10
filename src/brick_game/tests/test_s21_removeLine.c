#include "s21_tests.h"

START_TEST(test_removeLine_middle) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  if (context->gameStateInfo.field) {
    freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  }
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);

  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      context->gameStateInfo.field[i][j] = i + 1;
    }
  }

  int lineToRemove = 5;
  removeLine(lineToRemove);

  for (int j = 0; j < FIELD_WIDTH; j++) {
    ck_assert_int_eq(context->gameStateInfo.field[0][j], 0);
  }

  for (int i = 1; i <= lineToRemove; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      ck_assert_int_eq(context->gameStateInfo.field[i][j], i);
    }
  }

  for (int i = lineToRemove + 1; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      ck_assert_int_eq(context->gameStateInfo.field[i][j], i + 1);
    }
  }

  cleanupTest();
}
END_TEST

START_TEST(test_removeLine_top) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  if (context->gameStateInfo.field) {
    freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  }
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);

  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      context->gameStateInfo.field[i][j] = i + 1;
    }
  }

  removeLine(0);

  for (int j = 0; j < FIELD_WIDTH; j++) {
    ck_assert_int_eq(context->gameStateInfo.field[0][j], 0);
  }

  for (int i = 1; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      ck_assert_int_eq(context->gameStateInfo.field[i][j], i + 1);
    }
  }

  cleanupTest();
}
END_TEST

START_TEST(test_removeLine_bottom) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  if (context->gameStateInfo.field) {
    freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  }
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);

  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      context->gameStateInfo.field[i][j] = i + 1;
    }
  }

  int lastLine = FIELD_HEIGHT - 1;
  removeLine(lastLine);

  for (int j = 0; j < FIELD_WIDTH; j++) {
    ck_assert_int_eq(context->gameStateInfo.field[0][j], 0);
  }

  for (int i = 1; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      ck_assert_int_eq(context->gameStateInfo.field[i][j], i);
    }
  }

  cleanupTest();
}
END_TEST

Suite *suiteRemoveLine(void) {
  Suite *s = suite_create("suite_removeLine");
  TCase *tc = tcase_create("tc_removeLine");

  tcase_add_checked_fixture(tc, setupTest, cleanupTest);
  tcase_add_test(tc, test_removeLine_middle);
  tcase_add_test(tc, test_removeLine_top);
  tcase_add_test(tc, test_removeLine_bottom);

  suite_add_tcase(s, tc);
  return s;
}