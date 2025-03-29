#include "s21_tests.h"

START_TEST(test_timer_not_triggered) {
  GameContext_t *context = getCurrentContext();
  context->lastTime = getCurrentTime();
  context->gameStateInfo.speed = 1000;  // 1 секунда

  ck_assert_int_eq(timer(), false);
}
END_TEST

START_TEST(test_timer_triggered) {
  GameContext_t *context = getCurrentContext();
  context->lastTime = getCurrentTime() - context->gameStateInfo.speed - 1;
  context->gameStateInfo.speed = 1000;  // 1 секунда

  ck_assert_int_eq(timer(), true);
}
END_TEST

Suite *suiteTimer(void) {
  Suite *suite = suite_create("suite_timer");
  TCase *tc = tcase_create("tc_timer");

  tcase_add_test(tc, test_timer_not_triggered);
  tcase_add_test(tc, test_timer_triggered);

  suite_add_tcase(suite, tc);
  return suite;
}