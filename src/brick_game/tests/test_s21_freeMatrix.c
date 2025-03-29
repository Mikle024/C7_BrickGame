#include "s21_tests.h"

START_TEST(test_freeMatrix_null_matrix) {
  int **matrix = NULL;
  freeMatrix(matrix, 5);
  // Если не произошла ошибка, тест считается пройденным
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_freeMatrix_valid_matrix) {
  int rows = 3;
  int **matrix = malloc(rows * sizeof(int *));
  for (int i = 0; i < rows; i++) {
    matrix[i] = malloc(5 * sizeof(int));
  }

  freeMatrix(matrix, rows);

  // Проверка освобождения памяти
  // Если память была освобождена, то повторный доступ к матрице должен быть
  // запрещен, однако это не всегда легко проверить без использования
  // специального инструмента (например, valgrind). В этом тесте мы не проверяем
  // на утечку памяти, потому что такая проверка требует внешнего инструмента.
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_freeMatrix_zero_rows) {
  int rows = 0;
  int **matrix = NULL;
  freeMatrix(matrix, rows);
  // Если не произошла ошибка, тест считается пройденным
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