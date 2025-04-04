#include "s21_tests.h"

START_TEST(test_freeMatrix_null_matrix) {
  int **matrix = NULL;
  freeMatrix(matrix, 5);
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_freeMatrix_valid_matrix) {
  int rows = 3;
  int **matrix = malloc(rows * sizeof(int *));
  if (matrix) {
    for (int i = 0; i < rows; i++) {
      matrix[i] = malloc(5 * sizeof(int));
    }

    freeMatrix(matrix, rows);
    ck_assert_int_eq(1, 1);
  } else {
    ck_assert_msg(0, "Memory allocation failed");
  }
}
END_TEST

START_TEST(test_freeMatrix_zero_rows) {
  int rows = 0;
  int **matrix = NULL;
  freeMatrix(matrix, rows);
  ck_assert_int_eq(1, 1);
}
END_TEST

Suite *suiteFreeMatrix(void) {
  Suite *suite = suite_create("suite_freeMatrix");
  TCase *tc = tcase_create("tc_freeMatrix");

  tcase_add_test(tc, test_freeMatrix_null_matrix);
  tcase_add_test(tc, test_freeMatrix_valid_matrix);
  tcase_add_test(tc, test_freeMatrix_zero_rows);

  suite_add_tcase(suite, tc);
  return suite;
}