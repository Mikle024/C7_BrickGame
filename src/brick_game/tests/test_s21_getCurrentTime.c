#include "s21_tests.h"

START_TEST(test_positive_getCurrentTime) {
  setupTest();

  long long first = getCurrentTime();
  sleep(1);
  long long second = getCurrentTime();

  ck_assert_int_ne(first, second);

  cleanupTest();
}
END_TEST

Suite *suiteGetCurrentTime(void) {
  Suite *suite = suite_create("suite_getCurrentTime");
  TCase *tc = tcase_create("tc_getCurrentTime");

  tcase_add_checked_fixture(tc, setupTest, cleanupTest);
  tcase_add_test(tc, test_positive_getCurrentTime);

  suite_add_tcase(suite, tc);
  return suite;
}