#include "s21_tests.h"

START_TEST(test_updateScore_positive) {
  int testScore = 1000;
  updateScore(testScore);

  int readScore = initHighScore();
  ck_assert_int_eq(readScore, testScore);
}
END_TEST

START_TEST(test_updateScore_zero) {
  updateScore(0);

  int readScore = initHighScore();
  ck_assert_int_eq(readScore, 0);
}
END_TEST

START_TEST(test_updateScore_negative) {
  updateScore(-100);

  int readScore = initHighScore();
  ck_assert_int_eq(readScore, 0);
}
END_TEST

START_TEST(test_updateScore_file_error) {
  remove("highScore.txt");

  MKDIR("highScore.txt");

  updateScore(1234);

  rmdir("highScore.txt");

  updateScore(0);
}
END_TEST

Suite *suiteUpdateScore(void) {
  Suite *s = suite_create("suite_updateScore");
  TCase *tc = tcase_create("tc_updateScore");

  tcase_add_test(tc, test_updateScore_positive);
  tcase_add_test(tc, test_updateScore_zero);
  tcase_add_test(tc, test_updateScore_negative);
  tcase_add_test(tc, test_updateScore_file_error);

  suite_add_tcase(s, tc);
  return s;
}
