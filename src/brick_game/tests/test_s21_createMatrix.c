#include "s21_tests.h"

START_TEST(test_createMatrix_valid) {
  int rows = 3;
  int columns = 4;
  
  int **matrix = createMatrix(rows, columns);
  
  // Проверяем, что матрица создана успешно
  ck_assert_ptr_nonnull(matrix);
  
  // Проверяем, что все элементы матрицы инициализированы нулями
  for (int i = 0; i < rows; i++) {
    ck_assert_ptr_nonnull(matrix[i]);
    for (int j = 0; j < columns; j++) {
      ck_assert_int_eq(matrix[i][j], 0);
    }
  }
  
  // Освобождаем память
  freeMatrix(matrix, rows);
}
END_TEST

START_TEST(test_createMatrix_zero_size) {
  // Тест на создание матрицы с нулевыми размерами
  int **matrix = createMatrix(0, 0);
  
  // Должно вернуть ненулевой указатель, хотя реальная матрица будет пустой
  ck_assert_ptr_nonnull(matrix);
  
  // Освобождаем память
  freeMatrix(matrix, 0);
}
END_TEST

START_TEST(test_createMatrix_large_size) {
  // Тест на создание большой матрицы
  int rows = 100;
  int columns = 100;
  
  int **matrix = createMatrix(rows, columns);
  
  // Проверяем, что матрица создана успешно
  ck_assert_ptr_nonnull(matrix);
  
  // Проверяем несколько случайных ячеек
  ck_assert_int_eq(matrix[0][0], 0);
  ck_assert_int_eq(matrix[50][50], 0);
  ck_assert_int_eq(matrix[99][99], 0);
  
  // Освобождаем память
  freeMatrix(matrix, rows);
}
END_TEST

Suite *suiteCreateMatrix(void) {
  Suite *s = suite_create("suite_createMatrix");
  TCase *tc = tcase_create("tc_createMatrix");
  
  tcase_add_test(tc, test_createMatrix_valid);
  tcase_add_test(tc, test_createMatrix_zero_size);
  tcase_add_test(tc, test_createMatrix_large_size);
  
  suite_add_tcase(s, tc);
  return s;
} 