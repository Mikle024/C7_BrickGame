#include "s21_tests.h"

START_TEST(test_timer_not_triggered) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  context->lastTime = getCurrentTime();
  context->gameStateInfo.speed = 1000;

  ck_assert_int_eq(timer(), false);

  cleanupTest();
}
END_TEST

START_TEST(test_timer_triggered) {
  setupTest();
  GameContext_t *context = getCurrentContext();

  context->lastTime = 0;
  context->gameStateInfo.speed = 1;

  ck_assert_int_eq(timer(), true);

  ck_assert_int_gt(context->lastTime, 0);

  cleanupTest();
}
END_TEST

Suite *suiteTimer(void) {
  Suite *suite = suite_create("suite_timer");
  TCase *tc = tcase_create("tc_timer");

  tcase_add_checked_fixture(tc, setupTest, cleanupTest);
  tcase_add_test(tc, test_timer_not_triggered);
  tcase_add_test(tc, test_timer_triggered);

  suite_add_tcase(suite, tc);
  return suite;
}