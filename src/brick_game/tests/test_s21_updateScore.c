#include "s21_tests.h"
#include <stdio.h>
#include <unistd.h>

// Тестирование обновления счета
START_TEST(test_updateScore_positive) {
  // Записываем новое значение в файл
  int testScore = 1000;
  updateScore(testScore);
  
  // Читаем значение обратно и проверяем, что оно сохранилось правильно
  int readScore = initHighScore();
  ck_assert_int_eq(readScore, testScore);
}
END_TEST

// Тестирование обновления с нулевым счетом
START_TEST(test_updateScore_zero) {
  // Записываем нулевое значение
  updateScore(0);
  
  // Проверяем, что значение сохранено как 0
  int readScore = initHighScore();
  ck_assert_int_eq(readScore, 0);
}
END_TEST

// Тестирование обновления с отрицательным счетом
// (Функция должна корректно обрабатывать даже такие случаи)
START_TEST(test_updateScore_negative) {
  // Записываем отрицательное значение
  updateScore(-100);
  
  // Проверяем результат (будет 0 из-за проверки в initHighScore)
  int readScore = initHighScore();
  ck_assert_int_eq(readScore, 0);
}
END_TEST

// Набор тестов для функции updateScore
Suite *suiteUpdateScore(void) {
  Suite *s = suite_create("suite_updateScore");
  TCase *tc = tcase_create("tc_updateScore");
  
  tcase_add_test(tc, test_updateScore_positive);
  tcase_add_test(tc, test_updateScore_zero);
  tcase_add_test(tc, test_updateScore_negative);
  
  suite_add_tcase(s, tc);
  return s;
}
