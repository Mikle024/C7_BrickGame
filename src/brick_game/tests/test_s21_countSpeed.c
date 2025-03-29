#include "s21_tests.h"

// Тест изменения скорости на разных уровнях
START_TEST(test_countSpeed_levels) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  
  // Сохраняем исходное состояние
  int originalLevel = context->gameStateInfo.level;
  int originalSpeed = context->gameStateInfo.speed;
  
  // Тестируем скорость на уровне 1
  context->gameStateInfo.level = 1;
  countSpeed();
  ck_assert_int_eq(context->gameStateInfo.speed, START_DELAY);
  
  // Тестируем скорость на уровне 5
  context->gameStateInfo.level = 5;
  countSpeed();
  ck_assert_int_lt(context->gameStateInfo.speed, START_DELAY); // Скорость должна уменьшиться
  ck_assert_int_gt(context->gameStateInfo.speed, MIN_DELAY);   // Но не стать меньше минимальной
  
  // Тестируем скорость на максимальном уровне
  context->gameStateInfo.level = MAX_LEVEL;
  countSpeed();
  int expectedSpeed = START_DELAY - (MAX_LEVEL - 1) * ((START_DELAY - MIN_DELAY) / (MAX_LEVEL - 1));
  ck_assert_int_eq(context->gameStateInfo.speed, expectedSpeed);
  
  // Восстанавливаем исходное состояние
  context->gameStateInfo.level = originalLevel;
  context->gameStateInfo.speed = originalSpeed;
}
END_TEST

// Тест предельных значений уровней
START_TEST(test_countSpeed_edge_cases) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  
  // Сохраняем исходное состояние
  int originalLevel = context->gameStateInfo.level;
  int originalSpeed = context->gameStateInfo.speed;
  
  // Тестируем скорость на уровне 0 (некорректное значение)
  context->gameStateInfo.level = 0;
  countSpeed();
  // Ожидаем, что скорость будет установлена в соответствии с формулой
  ck_assert_int_le(context->gameStateInfo.speed, START_DELAY);
  
  // Тестируем скорость на уровне выше максимального
  context->gameStateInfo.level = MAX_LEVEL + 5;
  countSpeed();
  ck_assert_int_eq(context->gameStateInfo.speed, MIN_DELAY); // Должна быть минимальная скорость
  
  // Восстанавливаем исходное состояние
  context->gameStateInfo.level = originalLevel;
  context->gameStateInfo.speed = originalSpeed;
}
END_TEST

// Набор тестов для функции countSpeed
Suite *suiteCountSpeed(void) {
  Suite *s = suite_create("suite_countSpeed");
  TCase *tc = tcase_create("tc_countSpeed");
  
  tcase_add_test(tc, test_countSpeed_levels);
  tcase_add_test(tc, test_countSpeed_edge_cases);
  
  suite_add_tcase(s, tc);
  return s;
}
