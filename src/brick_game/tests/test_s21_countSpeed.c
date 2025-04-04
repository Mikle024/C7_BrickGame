#include "s21_tests.h"

START_TEST(test_countSpeed_levels) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  context->gameStateInfo.level = 1;
  countSpeed();
  ck_assert_int_eq(context->gameStateInfo.speed, START_DELAY);

  context->gameStateInfo.level = 5;
  countSpeed();
  int expectedSpeed5 = START_DELAY - (5 - START_LEVEL) *
                                         (START_DELAY - MIN_DELAY) /
                                         (MAX_LEVEL - START_LEVEL);
  ck_assert_int_eq(context->gameStateInfo.speed, expectedSpeed5);

  context->gameStateInfo.level = MAX_LEVEL;
  countSpeed();
  int expectedSpeedMax = START_DELAY - (MAX_LEVEL - START_LEVEL) *
                                           (START_DELAY - MIN_DELAY) /
                                           (MAX_LEVEL - START_LEVEL);
  ck_assert_int_eq(context->gameStateInfo.speed, expectedSpeedMax);

  cleanupTest();
}
END_TEST

START_TEST(test_countSpeed_edge_cases) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  context->gameStateInfo.level = MAX_LEVEL + 5;
  countSpeed();
  ck_assert_int_eq(context->gameStateInfo.speed, MIN_DELAY);

  cleanupTest();
}
END_TEST

Suite *suiteCountSpeed(void) {
  Suite *s = suite_create("suite_countSpeed");
  TCase *tc = tcase_create("tc_countSpeed");

  tcase_add_checked_fixture(tc, setupTest, cleanupTest);
  tcase_add_test(tc, test_countSpeed_levels);
  tcase_add_test(tc, test_countSpeed_edge_cases);

  suite_add_tcase(s, tc);
  return s;
}
