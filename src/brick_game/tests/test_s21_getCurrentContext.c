#include "s21_tests.h"

START_TEST(test_positive_getCurrentContext) {
  GameContext_t *ctx1 = getCurrentContext();
  ck_assert_ptr_nonnull(ctx1);
}
END_TEST

Suite *suiteGetCurrentContext(void) {
  Suite *suite = suite_create("suite_getCurrentContext");
  TCase *tc = tcase_create("tc_getCurrentContext");

  tcase_add_test(tc, test_positive_getCurrentContext);

  suite_add_tcase(suite, tc);
  return suite;
}