#include "s21_tests.h"

START_TEST(test_countScore_lines) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  context->gameStateInfo.score = 0;
  context->gameStateInfo.level = 1;
  context->gameStateInfo.high_score = 2000;
  context->gameStateInfo.speed = START_DELAY;

  countScore(1);
  ck_assert_int_eq(context->gameStateInfo.score, 100);

  countScore(2);
  ck_assert_int_eq(context->gameStateInfo.score, 400);

  countScore(3);
  ck_assert_int_eq(context->gameStateInfo.score, 1100);

  countScore(4);
  ck_assert_int_eq(context->gameStateInfo.score, 2600);

  cleanupTest();
}
END_TEST

START_TEST(test_countScore_level_change) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  context->gameStateInfo.score = 0;
  context->gameStateInfo.level = 1;
  context->gameStateInfo.speed = START_DELAY;

  context->gameStateInfo.score = 599;
  countScore(0);
  ck_assert_int_eq(context->gameStateInfo.level, 1);
  ck_assert_int_eq(context->gameStateInfo.speed, START_DELAY);

  context->gameStateInfo.score = 601;
  countScore(0);
  ck_assert_int_eq(context->gameStateInfo.level, 2);
  ck_assert_int_eq(context->gameStateInfo.speed, START_DELAY - 72);

  context->gameStateInfo.score = 1201;
  countScore(0);
  ck_assert_int_eq(context->gameStateInfo.level, 3);
  ck_assert_int_eq(context->gameStateInfo.speed, START_DELAY - 144);

  cleanupTest();
}
END_TEST

START_TEST(test_countScore_max_level) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  context->gameStateInfo.score = 0;
  context->gameStateInfo.level = 1;
  context->gameStateInfo.speed = START_DELAY;

  context->gameStateInfo.score = 6000;
  countScore(0);
  ck_assert_int_eq(context->gameStateInfo.level, MAX_LEVEL);

  int currentSpeed = context->gameStateInfo.speed;
  countScore(0);
  ck_assert_int_eq(context->gameStateInfo.speed, currentSpeed);

  cleanupTest();
}
END_TEST

START_TEST(test_countScore_high_score) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  context->gameStateInfo.score = 100;
  context->gameStateInfo.high_score = 1000;

  countScore(0);
  ck_assert_int_eq(context->gameStateInfo.high_score, 1000);

  context->gameStateInfo.score = 1100;
  countScore(0);
  ck_assert_int_eq(context->gameStateInfo.high_score, 1100);

  context->gameStateInfo.score = 900;
  countScore(0);
  ck_assert_int_eq(context->gameStateInfo.high_score, 1100);

  cleanupTest();
}
END_TEST

START_TEST(test_countScore_edge_cases) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  context->gameStateInfo.score = 0;
  context->gameStateInfo.level = 1;
  context->gameStateInfo.speed = START_DELAY;

  countScore(0);
  ck_assert_int_eq(context->gameStateInfo.score, 0);

  countScore(-1);
  ck_assert_int_eq(context->gameStateInfo.score, 0);

  int beforeScore = context->gameStateInfo.score;
  countScore(5);
  ck_assert_int_ge(context->gameStateInfo.score, beforeScore);

  context->gameStateInfo.score = 1000000;
  countScore(4);
  ck_assert_int_eq(context->gameStateInfo.score, 1001500);

  cleanupTest();
}
END_TEST

START_TEST(test_countScore_speed_limits) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  context->gameStateInfo.score = 0;
  context->gameStateInfo.level = 1;
  context->gameStateInfo.speed = START_DELAY;

  context->gameStateInfo.score = 6000;
  countScore(0);
  ck_assert_int_eq(context->gameStateInfo.level, MAX_LEVEL);
  ck_assert_int_eq(context->gameStateInfo.speed, MIN_DELAY);

  countScore(0);
  ck_assert_int_eq(context->gameStateInfo.speed, MIN_DELAY);

  cleanupTest();
}
END_TEST

Suite *suiteCountScore(void) {
  Suite *s = suite_create("suite_countScore");
  TCase *tc = tcase_create("tc_countScore");

  tcase_add_checked_fixture(tc, setupTest, cleanupTest);
  tcase_add_test(tc, test_countScore_lines);
  tcase_add_test(tc, test_countScore_level_change);
  tcase_add_test(tc, test_countScore_max_level);
  tcase_add_test(tc, test_countScore_high_score);
  tcase_add_test(tc, test_countScore_edge_cases);
  tcase_add_test(tc, test_countScore_speed_limits);

  suite_add_tcase(s, tc);
  return s;
}