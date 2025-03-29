#include "s21_tests.h"

// Тест координат внутри поля
START_TEST(test_pixelInField_inside) {
  // Проверяем координаты внутри поля
  ck_assert_int_eq(pixelInField(0, 0), true);                      // Верхний левый угол
  ck_assert_int_eq(pixelInField(FIELD_WIDTH - 1, 0), true);        // Верхний правый угол
  ck_assert_int_eq(pixelInField(0, FIELD_HEIGHT - 1), true);       // Нижний левый угол
  ck_assert_int_eq(pixelInField(FIELD_WIDTH - 1, FIELD_HEIGHT - 1), true); // Нижний правый угол
  ck_assert_int_eq(pixelInField(FIELD_WIDTH / 2, FIELD_HEIGHT / 2), true); // Центр поля
}
END_TEST

// Тест координат вне поля
START_TEST(test_pixelInField_outside) {
  // Проверяем координаты за пределами поля
  ck_assert_int_eq(pixelInField(-1, 0), false);          // Левее левой границы
  ck_assert_int_eq(pixelInField(0, -1), false);          // Выше верхней границы
  ck_assert_int_eq(pixelInField(FIELD_WIDTH, 0), false); // Правее правой границы
  ck_assert_int_eq(pixelInField(0, FIELD_HEIGHT), false); // Ниже нижней границы
  
  // Проверяем координаты в углах за пределами поля
  ck_assert_int_eq(pixelInField(-1, -1), false);
  ck_assert_int_eq(pixelInField(FIELD_WIDTH, FIELD_HEIGHT), false);
  ck_assert_int_eq(pixelInField(-1, FIELD_HEIGHT), false);
  ck_assert_int_eq(pixelInField(FIELD_WIDTH, -1), false);
  
  // Проверяем граничные значения
  ck_assert_int_eq(pixelInField(FIELD_WIDTH, FIELD_HEIGHT - 1), false);
  ck_assert_int_eq(pixelInField(FIELD_WIDTH - 1, FIELD_HEIGHT), false);
}
END_TEST

// Набор тестов для функции pixelInField
Suite *suitePixelInField(void) {
  Suite *s = suite_create("suite_pixelInField");
  TCase *tc = tcase_create("tc_pixelInField");
  
  tcase_add_test(tc, test_pixelInField_inside);
  tcase_add_test(tc, test_pixelInField_outside);
  
  suite_add_tcase(s, tc);
  return s;
} 