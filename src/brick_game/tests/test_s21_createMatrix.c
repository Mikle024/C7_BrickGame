#include "s21_tests.h"

START_TEST(test_createMatrix_valid) {
  int const rows = 3;
  int const columns = 4;

  int **matrix = createMatrix(rows, columns);

  ck_assert_ptr_nonnull(matrix);

  for (int i = 0; i < rows; i++) {
    ck_assert_ptr_nonnull(matrix[i]);
    for (int j = 0; j < columns; j++) {
      ck_assert_int_eq(matrix[i][j], 0);
    }
  }

  freeMatrix(matrix, rows);
}
END_TEST

START_TEST(test_createMatrix_zero_size) {
  int **matrix = createMatrix(0, 0);

  ck_assert_ptr_nonnull(matrix);

  freeMatrix(matrix, 0);
}
END_TEST

START_TEST(test_createMatrix_large_size) {
  int rows = 100;
  int columns = 100;

  int **matrix = createMatrix(rows, columns);

  ck_assert_ptr_nonnull(matrix);

  ck_assert_int_eq(matrix[0][0], 0);
  ck_assert_int_eq(matrix[50][50], 0);
  ck_assert_int_eq(matrix[99][99], 0);

  freeMatrix(matrix, rows);
}
END_TEST

START_TEST(test_createMatrix_negative_size) {
  int **matrix = createMatrix(-1, -1);
  ck_assert_ptr_null(matrix);

  if (matrix) {
    freeMatrix(matrix, 0);
  }
}
END_TEST

START_TEST(test_createMatrix_negative_size_rows) {
  int **matrix = createMatrix(-1, 1);
  ck_assert_ptr_null(matrix);

  if (matrix) {
    freeMatrix(matrix, 0);
  }
}
END_TEST

START_TEST(test_createMatrix_negative_size_column) {
  int **matrix = createMatrix(1, -1);
  ck_assert_ptr_null(matrix);

  if (matrix) {
    freeMatrix(matrix, 0);
  }
}
END_TEST

Suite *suiteCreateMatrix(void) {
  Suite *s = suite_create("suite_createMatrix");
  TCase *tc = tcase_create("tc_createMatrix");

  tcase_add_test(tc, test_createMatrix_valid);
  tcase_add_test(tc, test_createMatrix_zero_size);
  tcase_add_test(tc, test_createMatrix_large_size);
  tcase_add_test(tc, test_createMatrix_negative_size);
  tcase_add_test(tc, test_createMatrix_negative_size_rows);
  tcase_add_test(tc, test_createMatrix_negative_size_column);

  suite_add_tcase(s, tc);
  return s;
}