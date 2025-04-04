#include "s21_tests.h"

START_TEST(test_positive_initRandom) {
  setupTest();

  initRandom();
  int first = rand();
  int second = rand();

  ck_assert_int_ne(first, second);

  cleanupTest();
}
END_TEST

Suite *suiteInitRandom(void) {
  Suite *suite = suite_create("suite_initRandom");
  TCase *tc = tcase_create("tc_initRandom");

  tcase_add_checked_fixture(tc, setupTest, cleanupTest);
  tcase_add_test(tc, test_positive_initRandom);

  suite_add_tcase(suite, tc);
  return suite;
}