#include "s21_tests.h"

START_TEST(test_positive_getCurrentContext) {
  GameContext_t *ctx1 = getCurrentContext();
  ck_assert_ptr_nonnull(ctx1);

  GameContext_t *ctx2 = getCurrentContext();
  ck_assert_ptr_eq(ctx1, ctx2);

  ck_assert(ctx1->gameStateInfo.field != NULL);
  ck_assert(ctx1->gameStateInfo.next != NULL);
  ck_assert_int_ge(ctx1->gameStateInfo.score, 0);
  ck_assert_int_ge(ctx1->gameStateInfo.high_score, 0);
  ck_assert_int_ge(ctx1->gameStateInfo.level, 1);
  ck_assert_int_ge(ctx1->gameStateInfo.speed, 1);
}
END_TEST

Suite *suiteGetCurrentContext(void) {
  Suite *suite = suite_create("suite_getCurrentContext");
  TCase *tc = tcase_create("tc_getCurrentContext");

  tcase_add_test(tc, test_positive_getCurrentContext);

  suite_add_tcase(suite, tc);
  return suite;
}