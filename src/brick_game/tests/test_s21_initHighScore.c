#include "s21_tests.h"

START_TEST(test_highscore_no_file) {
  remove("highScore.txt");
  ck_assert_int_eq(initHighScore(), 0);
}
END_TEST

START_TEST(test_highscore_invalid_content) {
  FILE *fp = fopen("highScore.txt", "w");
  fprintf(fp, "invalid123\n");
  fclose(fp);

  ck_assert_int_eq(initHighScore(), 0);
}
END_TEST

START_TEST(test_highscore_negative_value) {
  FILE *fp = fopen("highScore.txt", "w");
  fprintf(fp, "-100\n");
  fclose(fp);

  ck_assert_int_eq(initHighScore(), 0);
}
END_TEST

START_TEST(test_highscore_valid_value) {
  FILE *fp = fopen("highScore.txt", "w");
  fprintf(fp, "5000\n");
  fclose(fp);

  ck_assert_int_eq(initHighScore(), 5000);
}
END_TEST

START_TEST(test_highscore_empty_file) {
  FILE *fp = fopen("highScore.txt", "w");
  fclose(fp);

  ck_assert_int_eq(initHighScore(), 0);
}
END_TEST

START_TEST(test_highscore_zero_value) {
  FILE *fp = fopen("highScore.txt", "w");
  fprintf(fp, "0\n");
  fclose(fp);

  ck_assert_int_eq(initHighScore(), 0);
}
END_TEST

Suite *suiteInitHighScore(void) {
  Suite *suite = suite_create("suite_initHighScore");
  TCase *tc = tcase_create("tc_initHighScore");

  tcase_add_test(tc, test_highscore_no_file);
  tcase_add_test(tc, test_highscore_invalid_content);
  tcase_add_test(tc, test_highscore_negative_value);
  tcase_add_test(tc, test_highscore_valid_value);
  tcase_add_test(tc, test_highscore_empty_file);
  tcase_add_test(tc, test_highscore_zero_value);

  suite_add_tcase(suite, tc);
  return suite;
}